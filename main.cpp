#include <iostream>
#include <SFML/Graphics.hpp>

const int Buttons_num = 4;


int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Sorts analizer");
	/*sf::RectangleShape buttons[Buttons_num] = {	sf::RectangleShape (sf::Vector2f (100, 30)),
												sf::RectangleShape (sf::Vector2f (100, 30)),
												sf::RectangleShape (sf::Vector2f (100, 30)),
												sf::RectangleShape (sf::Vector2f (100, 30)),};
*/
	sf::Font font;
	font.loadFromFile ("Country_Western_Regular.ttf");
	sf::Text text ("Bubble", font, 20);
	text.setColor (sf::Color::Red);
	
	while (window.isOpen())
	{
		window.clear (sf::Color (255, 255, 255));
		window.draw (text);
/*
		sf::RectangleShape button_1 (sf::Vector2f (100, 30));
		button_1.setPosition (50, 400);
		button_1.setFillColor (sf::Color (0, 255, 0));
		window.draw (button_1);
*/

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