#include <iostream>
#include <SFML/Graphics.hpp>
#include "sorting_algorithms.cpp"
#include "type_wrapper.cpp"



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
		font.loadFromFile ("Crystal_Regular.ttf");
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
	const float x_scale;
	const float y_scale;
	float max_x;
	float max_y;
	float min_x;
	float min_y;
	uint32_t points_num;
	sf::Color color;
	sf::VertexArray graph;


public:
	Graph (float x, float y, float x_sc = 1, float y_sc = 1, const sf::Color &col = sf::Color::Black) :
		x_pos (x),
		y_pos (y),
		x_scale (x_sc),
		y_scale (y_sc),
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
		graph.append (sf::Vector2f (x_pos + x / x_scale, y_pos - y / y_scale));
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



sort_counter<int> *generate_array (int size)
{
	sort_counter<int> *arr = new sort_counter<int>[size];
	srand (345234);

	for (int i = 0; i < size; ++i)
		arr[i] = sort_counter<int> (rand () % RAND_MAX);

	return arr;
}



void draw_sort_graph (Graph &compares_graph, Graph &assigns_graph, void (*sort) (sort_counter<int> *, size_t))
{
	//Graph compares_graph (5, 300, 10, 10000, sf::Color::Red);
	//Graph assigns_graph  (250, 300, 10, 10000, sf::Color::Red);

	for (int i = 100; i < 3000; i += 100)
	{
		sort_counter<int> *array = generate_array (i);
		sort_counter<int>::reset ();
		sort (array, i);
		compares_graph.add_point (i, sort_counter<int>::compares ());
		assigns_graph.add_point  (i, sort_counter<int>::assigns ());
		printf("size: %d, comps: %d, assigns: %d\n", i, sort_counter<int>::compares (), sort_counter<int>::assigns ());
	}
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(700, 700), "Sorts analizer");

	//Graph gr (100, 100, 5, 10000, sf::Color::Blue);
	Graph compares_graph (5, 500, 10, 10000, sf::Color::Red);
	Graph assigns_graph  (350, 500, 10, 10000, sf::Color::Red);

	Button button_bubble    (10,  600, 150, 70, sf::Color::Red,    "Bubble",      40);
	Button button_quick     (170, 600, 150, 70, sf::Color::Green,  "Quick",       40);
	Button button_selection (330, 600, 150, 70, sf::Color::Blue,   "Selection",   40);
	Button button_merge     (490, 600, 150, 70, sf::Color (0, 255, 255), "Merge", 40);

	//for (int f = 100; f < 1000; f += 100)
		//gr.add_point (f,  f * f);



	
	while (window.isOpen())
	{
		window.clear (sf::Color (255, 255, 255));

		//gr.draw (window);
		button_bubble.draw    (window);
		button_quick.draw     (window);
		button_selection.draw (window);
		button_merge.draw     (window);

		compares_graph.draw (window);
		assigns_graph.draw  (window);

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
					draw_sort_graph (compares_graph, assigns_graph, bubble_sort<sort_counter<int>>);
			}
		}

		window.display();
	}
 
	return 0;
}