#pragma once

#include "Square.h"
#include "TetrisBlock.h"
#include "RandomBlock.h"
#include "Bomb.h"
#include <vector>
#include <fstream>
#include <cstdio>

using namespace std;

class GameMap {
private:
	std::vector< std::vector<Square*> > map;

	int mapHeight, mapWidth, spawnH;
	float squares_size = 35.0f;
	int colors[4] = {0,1,2,3};

	// helper functions
	void addSqAt(int, int, int);
	void removeSqAt(int, int);
	Square* getSqAt(int, int) const;
	bool haveSqAt(int, int) const;
	bool withIngBound(int, int) const;
	GameObject* generator(int, coords);

	bool shiftObj(GameObject*, int, int);
	void undoChanges(GameObject*, coords, int, int);
	int update();

public:
	GameMap(int = 20, int = 10, int = 4);
	~GameMap();

	GameObject* spawn();
	void rotate(GameObject*, bool);
	int updateObj(GameObject*, int, int, int&);

	bool loadSaveFile(string);
	bool writeSaveFile(string, GameObject*);
	void removeSaveFile(string);

	void setSqsSize(float);
	int getMapHeight()const { return mapHeight; }
	int getMapWidth()const { return mapWidth; }
	float getSquareSize()const{return squares_size;}

	// friends
	friend ofstream& operator<<(ofstream& out, const GameMap& m);
	friend ifstream& operator>>(ifstream& out, GameMap& m);
	friend class Debug;
	friend class GameGraphics;
};
