#include "TextBox.h"


TextBox::TextBox(int size, sf::Color color, bool sel)
{
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	isSelected = sel;

	if (isSelected)	{
		textbox.setString("_");
	} else {
		textbox.setString("");
	}
}

void TextBox::setSelected(bool t) {
	if (t && !isSelected)textbox.setString(textHolder.str() + "_");
	if (!t && isSelected)textbox.setString(textHolder.str());
	isSelected = t;
}

void TextBox::typeOn(sf::Event& input) {
	if (isSelected) {
		int charType = input.text.unicode;
		if (charType < 128) {
			if (hasLimit) {
				if (charType == DELETE_KEY || textHolder.str().length() < limit) {
					inputLogic(charType);
				}
			} else {
				inputLogic(charType);
			}
		}
	}
}

void TextBox::inputLogic(int cTyped) {
	if (cTyped != DELETE_KEY && cTyped != ENTER_KEY && cTyped != ESCAPE_KEY) {
		std::string copy = textHolder.str();
		copy += static_cast<char>(cTyped);
		textHolder.str("");
		textHolder.str(copy);
	} else if (cTyped == DELETE_KEY) {
		deleteLastChar();
	}
	textbox.setString(textHolder.str() + "_");
}

void TextBox::deleteLastChar() {
	if (textHolder.str().length() <= 0) 
		return;
	std::string ori = textHolder.str();
	std::string copy = "";
	for (unsigned i = 0; i < ori.length()-1; i++) {
		copy += ori[i];
	}
	textHolder.str("");
	textHolder.str(copy);
	textbox.setString(textHolder.str());
}