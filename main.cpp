#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "sorting_algorithms.cpp"
#include "type_wrapper.cpp"
#include "graphics/include/application.hpp"
#include "graphics/include/button.hpp"
#include "graphics/include/graph.hpp"


sf::Font Global_font;
const char Text_format[] = "graphics/include/Crystal_Regular.ttf";
const char Window_name[] = "Sorts analizer";
const int Window_side = 700;
const int Compares_graph_x_pos = 5;
const int Assigns_graph_x_pos  = 350;
const int Graph_y_pos = 500;
const int Rand_seed = 345234;
const int Button_x_side = 150;
const int Button_y_side = 70;
const int Text_size = 33;
const int Iterations = 1000;
const int Graph_length = 333;
const int Iter_step = 50;


sort_counter<int> *random_fill (sort_counter<int> *arr, size_t size)
{
	srand (Rand_seed);

	for (int i = 0; i < size; ++i)
		arr[i] = sort_counter<int> (rand () % RAND_MAX);

<<<<<<< HEAD
class Graph
=======
	return arr;
}


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
		if (counted)
			return;

		//printf ("Sort Action\n");
		for (int i = Iter_step; i < Iterations; i += Iter_step)
		{
			sort_counter<int> *array = random_fill (new sort_counter<int>[i], i);
			sort_counter<int>::reset ();
			sort (array, i);
			delete[] array;
			compares_graph.add_point (i, sort_counter<int>::compares ());
			assigns_graph.add_point  (i, sort_counter<int>::assigns ());
			//printf("size: %d, comps: %d, assigns: %d\n", i, sort_counter<int>::compares (), sort_counter<int>::assigns ());
		}
		
		counted = true;
	}

	void draw (sf::RenderWindow &window) const
	{
		Button::draw (window);
		if (counted)
		{
			compares_graph.draw (window);
			assigns_graph.draw  (window);
		}
	}
	
	void press ()
	{
		set_fill_color (get_fill_color () - Color_diff);
	}

	void release ()
	{
		set_fill_color (get_fill_color () + Color_diff);
	}

	void clear ()
	{
		compares_graph.clear ();
		assigns_graph.clear ();
		counted = false;
	}
};



class ClearButton : public Button
>>>>>>> d44d33ee459ba9a1eb3af61f0abddfcd508598d7
{
private:
	std::vector<SortButton *> sort_buttons;
public:
	ClearButton (std::vector<SortButton *> &buttons) :
		Button (sf::RectangleShape (sf::Vector2f (50, 50)), sf::Text ("X", Global_font, 40)),
		sort_buttons (buttons)
	{}

	void action ()
	{
		//printf ("Clear Action\n");
		for (int i = 0; i < sort_buttons.size (); ++i)
			sort_buttons[i]->clear ();
	}

	void clear ()
	{
		graph.clear ();
	}
};



//==========
// Abstract class of default rectangle button with text
//==========
class AbstractButton
{
private:
	sf::RectangleShape rectangle;
	sf::Text text;

public:
	AbstractButton (const sf::RectangleShape &_rectangle, const sf::Text &_text) :
		rectangle (_rectangle),
		text (_text)
	{}

	virtual ~AbstractButton () = 0;

	void set_position (const sf::Vector2f &pos)
	{
		rectangle.setPosition (pos);
		text.setPosition (pos.x + (rectangle.getSize ().x - text.getString ().getSize () * text.getCharacterSize () / 2) / 2, pos.y + 1);
	}

	void set_fill_color (const sf::Color &color)
	{
		rectangle.setFillColor (color);
	}

	const sf::Color &get_fill_color () const
	{
		return rectangle.getFillColor ();
	}

	void set_text_color (const sf::Color &color)
	{
		text.setFillColor (color);
	}

	template <typename T>
	bool contains (T x, T y) const
	{
		return rectangle.getGlobalBounds ().contains (x, y);
	}

	bool contains (sf::Vector2f &coord) const
	{
		return rectangle.getGlobalBounds ().contains (coord);
	}

	void draw (sf::RenderWindow &window) const
	{
		window.draw (rectangle);
		window.draw (text);
	}

	virtual void action () {printf ("Abstract Action\n");}
};

AbstractButton::~AbstractButton () {}



class SortButton : public AbstractButton
{
private:
	typedef void(*sort_function_ptr)(sort_counter<int>*,size_t);
	bool counted = false;
	sort_function_ptr sort;
	//Graph compares_graph;
	//Graph assigns_graph;
	const sf::Color Color_diff;

public:
	SortButton (sort_function_ptr _sort, const sf::Vector2f &size, const sf::Text &_text, const sf::Color &color_diff) :
		AbstractButton (sf::RectangleShape (size), _text),
		sort (_sort),
		Color_diff (color_diff)
		//compares_graph (Graph (Compares_graph_x_pos, Graph_y_pos, Iterations / Graph_length, (Iterations * Iterations) / (Graph_y_pos * 3), color)),
		//assigns_graph  (Graph (Assigns_graph_x_pos,  Graph_y_pos, Iterations / Graph_length, (Iterations * Iterations) / (Graph_y_pos * 3), color))
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



class ClearButton : public AbstractButton
{
public:
	ClearButton () :
		AbstractButton (sf::RectangleShape (sf::Vector2f (50, 50)), sf::Text ("X", Global_font, 40))
	{}

	void action ()
	{
		printf ("Clear Action\n");
	}
};


/*
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
*/


int main()
{
	Application sorts_analizer (Window_side, Window_side, Window_name);

	const int sorts_num = 4;
	SortButton sort_buttons[sorts_num] = {
		SortButton (bubble_sort,    sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Bubble",    Global_font, Text_size), sf::Color (0, 0, 0)),
		SortButton (quick_sort,     sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Quick",     Global_font, Text_size), sf::Color (0, 0, 0)),
		SortButton (selection_sort, sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Selection", Global_font, Text_size), sf::Color (0, 0, 0)),
		SortButton (gnome_sort,     sf::Vector2f (Button_x_side, Button_y_side), sf::Text ("Gnome",     Global_font, Text_size), sf::Color (0, 0, 0))
	};
	
	std::vector<SortButton *> clearable_buttons;
	int button_x_pos = 10;
	for (int i = 0; i < sorts_num; ++i)
	{
		sort_buttons[i].set_fill_color (sf::Color::Yellow);
		sort_buttons[i].set_text_color (sf::Color::Black);
		sort_buttons[i].set_position (sf::Vector2f(button_x_pos, Graph_y_pos + 50));
		button_x_pos += (Button_x_side + 10);
		sorts_analizer.add_button (&sort_buttons[i]);
		clearable_buttons.push_back (&sort_buttons[i]);
	}

	ClearButton clear_butt (clearable_buttons);
	clear_butt.set_fill_color (sf::Color::Yellow);
	clear_butt.set_text_color (sf::Color::Black);
	clear_butt.set_position (sf::Vector2f(5, Graph_y_pos + 20));
	sorts_analizer.add_button (&clear_butt);

	sorts_analizer.run ();

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
<<<<<<< HEAD
	AbstractButton *buttons[5] = {};
=======
	Button *buttons[5] = {};
>>>>>>> d44d33ee459ba9a1eb3af61f0abddfcd508598d7
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