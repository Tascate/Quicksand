#include "TetrisBlock.h"

//I shape = 0
//Square shape = 1
//L shape = 2
//T shape = 3
//J shape = 4
//S shape = 5
//Z shape = 6
TetrisBlock::TetrisBlock(int height, int width, int c, coords start) : GameObject(4, c, start) {
	if (height < 4 || width < 4)
		throw BlockEx::InvalidSpawn(height < 4, width < 4, 4, 10); // default spawn width & height
	numberOfBlocks = 4;
	int shape = rand() % 7;
	switch (shape) {
	case 0: // -------
		//I shape
		blockArea[0].row = start.row; blockArea[0].col = start.col;
		blockArea[1].row = start.row; blockArea[1].col = start.col - 1;
		blockArea[2].row = start.row; blockArea[2].col = start.col - 2;
		blockArea[3].row = start.row; blockArea[3].col = start.col + 1;
		break;
	case 1:
		// square shape
		blockArea[0].row = start.row; blockArea[0].col = start.col;
		blockArea[1].row = start.row - 1; blockArea[1].col = start.col - 1;
		blockArea[2].row = start.row - 1; blockArea[2].col = start.col;
		blockArea[3].row = start.row; blockArea[3].col = start.col - 1;
		break;
	case 2:
		//L shape
		blockArea[0].row = start.row; blockArea[0].col = start.col;
		blockArea[1].row = start.row - 1; blockArea[1].col = start.col;
		blockArea[2].row = start.row + 1; blockArea[2].col = start.col;
		blockArea[3].row = start.row + 1; blockArea[3].col = start.col + 1;
		break;
	case 3:
		//T shape
		blockArea[0].row = start.row; blockArea[0].col = start.col;
		blockArea[1].row = start.row; blockArea[1].col = start.col - 1;
		blockArea[2].row = start.row; blockArea[2].col = start.col + 1;
		blockArea[3].row = start.row - 1; blockArea[3].col = start.col;
		break;
	case 4:
		//J shape
		blockArea[0].row = start.row; blockArea[0].col = start.col;
		blockArea[1].row = start.row - 1; blockArea[1].col = start.col;
		blockArea[2].row = start.row + 1; blockArea[2].col = start.col;
		blockArea[3].row = start.row + 1; blockArea[3].col = start.col - 1;
		break;
	case 5:
		// S shape
		blockArea[0].row = start.row; blockArea[0].col = start.col;
		blockArea[1].row = start.row; blockArea[1].col = start.col - 1;
		blockArea[2].row = start.row - 1; blockArea[2].col = start.col;
		blockArea[3].row = start.row - 1; blockArea[3].col = start.col + 1;
		break;
	case 6:
		// Z shape
		blockArea[0].row = start.row; blockArea[0].col = start.col;
		blockArea[1].row = start.row; blockArea[1].col = start.col - 1;
		blockArea[2].row = start.row + 1; blockArea[2].col = start.col;
		blockArea[3].row = start.row + 1; blockArea[3].col = start.col + 1;
		break;
	default:
		// square shape
		blockArea[0].row = start.row; blockArea[0].col = start.col;
		blockArea[1].row = start.row - 1; blockArea[1].col = start.col - 1;
		blockArea[2].row = start.row - 1; blockArea[2].col = start.col;
		blockArea[3].row = start.row; blockArea[3].col = start.col - 1;
		break;
	}
}