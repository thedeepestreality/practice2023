#include <SFML/Graphics.hpp>
#include <vector>

using Point = sf::Vector2f;
std::vector<sf::Vertex> getLanesRectangle(
	const sf::ConvexShape& border, 
	double width
){
	double borderWidth = border.getPoint(2).x - border.getPoint(1).x;
	double x0 = border.getPoint(0).x + width/2;
	double yLo = border.getPoint(0).y;
	double yUp = border.getPoint(1).y;
	double factWidth = borderWidth - width;
	int laneCount = (int)(factWidth + width - 1) / width;
	double dx = factWidth / laneCount;
	std::vector<sf::Vertex> result;
	for (int i = 0; i <= laneCount; ++i) {
		result.emplace_back(Point(x0 + dx * i, yLo));
		result.emplace_back(Point(x0 + dx * i, yUp));
		result.emplace_back(Point(x0 + dx * i, yLo));
	}
	return result;
}

using Point = sf::Vector2f;
std::vector<sf::Vertex> getLanesTrapezoid(
	const sf::ConvexShape& border,
	double width
) {
	double upLength = border.getPoint(2).x - border.getPoint(1).x;
	double loLength = border.getPoint(3).x - border.getPoint(0).x;
	// get max side length
	double borderWidth = std::max(upLength, loLength);
	// get left x offset
	double x0 = std::min(border.getPoint(0).x, border.getPoint(1).x);
	// lower and upper y coordinate
	double yLo = border.getPoint(0).y;
	double yUp = border.getPoint(1).y;

	//double dx = factWidth / laneCount;

	// dir vector of left side
	double axL = border.getPoint(1).x - border.getPoint(0).x;
	double ayL = border.getPoint(1).y - border.getPoint(0).y;
	double aLength = std::sqrt(axL*axL + ayL * ayL);
	axL /= aLength;
	ayL /= aLength;
	// normal vector of left side
	double nxL = -ayL;
	double nyL = axL;

	// point on the first lane parallel to left side
	Point P0 = border.getPoint(1) + sf::Vector2f(nxL*width / 2, nyL*width / 2);
	// lane crossing with upper side
	double t = (yUp - P0.y) / ayL;
	double xUp0 = P0.x + axL * t;
	// lane crossing with lower side
	t = (yLo - P0.y) / ayL;
	double xLo0 = P0.x + axL * t;

	// width without left and right lane
	double factWidth = borderWidth - width/2 - (xLo0- x0);
	int laneCount = (int)(factWidth + width - 1) / width;
	double dWidth = factWidth / laneCount;

	// dir vector of right side
	double axR = border.getPoint(2).x - border.getPoint(3).x;
	double ayR = border.getPoint(2).y - border.getPoint(3).y;
	double aRLength = std::sqrt(axR*axR + ayR * ayR);
	axR /= aRLength;
	ayR /= aRLength;

	// calculate direction vector shift on each lane
	double dax = (axR - axL) / laneCount;
	double day = (ayR - ayL) / laneCount;

	std::vector<sf::Vertex> result;
	double xL0 = xLo0;
	double yCurr = yLo;
	double yOp = yUp;
	if (upLength > loLength) {
		xL0 = xUp0;
		yCurr = yUp;
		yOp = yLo;
	}
	for (int i = 0; i <= laneCount; ++i)
	{
		double xCurr = xL0 + i * dWidth;
		double axCurr = axL + i * dax;
		double ayCurr = ayL + i * day;

		t = (yOp - yCurr) / ayCurr;
		double xOp = xCurr + axCurr * t;

		result.emplace_back(Point(xCurr, yCurr));
		result.emplace_back(Point(xOp, yOp));
		result.emplace_back(Point(xCurr, yCurr));
	}
	//for (int i = 0; i <= laneCount; ++i) {
	//	result.emplace_back(Point(x0 + dx * i, yLo));
	//	result.emplace_back(Point(x0 + dx * i, yUp));
	//	result.emplace_back(Point(x0 + dx * i, yLo));
	//}
	return result;
}

sf::ConvexShape getLane(Point A, Point B, double width, sf::Color color) {
	sf::ConvexShape lane;
	// dir vector of left side
	double ax = B.x - A.x;
	double ay = B.y - A.y;
	double aLength = std::sqrt(ax*ax + ay * ay);
	ax /= aLength;
	ay /= aLength;
	// normal vector of left side
	double nx = -ay;
	double ny = ax;

	Point delta(nx*width / 2, ny*width / 2);
	lane.setPointCount(4);
	lane.setPoint(0, A - delta);
	lane.setPoint(1, B - delta);
	lane.setPoint(2, B + delta);
	lane.setPoint(3, A + delta);
	lane.setFillColor(color);
	return lane;
}

void drawLanes(
	const std::vector<sf::Vertex>& lanes, 
	double width, 
	sf::RenderWindow& window
) {
	for (int i = 0; i < lanes.size() / 3; ++i) {
		sf::Uint8 colorPortion = 255.0 * 3 * i / (lanes.size()-1);
		auto laneRect = getLane(
			lanes[i*3].position,
			lanes[i*3+1].position,
			width,
			sf::Color(0, 255 - colorPortion, colorPortion, 127)
		);
		window.draw(laneRect);
	}
}

int main()
{
	const int LANE_WIDTH = 50;
	const int BORDER_WIDTH = 410;
	const int BORDER_HEIGHT = 200;
	sf::RenderWindow window(
		sf::VideoMode(BORDER_WIDTH+20, BORDER_HEIGHT+20), 
		"SFML works!"
	);
	sf::ConvexShape border;
	border.setPointCount(4);
	border.setPoint(0, sf::Vector2f(10, 10+200));
	border.setPoint(1, sf::Vector2f(10+50, 10));
	border.setPoint(2, sf::Vector2f(10+BORDER_WIDTH, 10));
	border.setPoint(3, sf::Vector2f(10+BORDER_WIDTH, 10 + 200));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(1);
	border.setOutlineColor(sf::Color::Red);

	auto lanes = getLanesTrapezoid(border, LANE_WIDTH);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(border);
		window.draw(&lanes[0], lanes.size(), sf::LineStrip);
		drawLanes(lanes, LANE_WIDTH, window);
		window.display();
	}

	return 0;
}
