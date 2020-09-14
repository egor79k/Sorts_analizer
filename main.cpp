#include <iostream>
#include <SFML/Graphics.hpp>
#include "sorting_algorithms.cpp"
#include "type_wrapper.cpp"


const char Text_format[] = "Crystal_Regular.ttf";
const int Compares_graph_x_pos = 5;
const int Assigns_graph_x_pos  = 350;
const int Graph_y_pos = 500;
const int Window_side = 700;
const int Rand_seed = 345234;
const int Button_x_side = 150;
const int Button_y_side = 70;
const int Text_size = 35;
const int Iterations = 5000;
const int Graph_length = 333;
const int Iter_step = 50;



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
		font.loadFromFile (Text_format);
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



struct sort_algorithm
{
	static int button_x_pos;
	bool counted = false;
	void (*sort) (sort_counter<int> *, size_t);
	Button button;
	Graph compares_graph;
	Graph assigns_graph;

	sort_algorithm (void (*sort_alg) (sort_counter<int> *, size_t), const sf::Color &color, char *name) :
		sort (sort_alg),
		button (Button (button_x_pos, Graph_y_pos + 100, Button_x_side, Button_y_side, color, name, Text_size)),
		compares_graph (Graph (Compares_graph_x_pos, Graph_y_pos, Iterations / Graph_length, (Iterations * Iterations) / (Graph_y_pos * 3), color)),
		assigns_graph  (Graph (Assigns_graph_x_pos,  Graph_y_pos, Iterations / Graph_length, (Iterations * Iterations) / (Graph_y_pos * 3), color))
	{ button_x_pos += (Button_x_side + 10); }
};

int sort_algorithm::button_x_pos = 10;



sort_counter<int> *generate_array (int size)
{
	sort_counter<int> *arr = new sort_counter<int>[size];
	srand (Rand_seed);

	for (int i = 0; i < size; ++i)
		arr[i] = sort_counter<int> (rand () % RAND_MAX);

	return arr;
}



void count_sort_graph (sort_algorithm &sort_alg)
{
	for (int i = Iter_step; i < Iterations; i += Iter_step)
	{
		sort_counter<int> *array = generate_array (i);
		sort_counter<int>::reset ();
		sort_alg.sort (array, i);
		sort_alg.compares_graph.add_point (i, sort_counter<int>::compares ());
		sort_alg.assigns_graph.add_point  (i, sort_counter<int>::assigns ());
		sort_alg.counted = true;
		printf("size: %d, comps: %d, assigns: %d\n", i, sort_counter<int>::compares (), sort_counter<int>::assigns ());
	}
}



int main()
{
	sf::Font font;
	font.loadFromFile (Text_format);
	sf::Text compares_title = sf::Text ("Compares",    font, Text_size);
	sf::Text assigs_title   = sf::Text ("Assignments", font, Text_size);
	compares_title.setFillColor (sf::Color::Black);
	assigs_title.setFillColor   (sf::Color::Black);
	compares_title.setPosition (Compares_graph_x_pos + 2, 5);
	assigs_title.setPosition   (Assigns_graph_x_pos + 2 , 5);

	sort_algorithm bubble    (bubble_sort,    sf::Color::Red,   "Bubble");
	sort_algorithm quick     (quick_sort,     sf::Color::Green, "Quick");
	sort_algorithm selection (selection_sort, sf::Color::Blue,  "Selection");
	sort_algorithm gnome     (gnome_sort,     sf::Color (0, 255, 255), "Gnome");

	sf::RenderWindow window(sf::VideoMode (Window_side, Window_side), "Sorts analizer");


	while (window.isOpen())
	{
		window.clear (sf::Color (255, 255, 255));

		bubble.button.draw    (window);
		quick.button.draw     (window);
		selection.button.draw (window);
		gnome.button.draw     (window);

		window.draw (compares_title);
		window.draw (assigs_title);


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

		if (gnome.counted)
		{
			gnome.compares_graph.draw (window);
			gnome.assigns_graph.draw (window);
		}

		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && static_cast<int> (event.key.code) == static_cast<int> (sf::Mouse::Left))
			{
				if (bubble.button.pressed (window) && !bubble.counted)
					count_sort_graph (bubble);
				else if (quick.button.pressed (window) && !quick.counted)
					count_sort_graph (quick);
				else if (selection.button.pressed (window) && !selection.counted)
					count_sort_graph (selection);
				else if (gnome.button.pressed (window) && !gnome.counted)
					count_sort_graph (gnome);
			}
		}

		window.display();
	}
 
	return 0;
}