#include "Game.h"

Game::Game() : window(new sf::RenderWindow(sf::VideoMode(static_cast<unsigned>(windowWidth), static_cast<unsigned>(windowHeight))
	, "Tetris", sf::Style::Close)), drawer(window, &map, SQUARE_OFFSET), q("Quit", 15, sf::Color::Yellow, { 70, 50 }, sf::Color::Black),
	c("Cancel", 15, sf::Color::White, { 70, 50 }, sf::Color::Black), r("Retry", 15, sf::Color::Yellow, { 70, 50 }, sf::Color::Black) {
	srand(static_cast<unsigned>(time(nullptr)));
	currObj = map.spawn();
	gameState = GameState::Playing;
}

Game::Game(sf::RenderWindow& w) :
	SQUARE_SIZE((w.getSize().y / MAP_HEIGHT < w.getSize().x / MAP_WIDTH) ?
	(w.getSize().y * SQURE_TO_OFFSET_RATIO) / (MAP_HEIGHT * (SQURE_TO_OFFSET_RATIO + 1) + 1)
		: (w.getSize().x * SQURE_TO_OFFSET_RATIO) / (MAP_WIDTH * (SQURE_TO_OFFSET_RATIO + 1) + 1))
	, windowWidth(static_cast<float>(w.getSize().x)), windowHeight(static_cast<float>(w.getSize().y))
	, window(&w), drawer(window, &map, SQUARE_OFFSET), q("Quit", 15, sf::Color::Yellow, { 70, 50 }, sf::Color::Black),
	c("Cancel", 15, sf::Color::White, { 70, 50 }, sf::Color::Black), r("Retry", 15, sf::Color::Yellow, { 70, 50 }, sf::Color::Black) {
	selfGenerate = false;
	srand(static_cast<unsigned>(time(nullptr)));
	currObj = map.spawn();
	gameState = GameState::InMenu;
}

Game::~Game() {
	if (selfGenerate && window != nullptr) delete window;
}

void Game::playGame() {
	map.setSqsSize(SQUARE_SIZE);
	mPlayer.playOne("Tetris.ogg");

	//Set Window Settings
	//Makes it so key inputs are only processed once when held down
	window->setKeyRepeatEnabled(false);  //Certain inputs have special-case to check for held input
	window->setJoystickThreshold(DEFAULT_DEADZONE);
	window->setFramerateLimit(DEFAULT_FRAMERATE);

	//Set Fonts for Text
	q.setFont(drawer.getFont());
	c.setFont(drawer.getFont());
	r.setFont(drawer.getFont());

	while (window->isOpen()) {
		gameLoop();
	}
}

//Gameloop for continously running the game
void Game::gameLoop() {
	sf::Event evnt;
	switch (gameState) 	{
	case GameState::InMenu: {
		q.setPosition({ (windowWidth / 2) - 35, windowHeight - 55});
		// draw menu Once
		if (flag) {
			q.setBackColor(sf::Color::Black);
			q.setTxtColor(sf::Color::Yellow);
			q.drawTo(*window);
			drawer.drawMenu();
			window->display();
			flag = false;
		}
		// look for spacebar
		while (window->pollEvent(evnt)) {
			if (evnt.type == sf::Event::MouseMoved) {
				while (q.isMouseover(*window)) {
					q.setBackColor(sf::Color::White);
					q.setTxtColor(sf::Color::Black);
					q.drawTo(*window);
					drawer.drawMenu();
					window->display();
					if (q.isCliked(*window)) {
						window->close();
						break;
					}
				}
				flag = true;
			}
			if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Space) {
				gameState = GameState::GetUser;
				flag = true;
			}
			else if (evnt.type == sf::Event::Closed)
				window->close();
		}
		break;
	}
	case GameState::GetUser: {
		TextBox textB(30, sf::Color::White, true);
		textB.setFont(drawer.getFont());
		textB.setPosition(sf::Vector2f(0, windowHeight / 2));
		c.setPosition({ (windowWidth / 2) - 35, windowHeight - 55 });

		// gets user input
		while (gameState == GameState::GetUser) {
			drawer.drawUserMenu();
			textB.drawTo(*window);
			c.setTxtColor(sf::Color::White);
			c.setBackColor(sf::Color::Black);
			c.drawTo(*window);
			window->display();
			// looks for return key, otherwise displays user's input
			while (window->pollEvent(evnt)) {
				if (evnt.type == sf::Event::MouseMoved) {
					while (c.isMouseover(*window)) {
						c.setBackColor(sf::Color::White);
						c.setTxtColor(sf::Color::Black);
						c.drawTo(*window);
						window->display();
						if (c.isCliked(*window)) {
							window->clear();
							gameState = GameState::InMenu;
							break;
						}
					}
					flag = true;
				}
				if (evnt.type == sf::Event::KeyPressed &&
					(evnt.key.code == sf::Keyboard::Space || evnt.key.code == sf::Keyboard::Enter)) {
					flag = true;
					gameState = GameState::Playing;
					break;
				}
				else if (evnt.type == sf::Event::TextEntered) {
					textB.typeOn(evnt);
				}
				else if (evnt.type == sf::Event::Closed)
					window->close();
			}
		}
		// update based on input
		playerName = textB.getText();
		map.loadSaveFile(playerName);
		break;
	}
	case GameState::GameOver: {
		while (window->pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				window->close();
				break;
			}
		}
		break;
	}
	case GameState::Paused: {
		r.setPosition({windowWidth / 2 - 75, windowHeight / 2});
		q.setPosition({ windowWidth / 2, windowHeight / 2 });

		// Pause window
		if (flag) {
			q.setBackColor(sf::Color::Black);
			q.setTxtColor(sf::Color::Yellow);
			r.setBackColor(sf::Color::Black);
			r.setTxtColor(sf::Color::Yellow);
			r.drawTo(*window);
			q.drawTo(*window);
			drawer.drawPauseMenu();
			mPlayer.pauseMusic();
			window->display();
			flag = false;
		}
		while (window->pollEvent(evnt)) { // pause
			if (evnt.type == sf::Event::MouseMoved) {
				while (q.isMouseover(*window)) {
					q.setBackColor(sf::Color::White);
					q.setTxtColor(sf::Color::Black);
					q.drawTo(*window);
					window->display();
					if (q.isCliked(*window)) {
						map.removeSaveFile(playerName);
						mPlayer.continueMusic();
						gameState = GameState::InMenu;
						window->clear();
						break;
					}
				}
				while (r.isMouseover(*window)) {
					r.setBackColor(sf::Color::White);
					r.setTxtColor(sf::Color::Black);
					r.drawTo(*window);
					window->display();
					if (r.isCliked(*window)) {
						map.removeSaveFile(playerName);
						mPlayer.continueMusic();
						gameState = GameState::GetUser;
						window->clear();
						break;
					}
				}
				flag = true;
			} 
			else if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Escape) {
				mPlayer.continueMusic();
				flag = true;
				gameState = GameState::Playing;
			} 
			else if (evnt.type == sf::Event::JoystickButtonPressed) {
				currentJoystickID = evnt.joystickButton.joystickId;
				if (sf::Joystick::isButtonPressed(currentJoystickID, 7)) {
					mPlayer.continueMusic();
					flag = true;
					gameState = GameState::Playing;
				}
			} 
			else if (evnt.type == sf::Event::Closed)
				map.writeSaveFile(playerName, currObj);
		}
		break;
	}
	case GameState::Debug: 	{
		Debug dMenu(&map, currObj);
		int row, col;
		sf::Event evnt;
		// debug mode is on
		while (gameState == GameState::Debug) {
			// look for user input
			while (window->pollEvent(evnt)) {
				if (evnt.type == sf::Event::KeyPressed) {
					if (evnt.key.code == sf::Keyboard::Y) {
						gameState = GameState::Playing;
						break;
					} 
					else if (evnt.key.code == sf::Keyboard::P) {
						// get user Input
						GameObject* newObj;
						char input;
						cout << "Enter the first letter of the block in lower case: ";
						cin >> input;
						newObj = dMenu.spawn(input);
						if (newObj) {
							delete currObj;
							currObj = newObj;
							drawer.drawMap();
							window->display();
						}
					}
				} 
				else if (evnt.type == sf::Event::JoystickButtonPressed) {
					currentJoystickID = evnt.joystickButton.joystickId;
					if (sf::Joystick::isButtonPressed(currentJoystickID, 6)) {
						gameState = GameState::Playing;
						break;
					}
				}
				// move to cursor if it is pressed
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
					row = mousePos.y / (static_cast<int>(map.getSquareSize()) + static_cast<int>(SQUARE_OFFSET));
					col = mousePos.x / (static_cast<int>(map.getSquareSize()) + static_cast<int>(SQUARE_OFFSET));
					dMenu.moveBlock(row, col);
					drawer.drawMap();
					window->display();
				}
			}
		}
	}
	break;
	case GameState::Playing: {
		float eTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		dropTimer += eTime;
		while (window->pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window->close();
				map.writeSaveFile(playerName, currObj); //save current state to file
				break;
			case sf::Event::KeyPressed:
				checkForKeyInput(evnt.key.code); //get actions, inputs are only Read Once
				break;
			case sf::Event::KeyReleased:
				checkForReleaseKeyInput(evnt.key.code); //Used for DAS
				break;
			case sf::Event::JoystickButtonPressed:
				currentJoystickID = evnt.joystickButton.joystickId; //update Joystick ID
				//get button actions, Joystick inputs are only Read Once
				checkForJoyButtonInput(evnt.joystickButton.joystickId, evnt.joystickButton.button); 
				break;
			case sf::Event::JoystickMoved:
				currentJoystickID = evnt.joystickMove.joystickId;
				//get axis actions, Joystick inputs are only Read Once
				checkForJoyAxisMove(currentJoystickID, evnt.joystickMove.axis, evnt.joystickMove.position); 
				break;
			default:
				break;
			}
		}
		checkForHeldInput(); //Special-Case for held-down inputs
		if (delayingAutoShift) { //DAS is enabled, movement input is held down
			shiftTimer += eTime;
			if (shiftTimer >= DEFAULT_DAS_TIMER) {
				delayingAutoShift = false;
				shiftTimer = 0.0f;
			}
		} else if (isAutoShifting) { //Finished DAS, begin Auto Shifting, movement input is held down
			shiftTimer += eTime;
			if (shiftTimer >= DEFAULT_AS_TIMER) {
				shiftTimer = 0.0f;
				isAutoShifting = false;
			} else {
				dx = 0;
			}
		}
		if (gameState == GameState::Playing) {
			advanceGameState();
			//Update Screen
			if (gameState != GameState::GameOver) {
				window->clear();
				drawer.drawMap();
				drawer.drawScore(score);
				window->display();
			}
		}
	}
	break;
	}
}

void Game::checkForKeyInput(sf::Keyboard::Key keyInputted) {
	//Keyboard Inputs inside this function are only read once when held down
	switch (keyInputted) 
	{
	case sf::Keyboard::Escape: //Pausing
		gameState = GameState::Paused;
		break;
	case sf::Keyboard::Y: //Begins Debug Mode
		gameState = GameState::Debug;
		break;
	case sf::Keyboard::PageUp: //Volume Adjustment
		mPlayer.adjVolume(5);
		break;
	case sf::Keyboard::PageDown:
		mPlayer.adjVolume(-5);
		break;
	case sf::Keyboard::Space: //Tetris Hard Drop
		hardDropping = true;
		break;
	case sf::Keyboard::Up: //Rotate Clockwise
	case sf::Keyboard::X:
		map.rotate(currObj, true);
		break;
	case sf::Keyboard::LControl: //Rotate CounterClockwise
	case sf::Keyboard::RControl: 
	case sf::Keyboard::Z:
		map.rotate(currObj, false);
		break;
	case sf::Keyboard::Left: //Shift Left
		dx = -1;
		delayingAutoShift = true;
		break;
	case sf::Keyboard::Right: //Shift Right
		dx = 1;
		delayingAutoShift = true;
		break;
	}
}

void Game::checkForReleaseKeyInput(sf::Keyboard::Key keyReleased) {
	switch (keyReleased)
	{
	case sf::Keyboard::Left:
	case sf::Keyboard::Right:
		delayingAutoShift = false;
		shiftTimer = 0;
		break;
	}
}

void Game::checkForJoyButtonInput(unsigned int joystickID, unsigned int button) {
	//Joystick Inputs inside this function are only read once
	if (currentJoystickID == joystickID)
	{
		switch (button)
		{
		case 7: //pausing, 7 = start button
			gameState = GameState::Paused;
			break;
		case 6: //pausing, 6 = select button
			gameState = GameState::Debug;
			break;
		case 1: //rotate CW, 1 = B button,  3 = Y Button
		case 3:
			map.rotate(currObj, true);
			break;
		case 0: //rotate CCW, 0 = A button, 2 = X button,
		case 2:
			map.rotate(currObj, false);
			break;
		}
	}
}

void Game::checkForJoyAxisMove(unsigned int joystickID, sf::Joystick::Axis axis, float position) {
	//Joystick Inputs inside this function are only read once
	if (currentJoystickID == joystickID)
	{
		switch (axis)
		{
		case sf::Joystick::Axis::PovX:
			if (position < -DEFAULT_DEADZONE) //d-pad left
			{
				dx = -1;
				delayingAutoShift = true;
			}
			else if (position >= -DEFAULT_DEADZONE) //d-pad right
			{
				dx = 1;
				delayingAutoShift = true;
			}
			else if (position >= -DEFAULT_DEADZONE|| position <= DEFAULT_DEADZONE) { //d-pad neutral position
				delayingAutoShift = false;
				shiftTimer = 0;
			}
			break;
		case sf::Joystick::Axis::PovY:
			if (position > DEFAULT_DEADZONE) //d-pad up
				hardDropping = true;
			break;
		}
	}
}

void Game::checkForHeldInput() {
	//Held Down Inputs are continously read
	//Hard Drop
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		isFastFalling = true;
	}
	//Block Movement
	if (!delayingAutoShift && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (dx == 1)
			shiftTimer = 0;
		dx = -1;
		isAutoShifting = true;
	} 
	else if (!delayingAutoShift && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (dx == -1)
			shiftTimer = 0;
		dx = 1;
		isAutoShifting = true;
	}
	else if (sf::Joystick::isConnected(currentJoystickID)) { //Key Held Inputs Prioritized over Joystick Held Inputs
		if (sf::Joystick::getAxisPosition(currentJoystickID, sf::Joystick::Axis::PovY) < -DEFAULT_DEADZONE) { //d-pad down
			isFastFalling = true;
		}
		if (!delayingAutoShift && sf::Joystick::getAxisPosition(currentJoystickID, sf::Joystick::Axis::PovX) < -DEFAULT_DEADZONE) { //d-pad left
			dx = -1;
			isAutoShifting = true;
		}
		else if (!delayingAutoShift && sf::Joystick::getAxisPosition(currentJoystickID, sf::Joystick::Axis::PovX) > DEFAULT_DEADZONE) { //d-pad right
			dx = 1;
			isAutoShifting = true;
		}
	}
}

void Game::advanceGameState() {
	int oldScore = score;
	map.updateObj(currObj, 0, dx, score);
	if (isFastFalling) {
		delay /= 15;
	}

	//User inputted a "Hard Drop"
	if (hardDropping) {
		score += hardDrop();
		oldScore = score;
		if (score != oldScore) mPlayer.playTwo("Tetris_DX.ogg");
		delete currObj;
		try {
			currObj = map.spawn();//throw exception if cant spawn
		}
		catch (MapEx::GameOver end) {
			gameOverSequence(end);
		}
		//gravity
	} 
	
	//Block falls normally or fast depending on if Soft Drop input is held
	else if (dropTimer > delay) {
		if (isFastFalling) {
			score++;
		}
		if (!map.updateObj(currObj, +1, 0, score)) { //reached the bottom
			if (score != oldScore) 
				mPlayer.playTwo("Tetris_DX.ogg");
			delete currObj;
			try {
				currObj = map.spawn();//throw exception if cant spawn
			} 
			catch (MapEx::GameOver end) {
				gameOverSequence(end);
			}
		}
		dropTimer = 0;
	}
	//reset values
	dx = 0;
	isFastFalling = false;
	delay = DEFAULT_SPEED / static_cast<float>(score / 1000 + 1);
}

int Game::hardDrop() {
	int lineMoved = 0;
	int oldScore = score;
	while (map.updateObj(currObj, +1, 0, score)) 
		lineMoved++;
	if (score != oldScore) 
		mPlayer.playTwo("Tetris_DX.ogg");
	hardDropping = false;
	return lineMoved;
}

void Game::gameOverSequence(MapEx::GameOver &end)
{
	//Remove save file if it exists
	map.removeSaveFile(playerName);

	//Compute Scoreboard
	ScoreBoard board;
	board.deserializeFrom(scoreboardFileName);
	board.newPlayerScore(score, playerName);
	board.serializeTo(scoreboardFileName);

	//Draw Scoreboard and end Game
	end.display(*window, drawer, board);
	gameState = GameState::GameOver;
	mPlayer.playThree("Tetris_Jingle.ogg");
}
