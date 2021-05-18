#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

// This class is created following turtorial:
// https://www.youtube.com/watch?v=T31MoLJws4U
class Button {
private:
	sf::Text bText;
	sf::RectangleShape hitbox;
public:
	Button();
	Button(std::string txt, unsigned fontSize, sf::Color txtColor, sf::Vector2f size, sf::Color bgColor);

	void setPosition(sf::Vector2f pos);
	void setFont(sf::Font& f);
	void setBackColor(sf::Color c);
	void setTxtColor(sf::Color c);

	sf::Vector2f getPosition();
	void drawTo(sf::RenderWindow& window);
	bool isMouseover(sf::RenderWindow& window);
	bool isCliked(sf::RenderWindow& window);
};
