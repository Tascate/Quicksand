#pragma once

#include <SFML/Graphics.hpp>
#include "ScoreBoard.h"
#include <cstdlib>
#include <string>

class GameMap;

class GameGraphics {
private:
	sf::RenderWindow* windowPtr;
	const GameMap* mapPtr;
	sf::Font gameFont;
    sf::Texture sand, bomb, background, boom, startingScreen, gold;
	float gameH, gameW, offset;
public:
    GameGraphics(sf::RenderWindow*, const GameMap*, float);
	void drawMenu();
	void drawUserMenu();
	void drawPauseMenu();
    void drawMap();
	void drawGameOver(const ScoreBoard&, int = 10);
	void drawScore(int);
	sf::Font& getFont(){return gameFont;}
};