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
	double borderWidth = std::max(
		border.getPoint(2).x - border.getPoint(1).x, 
		border.getPoint(3).x - border.getPoint(0).x
	);
	double x0 = std::min(border.getPoint(0).x, border.getPoint(1).x);
	double yLo = border.getPoint(0).y;
	double yUp = border.getPoint(1).y;

	//double dx = factWidth / laneCount;
	double axL = border.getPoint(1).x - border.getPoint(0).x;
	double ayL = border.getPoint(1).y - border.getPoint(0).y;
	double aLength = std::sqrt(axL*axL + ayL * ayL);
	axL /= aLength;
	ayL /= aLength;
	double nxL = -ayL;
	double nyL = axL;
	std::vector<sf::Vertex> result;
	Point P0 = border.getPoint(1) + sf::Vector2f(nxL*width / 2, nyL*width / 2);
	double t = (yUp - P0.y) / ayL;
	double xUp0 = P0.x + axL * t;
	//result.emplace_back(Point(xUp0, yUp));
	t = (yLo - P0.y) / ayL;
	double xLo0 = P0.x + axL * t;
	//result.emplace_back(Point(xLo0, yLo));
	double factWidth = borderWidth - width/2 - (xLo0- x0);
	int laneCount = (int)(factWidth + width - 1) / width;
	double dWidth = factWidth / laneCount;

	double axR = border.getPoint(2).x - border.getPoint(3).x;
	double ayR = border.getPoint(2).y - border.getPoint(3).y;
	double aRLength = std::sqrt(axR*axR + ayR * ayR);
	axR /= aRLength;
	ayR /= aRLength;
	double dax = (axR - axL) / laneCount;
	double day = (ayR - ayL) / laneCount;

	//for (int i = 0; i <= laneCount; ++i) {
	//	result.emplace_back(Point(x0 + dx * i, yLo));
	//	result.emplace_back(Point(x0 + dx * i, yUp));
	//	result.emplace_back(Point(x0 + dx * i, yLo));
	//}
	return result;
}

sf::ConvexShape getLane(Point A, Point B, double width, sf::Color color) {
	sf::ConvexShape lane;
	Point delta(width / 2, 0);
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
