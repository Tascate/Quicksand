#include "RandomBlock.h"

void RandomBlock::updateBoundary(LL<coords>& frontier, LL<coords>& temp, bool* hash, coords buffer, int width, int height) {
	if (buffer.row > 0 && buffer.col > 0 && buffer.row < height && buffer.col < width) {
		if (hash[height*buffer.row + buffer.col] == false) {
			if (!frontier.find(buffer))
				frontier.add(buffer); // boundary can be expanded on
		}
	} else {
		temp.add(buffer); // fixed boundary
	}
}

RandomBlock::RandomBlock(int height, int width, int c, coords start, int numberOfSpawn) : GameObject(numberOfSpawn, c, start) {
	if (height * width < numberOfBlocks)			// if spawn area is too small
		throw BlockEx::InvalidSpawn(true, true, 4, numberOfBlocks / 4);

	// resize origin point so hash table is smaller & more efficient
	int rOffset = start.row - height / 2; 
	int cOffset = start.col - width / 2;
	start.row -= rOffset;
	start.col -= cOffset;

	bool* hash = new bool[static_cast<long long>(height)*width]; // indicates blocks not taken
	for (int i = 0; i < height * width; i++) {
		hash[i] = false;
	}
	LL<coords> temp;
	LL<coords> frontier;

	frontier.add(start);
	for (int i = 0; i < numberOfBlocks; i++) {
		// choose random block
		blockArea[i] = frontier.remove(rand() % (frontier.getSize()));
		start = blockArea[i];
		hash[height*start.row + start.col] = true;	// indicate block has been taken

		// checks if can expand on top, bottom, left, right blocks
		start.row -= 1;
		updateBoundary(frontier, temp, hash, start, width, height);
		start.row += 2;
		updateBoundary(frontier, temp, hash, start, width, height);
		start.row -= 1;
		start.col -= 1;
		updateBoundary(frontier, temp, hash, start, width, height);
		start.col += 2;
		updateBoundary(frontier, temp, hash, start, width, height);
	}
	// resize to original coordinates
	for (int i = 0; i < numberOfBlocks; i++) {
		blockArea[i].row += rOffset;
		blockArea[i].col += cOffset;
	}
	delete[] hash;
}