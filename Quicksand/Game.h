#pragma once

#include "GameMap.h"
#include "Debug.h"
#include "GameGraphics.h"
#include "MusicPlayer.h"
#include "TextBox.h"
#include "Button.h"
#include <string>
#include <iostream>

class Game {
private:
	enum class GameState {
		Paused,
		Playing,
		GameOver,
		InMenu,
		Debug,
		GetUser
	};
	GameState gameState;

	//WINDOW SETTINGS
	//the window size is based on square size and the width and height
	const float SQURE_TO_OFFSET_RATIO = 5.0f;
	const int MAP_HEIGHT = 22;
	const int MAP_WIDTH = 10;
	const float SQUARE_SIZE = 20.0f;
	const float DEFAULT_SPEED = 0.60f;
	const int DEFAULT_FRAMERATE = 60;
	bool flag = true;

	const float SQUARE_OFFSET = SQUARE_SIZE / SQURE_TO_OFFSET_RATIO;
	float windowWidth = (SQUARE_SIZE + SQUARE_OFFSET) * MAP_WIDTH + SQUARE_OFFSET;
	float windowHeight = (SQUARE_SIZE + SQUARE_OFFSET) * MAP_HEIGHT + SQUARE_OFFSET;

	bool selfGenerate = true;
	sf::RenderWindow* window = nullptr;

	//MAP Setting
	GameMap map = GameMap(MAP_HEIGHT, MAP_WIDTH);
	GameObject* currObj;

	//GAME PLAY Setings
	int score = 0;
	float dropTimer = 0.0f, delay = float(DEFAULT_SPEED), shiftTimer = 0.0f;
	const float DEFAULT_DAS_TIMER = 0.2f;
	const float DEFAULT_AS_TIMER = 0.05f;
	int dx = 0;
	sf::Clock clock;
	bool hardDropping = false, isFastFalling = false, delayingAutoShift = false, isAutoShifting = false;
	unsigned int currentJoystickID = 0;
	const float DEFAULT_DEADZONE = 15;

	//User Settings
	string playerName = "Unkown";
	string scoreboardFileName = "scoreboard.bin";
	

	//MUSIC Objects
	MusicPlayer mPlayer;

	// graphics
	GameGraphics drawer;
	Button q, c, r;
	// helper
	void gameLoop();
	void gameOverSequence(MapEx::GameOver &end);
	void advanceGameState();
	void checkForKeyInput(sf::Keyboard::Key);
	void checkForReleaseKeyInput(sf::Keyboard::Key);
	void checkForJoyButtonInput(unsigned int, unsigned int);
	void checkForJoyAxisMove(unsigned int, sf::Joystick::Axis, float);
	void checkForHeldInput();
	int hardDrop();
public:
	Game();
	Game(sf::RenderWindow& w);
	~Game();
	void playGame();
	int getScore() const{return score;}
};
