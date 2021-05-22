#include "Game.h"

int main() {
	unsigned sqW = 35;
	unsigned windowHeight = sqW*22;
	unsigned windowWidth = sqW * 10;
	
	sf::RenderWindow test(sf::VideoMode(windowWidth, windowHeight), "QuickSand", sf::Style::Close);
	Game game(test);
	game.playGame();
	return 0;
}


