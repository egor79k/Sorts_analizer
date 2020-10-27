#include <iostream>
#include "include/button.hpp"


Button::Button (const sf::RectangleShape &_rectangle, const sf::Text &_text) :
	rectangle (_rectangle),
	text (_text)
{}


void Button::set_position (const sf::Vector2f &pos)
{
	rectangle.setPosition (pos);
	text.setPosition (pos.x + (rectangle.getSize ().x - text.getString ().getSize () * text.getCharacterSize () / 2) / 2, pos.y + 1);
}


void Button::set_fill_color (const sf::Color &color)
{
	rectangle.setFillColor (color);
}


const sf::Color &Button::get_fill_color () const
{
	return rectangle.getFillColor ();
}


void Button::set_text_color (const sf::Color &color)
{
	text.setFillColor (color);
}


bool Button::contains (int x, int y) const
{
	return rectangle.getGlobalBounds ().contains (x, y);
}


bool Button::contains (sf::Vector2f &coord) const
{
	return rectangle.getGlobalBounds ().contains (coord);
}


void Button::draw (sf::RenderWindow &window) const
{
	window.draw (rectangle);
	window.draw (text);
}


void Button::action ()
{
	printf ("Abstract Action\n");
}