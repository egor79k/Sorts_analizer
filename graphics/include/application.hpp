#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "button.hpp"

class Application
{
private:
	sf::RenderWindow window;

	std::vector<Button *> buttons;
	
public:
	Application (int width, int height, const char *window_header);

	void run ();

	void add_button (Button *button);
};

#endif