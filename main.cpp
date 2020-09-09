#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Sorts analizer");

	int color = 0;
	
	while (window.isOpen())
	{
		window.clear (sf::Color (255, 255, 255));

		sf::Vector2i mouse_pos = sf::Mouse::getPosition (window);

		sf::RectangleShape button_1 (sf::Vector2f (100, 30));
		button_1.setPosition (50, 400);
		button_1.setFillColor (sf::Color (0, 255, 0));
		window.draw (button_1);


		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && static_cast<int> (event.key.code) == static_cast<int> (sf::Mouse::Left))
			{
				if (button_1.getGlobalBounds ().contains (mouse_pos.x, mouse_pos.y))
					std::cout << "Button pressed!\n";
				//color = (color + 10) % 255;
			}
		}

		window.display();
	}
 
	return 0;
}