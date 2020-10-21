class Button
{
private:
	sf::RectangleShape rectangle;
	sf::Text text;

public:
	Button (const sf::RectangleShape &_rectangle, const sf::Text &_text);

	void set_position (const sf::Vector2f &pos);

	void set_fill_color (const sf::Color &color);

	const sf::Color &get_fill_color () const;

	void set_text_color (const sf::Color &color);

	template <typename T>
	bool contains (T x, T y) const;

	bool contains (sf::Vector2f &coord) const;

	void draw (sf::RenderWindow &window) const;
	
	virtual void action ();
};