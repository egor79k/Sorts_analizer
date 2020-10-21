#include "include/graph.hpp"


Graph::Graph (float x, float y, float x_sc, float y_sc, const sf::Color &col) :
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


void Graph::add_point (float x, float y)
{
	graph.append (sf::Vector2f (x_pos + x / x_scale, y_pos - y / y_scale));
	if (graph[points_num].position.x > max_x) max_x = graph[points_num].position.x;
	if (graph[points_num].position.y < max_y) max_y = graph[points_num].position.y;
	if (graph[points_num].position.x < min_x) min_x = graph[points_num].position.x;
	if (graph[points_num].position.y > min_y) min_y = graph[points_num].position.y;
	graph[points_num].color = color;
	++points_num;
}


void Graph::draw_mouse_pos (sf::RenderWindow &window, int x, int y)
{
	sf::Vector2i graph_coord = sf::Mouse::getPosition (window);
		if ( min_x < graph_coord.x && graph_coord.x < max_x && max_y < graph_coord.y && graph_coord.y < min_y)
	{
		graph_coord.x -= x_pos;
		graph_coord.y = y_pos - graph_coord.y;
		graph_coord.x *= x_scale;
		graph_coord.y *= y_scale;

		sf::Font font;
		font.loadFromFile (Default_text_format);
		sf::Text coord_pair = sf::Text (std::to_string (graph_coord.x) + " ; " + std::to_string (graph_coord.y), font, Default_text_size);
		coord_pair.setFillColor (sf::Color::Black);
		coord_pair.setPosition (x, y);
		window.draw (coord_pair);
	}
}


void Graph::draw (sf::RenderWindow &window) const
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


void Graph::clear ()
{
	graph.clear ();
}