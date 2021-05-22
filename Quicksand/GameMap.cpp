#include "GameMap.h"

GameMap::GameMap(int height, int width, int sh) :
	mapHeight(height), mapWidth(width), spawnH(sh) {
	map = std::vector<std::vector<Square*> >(mapHeight);
	for (int i = 0; i < mapHeight; i++) {
		map[i] = std::vector<Square*>(mapWidth);
		for (int k = 0; k < mapWidth; k++) {
			map[i][k] = nullptr;
		}
	}
}

GameMap::~GameMap() {
	for (int i = mapHeight - 1; i >= 0; i--) {
		for (int j = mapWidth - 1; j >= 0; j--) {
			delete map[i][j];
		}
	}
}

void GameMap::undoChanges(GameObject* ptr, coords stopped, int rowU, int colU) {
	// clean up mess
	coords* coordP = ptr->getCoords(0);
	for (int i = 1; *coordP != stopped ; i++) {
		if(haveSqAt(coordP->row, coordP->col))
			removeSqAt(coordP->row, coordP->col);
		else
			addSqAt(coordP->row, coordP->col, ptr->getType());
		coordP = ptr->getCoords(i);
	}

	// undo changes on GameObject* ptr
	coords invUpdate;
	invUpdate.row = -1*rowU;
	invUpdate.col = -1*colU;
	ptr->shift(invUpdate.row, invUpdate.col);

	// undo changes to map
	coordP = ptr->getCoords(0);
	for (int i = 1; coordP != nullptr; i++) {
		addSqAt(coordP->row, coordP->col, ptr->getType());
		coordP = ptr->getCoords(i);
	}
}

bool GameMap::shiftObj(GameObject* ptr, int rowU, int colU) {
	try {
		// remove Obj
		coords* coordP = ptr->getCoords(0);
		for (int i = 1; coordP != nullptr; i++) {
			removeSqAt(coordP->row, coordP->col);	// throws out of bounds
			coordP = ptr->getCoords(i);
		}
		ptr->shift(rowU, colU);
		// copy new Obj onto board
		coordP = ptr->getCoords(0);
		for (int i = 1; coordP != nullptr; i++) {
			addSqAt(coordP->row, coordP->col, ptr->getType()); // throws outofB & InvalidOp
			coordP = ptr->getCoords(i);
		}
		return true;
	} catch (const MapEx::OutOfBounds& out) {
		coords stopped;
		stopped.row = out.getRow();
		stopped.col = out.getCol();
		undoChanges(ptr, stopped, rowU, colU);
	} catch(const MapEx::InvalidOperation& badSq) {
		coords stopped;
		stopped.row = badSq.getRow();
		stopped.col = badSq.getCol();
		undoChanges(ptr, stopped, rowU, colU);
	}
	return false;
}

GameObject* GameMap::generator(int i, coords spawnPoint) {
	switch (i) {
		case 1:
			return new RandomBlock(spawnH, mapWidth, colors[rand() % 4], spawnPoint);
		case 2:
			return new Bomb(spawnH, mapWidth, spawnPoint);
		default:
			return new TetrisBlock(spawnH, mapWidth, colors[rand() % 4], spawnPoint);
	}
}

GameObject* GameMap::spawn() {
	// check if anything is in the spawn
	for (int i = 0; i < spawnH; i++) {
		for (int j = 0; j < mapWidth; j++) {
			if (haveSqAt(i, j)) {
				throw MapEx::GameOver();
			}
		}
	}
	coords spawnPoint;
	spawnPoint.row = spawnH / 2;
	spawnPoint.col = mapWidth / 2;
	GameObject* temp;
	try {
		temp = generator(rand() % 10 + 1, spawnPoint);
	} catch (BlockEx::InvalidSpawn badSpawn) {
		// reset map to fit block
		if (badSpawn.hasHeightIssue())
			spawnH = badSpawn.recommendHeight() + 1;
		if (badSpawn.hasWidthIssue())
			mapWidth = badSpawn.recommendWidth() + 1;
		spawnPoint.col = mapWidth / 2;
		spawnPoint.row = mapHeight / 2;

		temp = generator(rand() % 6 + 1, spawnPoint);
	}
	// draw block onto map
	coords* coordP = temp->getCoords(0);
	for (int i = 1; coordP != nullptr; i++) {
		addSqAt(coordP->row, coordP->col, temp->getType());
		coordP = temp->getCoords(i);
	}
	return temp;
}

int GameMap::updateObj(GameObject* obj, int rowU, int colU, int& score) {
	if (shiftObj(obj, rowU, colU))
		return true; // able to move
	if (rowU != 0){
		if (Bomb* bPtr = dynamic_cast<Bomb*>(obj)) {
			coords* ptr = bPtr->getExplosion(0);
			for (int i = 1; ptr != nullptr; i++) {
				if (withIngBound(ptr->row, ptr->col) && haveSqAt(ptr->row, ptr->col))
					removeSqAt(ptr->row, ptr->col);
				ptr = bPtr->getExplosion(i);
			}
			score += 10; // fixed rate
		} else {
			score += update()*10;
		}
	}
	return false; // block has reached the end of its lifespan, unable to move
}

int GameMap::update() {
	bool isFull;
	int sum = 0;
	// holder of empty rows
	bool* emptyRow = new bool[mapHeight];
	for (int i = 0; i < mapHeight; i++) emptyRow[i] = false;
	// establish empty rows
	for (int i = 0; i < mapHeight; i++) { 
		isFull = true;
		for (int j = 0; j < mapWidth; j++) {
			if (!haveSqAt(i, j)) {
				isFull = false;
				break;
			}
		}
		if (isFull) {
			emptyRow[i] = true;
			for (int j = 0; j < mapWidth; j++) {
				removeSqAt(i, j);
			}
			sum += mapWidth;
		}
	}
	// find first non - empty row
	int startI = 0;
	for (int i = 0; i < mapHeight; i++) {
		if (emptyRow[i] == false) {
			startI = i;
			break;
		}
	}
	// search for empty row top to bottom
	for (int emptyI = startI; emptyI < mapHeight; emptyI++) {
		if (emptyRow[emptyI]) {
			// shift down to fill empty row bottom to top
			for (int i = emptyI; i > startI; i--) {
				for (int j = 0; j < mapWidth; j++) {
					map[i][j] = map[static_cast<long long>(i) - 1][j];
				}
			}
		}
	}
	delete[] emptyRow;
	return sum;
}

void GameMap::rotate(GameObject* obj, bool rotateCW) {
	// clear current obj
	coords* coordP = obj->getCoords(0);
	for (int i = 1; coordP != nullptr; i++) {
		removeSqAt(coordP->row, coordP->col);
		coordP = obj->getCoords(i);
	}
	// rotate
	if (rotateCW)
		obj->rotateCW();
	else
		obj->rotateCCW();
	coordP = obj->getCoords(0);
	// check if rotated obj is valid
	for (int i = 1; coordP != nullptr; i++) {
		if (!withIngBound(coordP->row, coordP->col) || haveSqAt(coordP->row, coordP->col)) {
			obj->rotateCW();
			obj->rotateCW();
			obj->rotateCW();
			break;
		}
		coordP = obj->getCoords(i);
	}
	// update obj
	shiftObj(obj, 0, 0);
}

bool GameMap::haveSqAt(int row, int col) const {
	if (!withIngBound(row, col)) throw MapEx::OutOfBounds(row, col);
	return !(map[row][col] == nullptr);
}

Square* GameMap::getSqAt(int row, int col) const {
	if (!withIngBound(row, col)) throw MapEx::OutOfBounds(row, col);
	return map[row][col];
}

void GameMap::addSqAt(int row, int col, int color) {
	if (withIngBound(row, col)) {
		if (haveSqAt(row, col))
			throw  MapEx::InvalidOperation(row, col);
		Square* newSQ = new Square(row, col, squares_size, color);
		map[row][col] = newSQ;
	} else {
		throw MapEx::OutOfBounds(row, col);
	}
}

void GameMap::removeSqAt(int row, int col) {
	if (map[row][col] != nullptr) {
		delete map[row][col];
		map[row][col] = nullptr;
	}
}

void GameMap::setSqsSize(float newSize) {
	squares_size = newSize;
	for (int i = 0; i < mapHeight; i++) {
		for (int k = 0; k < mapWidth; k++) {
			if (map[i][k] != nullptr)map[i][k]->setSize(newSize);
		}
	}
}

bool GameMap::withIngBound(int row, int col) const {
	return !(col < 0 || col >= mapWidth || row < 0 || row >= mapHeight);
}

bool GameMap::loadSaveFile(string user) {
	ifstream svFile(user + ".bin", ios::binary);
	if (!svFile)
		return false;
	svFile >> *this;
	svFile.close();
	return true;
}

bool GameMap::writeSaveFile(string user, GameObject* ptr) {
	ofstream fout(user + ".bin", ios::binary);
	if (!fout)
		return false;
	coords* temp = ptr->getCoords(0);
	for (int i = 1; temp != nullptr; i++) {
		if (withIngBound(temp->row, temp->col))
			removeSqAt(temp->row, temp->col);
		temp = ptr->getCoords(i);
	}
	fout << *this;
	fout.close();
	return true;
}

void GameMap::removeSaveFile(string user) {
	user += ".bin";
	const char* buffer = user.c_str();
	remove(buffer);
}

ofstream& operator<<(ofstream& fout, const GameMap& m) {
	fout.write(reinterpret_cast<const char*>(&m.mapHeight), sizeof(m.mapHeight));
	fout.write(reinterpret_cast<const char*>(&m.mapWidth), sizeof(m.mapWidth));
	fout.write(reinterpret_cast<const char*>(&m.spawnH), sizeof(m.spawnH));
	for (int i = 0; i < m.mapHeight; i++) {
		for (int j = 0; j < m.mapWidth; j++) {
			if (m.map[i][j] != nullptr)
				fout.write(reinterpret_cast<const char*>(m.map[i][j]), sizeof(Square));
		}
	}
	return fout;
}

ifstream& operator>>(ifstream& fin, GameMap& m) {
	fin.read(reinterpret_cast<char*>(&m.mapHeight), sizeof(m.mapHeight));
	fin.read(reinterpret_cast<char*>(&m.mapWidth), sizeof(m.mapWidth));
	fin.read(reinterpret_cast<char*>(&m.spawnH), sizeof(m.spawnH));
	Square temp;
	while (fin.read(reinterpret_cast<char*>(&temp), sizeof(Square))) {
		m.map[temp.getRow()][temp.getCol()] = new Square(temp);
	}
	return fin;
}