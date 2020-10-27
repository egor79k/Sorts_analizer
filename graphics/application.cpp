#include "include/application.hpp"


Application::Application (int width, int height, const char *window_header) :
	window(sf::VideoMode (width, height), window_header)
{}

	
void Application::run ()
{
	while (window.isOpen ())
	{
		window.clear (sf::Color (255, 255, 255));

		for (int i = 0; i < buttons.size (); ++i)
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
					for (int i = 0; i < buttons.size (); ++i)
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
}


void Application::add_button (Button *button)
{
	buttons.push_back (button);
}