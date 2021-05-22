#include "GameGraphics.h"
#include "GameMap.h"

GameGraphics::GameGraphics(sf::RenderWindow* wP, const GameMap* mP, float off):
windowPtr(wP), mapPtr(mP), gameH(static_cast<float>(wP->getSize().y)), gameW(static_cast<float>(wP->getSize().x)), offset(off) {
	// load in neccessary textures
    sand.loadFromFile("Texture/sand.png");
    bomb.loadFromFile("Texture/bomb.png");
    background.loadFromFile("Texture/background.png");
    boom.loadFromFile("Texture/boom.png");
    gold.loadFromFile("Texture/Gold.png");
    gameFont.loadFromFile("Font/minercraftory.regular.ttf");
}

void GameGraphics::drawMap() {
	sf::RectangleShape back(sf::Vector2f(gameW, gameH));
	back.setTexture(&background);
	windowPtr->draw(back);
	sf::RectangleShape goldSquare(sf::Vector2f(mapPtr->squares_size, mapPtr->squares_size));
	goldSquare.setTexture(&gold);
	goldSquare.setFillColor(sf::Color::Yellow);
	for (int k = 0; k < mapPtr->getMapWidth(); k++) {
		//Gold is not drawn if an block is placed over it
		
		int goldHeight = mapPtr->spawnH;
		if (!mapPtr->haveSqAt(goldHeight, k)) {
			float xPos = offset + (mapPtr->squares_size + offset) * k;
			float yPos = offset + (mapPtr->squares_size + offset) * goldHeight;
			goldSquare.setPosition(xPos, yPos);
			windowPtr->draw(goldSquare);
		}
	}
    for (int i = 0; i < mapPtr->getMapHeight(); i++)
	{
		// color in blocks
		for (int k = 0; k < mapPtr->getMapWidth(); k++) {
			if (mapPtr->haveSqAt(i, k)) {
				sf::RectangleShape temp(sf::Vector2f(mapPtr->squares_size, mapPtr->squares_size));
				temp.setOutlineColor(sf::Color::Black);
				temp.setOutlineThickness(offset);
				switch (mapPtr->map[i][k]->getColor()) {
				case 0:
					temp.setTexture(&sand);
					break;
				case 1:
					temp.setTexture(&sand);
					temp.setFillColor(sf::Color(242, 106, 51));
					break;
				case 2:
					temp.setTexture(&sand);
					temp.setFillColor(sf::Color(163, 127, 42));
					break;
				case 3:
					temp.setTexture(&sand);
					temp.setFillColor(sf::Color(108, 129, 161));
					break;
				case 6: // bomb texture exploding
					temp.setTexture(&boom);
					break;
				case 7: // bomb real texture
					temp.setTexture(&bomb);
					break;
				}
				float xPos = offset + (mapPtr->squares_size + offset) * k;
				float yPos = offset + (mapPtr->squares_size + offset) * i;
				temp.setPosition(xPos, yPos);
				windowPtr->draw(temp);
			}
		}
	}
}

void GameGraphics::drawPauseMenu() {
	sf::Text pause("PAUSED", gameFont, 30);
	pause.setFillColor(sf::Color::Red);
	pause.setPosition(0,gameH - 40);
    windowPtr->draw(pause);
}

void GameGraphics::drawMenu() {
	// rules, tips
	sf::RectangleShape img(sf::Vector2f(gameW, gameH - 60));
	img.setTexture(&background);
	windowPtr->draw(img);

	// game name
	sf::Text text("QuickSand!", gameFont, 50);
	sf::Text text2("Press Space to Begin", gameFont, 25);
	text2.setPosition(5, 650);
	text.setFillColor(sf::Color::Yellow);
	text2.setFillColor(sf::Color::Yellow);
	windowPtr->draw(text);
	windowPtr->draw(text2);
}

void GameGraphics::drawGameOver(const ScoreBoard& board, int displayNumber) {
	// display game over message
	sf::Text gg("GAME OVER", gameFont, static_cast<unsigned>(mapPtr->squares_size));
    gg.setFillColor(sf::Color::Yellow);
    gg.setStyle(sf::Text::Bold);
	windowPtr->draw(gg);
	// display scoreboard
    const multimap<int, string> b = board.getBoard();
    auto it = b.crbegin();
    float height = (windowPtr->getSize().y - mapPtr->squares_size)/(displayNumber);
	sf::Text text;
    text.setFont(gameFont);
    text.setCharacterSize(20);
    string buffer;
    for(int i = 0; i < displayNumber && it != b.crend(); i++) {
        buffer = "Number " + to_string(i + 1);
        buffer += "    " + to_string(it->first) + " " + it->second;
        text.setString(buffer);
        text.setPosition(0, i*(height+5) + mapPtr->squares_size);
        windowPtr->draw(text);
        it++;
    }
}

void GameGraphics::drawScore(int s) {
	sf::Text scoreText;
    scoreText.setString(to_string(s));
	scoreText.setFont(gameFont);
	scoreText.setCharacterSize(static_cast<unsigned>(mapPtr->squares_size));
    scoreText.setPosition(mapPtr->squares_size, mapPtr->squares_size);
    windowPtr->draw(scoreText);
}

void GameGraphics::drawUserMenu() {
	sf::RectangleShape back(sf::Vector2f(gameW, gameH));
	back.setTexture(&background);
	windowPtr->draw(back);
	sf::Text instruc("Please Enter A UserName: ", gameFont, 20);
	instruc.setPosition(0,40);
	windowPtr->draw(instruc);
}