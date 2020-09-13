#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

const int Buttons_num = 4;



class Button
{
private:
	sf::RectangleShape rectangle;
	sf::Text text;

public:
	Button (int x_pos, int y_pos, float x_size, float y_size, const sf::Color &rect_color, char str[] = "", int text_size = 20, const sf::Color &text_color = sf::Color::Black)
	{
		rectangle = sf::RectangleShape (sf::Vector2f (x_size, y_size));
		rectangle.setFillColor (rect_color);
		rectangle.setPosition (x_pos, y_pos);

		static sf::Font font;
		font.loadFromFile ("Country_Western_Regular.ttf");
		text = sf::Text (str, font, text_size);
		text.setFillColor (text_color);
		text.setPosition (x_pos + 1, y_pos + 1);
	}

	bool pressed (sf::RenderWindow &window)
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition (window);
		return rectangle.getGlobalBounds ().contains (mouse_pos.x, mouse_pos.y);
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
	const float x_pos;
	const float y_pos;
	const float scale;
	float max_x;
	float max_y;
	float min_x;
	float min_y;
	uint32_t points_num;
	sf::Color color;
	sf::VertexArray graph;


public:
	Graph (float x, float y, float sc = 1, const sf::Color &col = sf::Color::Black) :
		x_pos (x),
		y_pos (y),
		scale (sc),
		max_x (x),
		max_y (y),
		min_x (x),
		min_y (y),
		points_num (0),
		color (col),
		graph (sf::VertexArray (sf::LineStrip))
	{}

	void add_point (float x, float y)
	{
		graph.append (sf::Vector2f (x_pos + x / scale, y_pos - y / scale));
		if (graph[points_num].position.x > max_x) max_x = graph[points_num].position.x;
		if (graph[points_num].position.y < max_y) max_y = graph[points_num].position.y;
		if (graph[points_num].position.x < min_x) min_x = graph[points_num].position.x;
		if (graph[points_num].position.y > min_y) min_y = graph[points_num].position.y;
		graph[points_num].color = color;
		++points_num;
	}

	void draw (sf::RenderWindow &window)
	{
		sf::RectangleShape Ox (sf::Vector2f (max_x - min_x, 1));
		sf::RectangleShape Oy (sf::Vector2f (1, min_y - max_y));
		Ox.setPosition (min_x, y_pos);
		Oy.setPosition (x_pos, max_y);
		Ox.setFillColor (sf::Color::Black);
		Oy.setFillColor (sf::Color::Black);
		window.draw (Ox);
		window.draw (Oy);
		window.draw (graph);
	}
};



int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Sorts analizer");

	Graph gr (100, 100, 0.1, sf::Color::Blue);

	Button button_bubble (200, 200, 100, 30, sf::Color::Red, "Bubble");

	for (float f = -10; f < 10; f += 0.1)
		gr.add_point (f,  1 / f);



	
	while (window.isOpen())
	{
		window.clear (sf::Color (255, 255, 255));

		gr.draw (window);
		button_bubble.draw (window);


		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && static_cast<int> (event.key.code) == static_cast<int> (sf::Mouse::Left))
			{
				//sf::Vector2i mouse_pos = sf::Mouse::getPosition (window);

				//if (button_bubble.getGlobalBounds ().contains (mouse_pos.x, mouse_pos.y))
				if (button_bubble.pressed (window))
					std::cout << "Button pressed!\n";
			}
		}

		window.display();
	}
 
	return 0;
}