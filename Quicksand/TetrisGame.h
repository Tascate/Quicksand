#pragma once

#include "gameMap.h"


class TetrisGame {
private:
    unsigned mapHeight, mapWidth;
    float squareSize;
    int difficulty;
public:
    TetrisGame(int h, int w, int sqSize, int diff = 0): mapHeight(h), mapWidth(w),
    squareSize(sqSize), difficulty(diff) {    }
};