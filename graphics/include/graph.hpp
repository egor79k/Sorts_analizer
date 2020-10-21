#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>

const char Default_text_format[] = "graphics/include/Crystal_Regular.ttf";
const int Default_text_size = 33;

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
	Graph (float x, float y, float x_sc = 1, float y_sc = 1, const sf::Color &col = sf::Color::Black);

	void add_point (float x, float y);

	void draw_mouse_pos (sf::RenderWindow &window, int x, int y);

	void draw (sf::RenderWindow &window) const;

	void clear ();
};

#endif