#include "Button.h"

Button::Button() {
	bText.setString("X");
	bText.setFillColor(sf::Color::Red);
	bText.setCharacterSize(12);

	hitbox.setSize({ 35,35 });
	hitbox.setFillColor(sf::Color::White);
}

Button::Button(std::string txt, unsigned fontSize, sf::Color txtColor, sf::Vector2f size, sf::Color bgColor) {
	bText.setString(txt);
	bText.setFillColor(txtColor);
	bText.setCharacterSize(fontSize);

	hitbox.setSize(size);
	hitbox.setFillColor(bgColor);
}

void Button::setPosition(sf::Vector2f pos) {
	hitbox.setPosition(pos);

	float xPos = pos.x + hitbox.getLocalBounds().width / 2 - bText.getLocalBounds().width / 2;
	float yPos = pos.y + hitbox.getLocalBounds().height / 2 - bText.getLocalBounds().height / 2;

	bText.setPosition({ xPos , yPos });
}

void Button::drawTo(sf::RenderWindow& window) {
	window.draw(hitbox);
	window.draw(bText);
}

bool Button::isMouseover(sf::RenderWindow& window) {
	float mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);
	float mouseY = static_cast<float>(sf::Mouse::getPosition(window).y);

	float btnPosX = hitbox.getPosition().x;
	float btnPosY = hitbox.getPosition().y;

	float btnXbound = btnPosX + hitbox.getLocalBounds().width;
	float btnYbound = btnPosY + hitbox.getLocalBounds().height;
	return (btnPosX <= mouseX && mouseX <= btnXbound) && (btnPosY <= mouseY && mouseY <= btnYbound);
}

sf::Vector2f Button::getPosition() {
	return hitbox.getPosition();
}

bool  Button::isCliked(sf::RenderWindow& window) {
	return isMouseover(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Button::setFont(sf::Font& f) { bText.setFont(f); }
void Button::setBackColor(sf::Color c) { hitbox.setFillColor(c); }
void Button::setTxtColor(sf::Color c) { bText.setFillColor(c); }
