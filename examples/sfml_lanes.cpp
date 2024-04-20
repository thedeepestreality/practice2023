#include <SFML/Graphics.hpp>
#include <vector>

using Point = sf::Vector2f;
std::vector<sf::Vertex> getLanes(
	const sf::ConvexShape& border, 
	double width
){
	return { 
		// debug vertices
		//sf::Vertex(Point(35,210)),
		//sf::Vertex(Point(35,10)),
		//sf::Vertex(Point(35,210)),
		//sf::Vertex(Point(75,210)),
		//sf::Vertex(Point(75,10)),
		//sf::Vertex(Point(75,210)),
		//sf::Vertex(Point(135,210)),
		//sf::Vertex(Point(135,10)),
		//sf::Vertex(Point(135,210)),
		//sf::Vertex(Point(185,210)),
		//sf::Vertex(Point(185,10)),
		//sf::Vertex(Point(185,210))
	};
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
	sf::RenderWindow window(sf::VideoMode(420, 220), "SFML works!");

	sf::ConvexShape border;
	border.setPointCount(4);
	border.setPoint(0, sf::Vector2f(10, 210));
	border.setPoint(1, sf::Vector2f(10, 10));
	border.setPoint(2, sf::Vector2f(410, 10));
	border.setPoint(3, sf::Vector2f(410, 210));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(1);
	border.setOutlineColor(sf::Color::Red);

	auto lanes = getLanes(border, 50);

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
		drawLanes(lanes, 50, window);
		window.display();
	}

	return 0;
}
