#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

enum Special_Key {
	DELETE_KEY = 8,
	ENTER_KEY = 13,
	ESCAPE_KEY = 27
};

// This class is created following turtorial:
// https://www.youtube.com/watch?v=T31MoLJws4U

class TextBox {
private:
	sf::Text textbox;
	std::ostringstream textHolder;
	bool isSelected = false;
	bool hasLimit = false;
	unsigned limit = 0;

	void inputLogic(int cTyped);
	void deleteLastChar();
public:
	TextBox() {}
	TextBox(int size, sf::Color color, bool sel);

	void setFont(sf::Font& f) { textbox.setFont(f); }
	void setPosition(sf::Vector2f pos) { textbox.setPosition(pos); }
	void setLimit(bool t, int l = 0) {
		hasLimit = t;
		limit = l;
	}
	void setSelected(bool t);

	std::string getText() { return textHolder.str(); }
	void drawTo(sf::RenderWindow& window) { window.draw(textbox); }
	void typeOn(sf::Event& input);
};
