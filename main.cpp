#include <iostream>
#include <SFML/Graphics.hpp>

const int Buttons_num = 4;



class Button
{
private:
	sf::RectangleShape rectangle;
	sf::Text text;

public:
	Button (char *str, const sf::Color &color, int x, int y)
	{
		rectangle = sf::RectangleShape (sf::Vector2f (200, 60));
		rectangle.setFillColor (color);
		rectangle.setPosition (x, y);

		static sf::Font font;
		font.loadFromFile ("Country_Western_Regular.ttf");
		text = sf::Text (str, font, 50);
		text.setColor (sf::Color::Black);
		text.setPosition (x + 5, y + 5);
	}

	void draw (sf::RenderWindow &window)
	{
		window.draw (rectangle);
		window.draw (text);
	}
};



class Graph
{
private:
	sf::VertexArray graph;
	double scale;
	sf::Color color;
	const int x_pos;
	const int y_pos;
	const sf::RectangleShape Ox (Vector2f (100, 3));
	const sf::RectangleShape Oy (Vector2f (3, 100));


public:
	Graph (int x, int y, double sc, sf::Color col) : x_pos (x), y_pos (y), scale (sc), color (col)
	{
		Ox.setPosition (x, y + 100);
		Oy.setPosition (x, y);
		Ox.setFillColor (sf::Color::Black);
		Oy.setFillColor (sf::Color::Black);
	}

	void add_point (int x, int y)
	{
		graph.append (sf::Vector2f (x_pos + x / scale, y_pos + 100 - y / scale));
	}

	void draw (sf::RenderWindow &window)
	{
		window.draw (Ox);
		window.draw (Oy);
		window.draw (graph);
	}
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 200), "Sorts analizer");

	//Button button_bubble ("Bubble", sf::Color (150, 0, 0), 0, 0);

	sf::VertexArray func (sf::LineStrip);
	
	func.append (sf::Vector2f (0, 0));
	func.append (sf::Vector2f (10, 30));
	func.append (sf::Vector2f (20, 40));
	func.append (sf::Vector2f (30, 30));
	func.append (sf::Vector2f (40, 0));

	func[0].color = sf::Color::Blue;
	func[1].color = sf::Color::Blue;
	func[2].color = sf::Color::Blue;
	func[3].color = sf::Color::Blue;
	func[4].color = sf::Color::Blue;




	
	while (window.isOpen())
	{
		window.clear (sf::Color (255, 255, 255));

		window.draw (func);

		//button_bubble.draw (window);


		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && static_cast<int> (event.key.code) == static_cast<int> (sf::Mouse::Left))
			{
				sf::Vector2i mouse_pos = sf::Mouse::getPosition (window);
/*
				if (button_1.getGlobalBounds ().contains (mouse_pos.x, mouse_pos.y))
					std::cout << "Button pressed!\n";*/
			}
		}

		window.display();
	}
 
	return 0;
}