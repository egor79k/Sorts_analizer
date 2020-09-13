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
	int button_x_pos = 10;

	struct sort_algorithm
	{
		bool counted = false;
		void (*sort) (sort_counter<int> *, size_t);
		Button button;
		Graph compares_graph;
		Graph assigns_graph;

		sort_algorithm (void (*sort_alg) (sort_counter<int> *, size_t), const sf::Color &color, char *name) :
			sort (sort_alg),
			button (Button (10, 600, 150, 70, color, name, 35)),
			compares_graph (Graph (5, 500, 10, 10000, color)),
			assigns_graph (Graph (350, 500, 10, 10000, color))
		{}// button_x_pos += 160; }
	};

	sort_algorithm bubble    (bubble_sort,    sf::Color::Red,          "Bubble");
	sort_algorithm quick     (quick_sort,     sf::Color::Green,        "Quick");
	sort_algorithm selection (selection_sort, sf::Color::Blue,         "Selection");
	//sort_algorithm merge     (sf::Color (0, 255, 255), "Merge");

	//bool bubble_counted    = false;
	//bool quick_counted     = false;
	//bool selection_counted = false;
	//bool merge_counted     = false;


	sf::RenderWindow window(sf::VideoMode(700, 700), "Sorts analizer");

	//Graph gr (100, 100, 5, 10000, sf::Color::Blue);
	//Graph bubble_compares_graph (5,   500, 10, 10000, sf::Color::Red);
	//Graph bubble_assigns_graph  (350, 500, 10, 10000, sf::Color::Red);
	//Graph quick_compares_graph  (5,   500, 10, 10000, sf::Color::Green);
	//Graph quick_assigns_graph   (350, 500, 10, 10000, sf::Color::Green);

	//Button button_bubble    (10,  600, 150, 70, sf::Color::Red,    "Bubble",      35);
	//Button button_quick     (170, 600, 150, 70, sf::Color::Green,  "Quick",       35);
	//Button button_selection (330, 600, 150, 70, sf::Color::Blue,   "Selection",   35);
	//Button button_merge     (490, 600, 150, 70, sf::Color (0, 255, 255), "Merge", 35);

	//for (int f = 100; f < 1000; f += 100)
		//gr.add_point (f,  f * f);



	
	while (window.isOpen())
	{
		window.clear (sf::Color (255, 255, 255));

		//gr.draw (window);
		bubble.button.draw    (window);
		quick.button.draw     (window);
		selection.button.draw (window);
		//merge.button.draw     (window);


		if (bubble.counted)
		{
			bubble.compares_graph.draw (window);
			bubble.assigns_graph.draw (window);
		}

		if (quick.counted)
		{
			quick.compares_graph.draw (window);
			quick.assigns_graph.draw (window);
		}

		if (selection.counted)
		{
			selection.compares_graph.draw (window);
			selection.assigns_graph.draw (window);
		}

		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && static_cast<int> (event.key.code) == static_cast<int> (sf::Mouse::Left))
			{
				if (bubble.button.pressed (window) && !bubble.counted)
				{
					draw_sort_graph (bubble.compares_graph, bubble.assigns_graph, bubble.sort);
					bubble.counted = true;
				}
				else if (quick.button.pressed (window) && !quick.counted)
				{
					draw_sort_graph (quick.compares_graph, quick.assigns_graph, quick.sort);
					quick.counted = true;
				}
				else if (selection.button.pressed (window) && !selection.counted)
				{
					draw_sort_graph (selection.compares_graph, selection.assigns_graph, selection.sort);
					selection.counted = true;
				}
				//else if (merge.button.pressed (window))
					//draw_sort_graph (compares_graph, assigns_graph, <sort_counter<int>>);
			}
		}

		window.display();
	}
 
	return 0;
}