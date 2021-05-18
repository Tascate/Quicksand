#pragma once

#include <SFML/Graphics.hpp>
#include "ScoreBoard.h"
#include <cstdlib>
#include <string>

using namespace sf;

class GameMap;

class GameGraphics {
private:
	RenderWindow* windowPtr;
	const GameMap* mapPtr;
	Font gameFont;
    Texture sand, bomb, background, boom, startingScreen, gold;
	float gameH, gameW, offset;
public:
    GameGraphics(RenderWindow*, const GameMap*, float);
	void drawMenu();
	void drawUserMenu();
	void drawPauseMenu();
    void drawMap();
	void drawGameOver(const ScoreBoard&, int = 10);
	void drawScore(int);
	Font& getFont(){return gameFont;}
};