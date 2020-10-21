#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "sorting_algorithms.cpp"
#include "type_wrapper.cpp"
#include "graphics/button.cpp"
#include "graphics/graph.cpp"


sf::Font Global_font;
const char Text_format[] = "graphics/include/Crystal_Regular.ttf";
const int Compares_graph_x_pos = 5;
const int Assigns_graph_x_pos  = 350;
const int Graph_y_pos = 500;
const int Window_side = 700;
const int Rand_seed = 345234;
const int Button_x_side = 150;
const int Button_y_side = 70;
const int Text_size = 33;
const int Iterations = 1000;
const int Graph_length = 333;
const int Iter_step = 50;



class SortButton : public Button
{
private:
	typedef void(*sort_function_ptr)(sort_counter<int>*,size_t);
	bool counted = false;
	sort_function_ptr sort;
	Graph compares_graph;
	Graph assigns_graph;
	const sf::Color Color_diff;

public:
	SortButton (sort_function_ptr _sort, const sf::Vector2f &size, const sf::Text &_text, const sf::Color &color_diff) :
		Button (sf::RectangleShape (size), _text),
		sort (_sort),
		Color_diff (color_diff),
		compares_graph (Graph (Compares_graph_x_pos, Graph_y_pos, Iterations / Graph_length, (Iterations * Iterations) / (Graph_y_pos * 3))),
		assigns_graph  (Graph (Assigns_graph_x_pos,  Graph_y_pos, Iterations / Graph_length, (Iterations * Iterations) / (Graph_y_pos * 3)))
	{}

	void action ()
	{
		printf ("Sort Action\n");
	}
	
	void press ()
	{
		set_fill_color (get_fill_color () - Color_diff);
	}

	void release ()
	{
		set_fill_color (get_fill_color () + Color_diff);
	}
};



class ClearButton : public Button
{
public:
	ClearButton () :
		Button (sf::RectangleShape (sf::Vector2f (50, 50)), sf::Text ("X", Global_font, 40))
	{}

	void action ()
	{
		printf ("Clear Action\n");
	}
};



struct sort_algorithm
{
	static int button_x_pos;
	bool counted = false;
	void (*sort) (sort_counter<int> *, size_t);
	SortButton button;
	Graph compares_graph;
	Graph assigns_graph;

	sort_algorithm (void (*sort_alg) (sort_counter<int> *, size_t), const sf::Color &color, const char *name) :
		sort (sort_alg),
		button (SortButton (sort_alg, sf::Vector2f(Button_x_side, Button_y_side), sf::Text (name, Global_font, Text_size), sf::Color (0, 0, 0))),
		compares_graph (Graph (Compares_graph_x_pos, Graph_y_pos, Iterations / Graph_length, (Iterations * Iterations) / (Graph_y_pos * 3), color)),
		assigns_graph  (Graph (Assigns_graph_x_pos,  Graph_y_pos, Iterations / Graph_length, (Iterations * Iterations) / (Graph_y_pos * 3), color))
	{
		button.set_fill_color (color);
		button.set_text_color (sf::Color::Black);
		button.set_position (sf::Vector2f(button_x_pos, Graph_y_pos + 100));
		button_x_pos += (Button_x_side + 10);
	}
};

int sort_algorithm::button_x_pos = 10;



sort_counter<int> *random_fill (sort_counter<int> *arr, size_t size)
{
	srand (Rand_seed);

	for (int i = 0; i < size; ++i)
		arr[i] = sort_counter<int> (rand () % RAND_MAX);

	return arr;
}



void count_sort_graph (sort_algorithm &sort_alg)
{
	for (int i = Iter_step; i < Iterations; i += Iter_step)
	{
		sort_counter<int> *array = random_fill (new sort_counter<int>[i], i);
		sort_counter<int>::reset ();
		sort_alg.sort (array, i);
		delete[] array;
		sort_alg.compares_graph.add_point (i, sort_counter<int>::compares ());
		sort_alg.assigns_graph.add_point  (i, sort_counter<int>::assigns ());
		//printf("size: %d, comps: %d, assigns: %d\n", i, sort_counter<int>::compares (), sort_counter<int>::assigns ());
	}
	
	sort_alg.counted = true;
}



int main()
{
	sf::RenderWindow window(sf::VideoMode (Window_side, Window_side), "Sorts analizer");

	const int sorts_num = 4;
	Button *buttons[5] = {};
	SortButton sort_buttons[sorts_num] = {
		SortButton (bubble_sort,    sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Bubble",    Global_font, Text_size), sf::Color (0, 0, 0)),
		SortButton (quick_sort,     sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Quick",     Global_font, Text_size), sf::Color (0, 0, 0)),
		SortButton (selection_sort, sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Selection", Global_font, Text_size), sf::Color (0, 0, 0)),
		SortButton (gnome_sort,     sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Gnome",     Global_font, Text_size), sf::Color (0, 0, 0))
	};
	
	int button_x_pos = 10;
	for (int i = 0; i < sorts_num; ++i)
	{
		sort_buttons[i].set_fill_color (sf::Color::Yellow);
		sort_buttons[i].set_text_color (sf::Color::Black);
		sort_buttons[i].set_position (sf::Vector2f(button_x_pos, Graph_y_pos + 50));
		button_x_pos += (Button_x_side + 10);
		buttons[i] = &sort_buttons[i];
	}

	const int buttons_num = sorts_num + 1;
	ClearButton clear_butt;
	clear_butt.set_fill_color (sf::Color::Yellow);
	clear_butt.set_text_color (sf::Color::Black);
	clear_butt.set_position (sf::Vector2f(5, Graph_y_pos + 20));
	buttons[sorts_num] = &clear_butt;

	while (window.isOpen ())
	{
		window.clear (sf::Color (255, 255, 255));

		for (int i = 0; i < buttons_num; ++i)
			buttons[i]->draw (window);

		sf::Event event;

		while (window.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
				window.close ();

			if (static_cast<int> (event.key.code) == static_cast<int> (sf::Mouse::Left))
			{
				sf::Vector2i mouse_pos = sf::Mouse::getPosition (window);
				
				if (event.type == sf::Event::MouseButtonPressed)
				{
					for (int i = 0; i < buttons_num; ++i)
					{
						if (buttons[i]->contains (mouse_pos.x, mouse_pos.y))
						{
							buttons[i]->action ();
							break;
						}
					}
				}
			}
		}

		window.display ();
	}


/*
	Global_font.loadFromFile (Text_format);
	sf::Text compares_title = sf::Text ("Compares",    Global_font, Text_size);
	sf::Text assigs_title   = sf::Text ("Assignments", Global_font, Text_size);
	compares_title.setFillColor (sf::Color::Black);
	assigs_title.setFillColor   (sf::Color::Black);
	compares_title.setPosition (Compares_graph_x_pos + 2, 5);
	assigs_title.setPosition   (Assigns_graph_x_pos + 2 , 5);

	sort_algorithm bubble    (bubble_sort,    sf::Color::Red,   "Bubble");
	sort_algorithm quick     (quick_sort,     sf::Color::Green, "Quick");
	sort_algorithm selection (selection_sort, sf::Color::Blue,  "Selection");
	sort_algorithm gnome     (gnome_sort,     sf::Color (0, 255, 255), "Gnome");

	sf::RenderWindow window(sf::VideoMode (Window_side, Window_side), "Sorts analizer");

	//=================
	// Temp realization
	const int sorts_num = 4;
	Button *buttons[5] = {};
	SortButton sort_buttons[sorts_num] = {
		SortButton (bubble_sort,    sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Bubble",    Global_font, Text_size), sf::Color (0, 0, 0)),
		SortButton (quick_sort,     sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Quick",     Global_font, Text_size), sf::Color (0, 0, 0)),
		SortButton (selection_sort, sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Selection", Global_font, Text_size), sf::Color (0, 0, 0)),
		SortButton (gnome_sort,     sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Gnome",     Global_font, Text_size), sf::Color (0, 0, 0))
	};
	
	int button_x_pos = 10;
	for (int i = 0; i < sorts_num; ++i)
	{
		sort_buttons[i].set_fill_color (sf::Color::Yellow);
		sort_buttons[i].set_text_color (sf::Color::Black);
		sort_buttons[i].set_position (sf::Vector2f(button_x_pos, Graph_y_pos + 50));
		button_x_pos += (Button_x_side + 10);
		buttons[i] = &sort_buttons[i];
	}

	const int buttons_num = sorts_num + 1;
	ClearButton clear_butt;
	clear_butt.set_fill_color (sf::Color::Yellow);
	clear_butt.set_text_color (sf::Color::Black);
	clear_butt.set_position (sf::Vector2f(5, Graph_y_pos + 20));
	buttons[sorts_num] = &clear_butt;
	// Temp realization
	//=================


	while (window.isOpen())
	{
		window.clear (sf::Color (255, 255, 255));

		bubble.compares_graph.draw_mouse_pos (window, 100, 500);
		bubble.assigns_graph.draw_mouse_pos  (window, 450, 500);

		bubble.button.draw    (window);
		quick.button.draw     (window);
		selection.button.draw (window);
		gnome.button.draw     (window);

		for (int i = 0; i < buttons_num; ++i)
			buttons[i]->draw (window);

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

			if (static_cast<int> (event.key.code) == static_cast<int> (sf::Mouse::Left))
			{
				sf::Vector2i mouse_pos = sf::Mouse::getPosition (window);
				
				if (event.type == sf::Event::MouseButtonPressed)
				{
					for (int i = 0; i < buttons_num; ++i)
					{
						if (buttons[i]->contains (mouse_pos.x, mouse_pos.y))
						{
							buttons[i]->action ();
							break;
						}
					}

					if (bubble.button.contains (mouse_pos.x, mouse_pos.y))
					{
						bubble.button.press ();
						if (!bubble.counted) count_sort_graph (bubble);
					}
					else if (quick.button.contains (mouse_pos.x, mouse_pos.y))
					{
						quick.button.press ();
						if (!quick.counted) count_sort_graph (quick);
					}
					else if (selection.button.contains (mouse_pos.x, mouse_pos.y))
					{
						selection.button.press ();
						if (!selection.counted) count_sort_graph (selection);
					}
					else if (gnome.button.contains (mouse_pos.x, mouse_pos.y))
					{
						gnome.button.press ();
						if (!gnome.counted) count_sort_graph (gnome);
					}
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
					if (bubble.button.contains (mouse_pos.x, mouse_pos.y))
						bubble.button.release ();
					else if (quick.button.contains (mouse_pos.x, mouse_pos.y))
						quick.button.release ();
					else if (selection.button.contains (mouse_pos.x, mouse_pos.y))
						selection.button.release ();
					else if (gnome.button.contains (mouse_pos.x, mouse_pos.y))
						gnome.button.release ();
				}
			}
		}

		window.display();
	}
 */
	return 0;
}