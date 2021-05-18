#pragma once

#include "GameObject.h"
#include "CustomExceptions.h"
#include <cstdlib>

using namespace std;

class TetrisBlock : public GameObject {
public:
    TetrisBlock() = delete;
    TetrisBlock(int height, int width, int c, coords start);
    ~TetrisBlock() = default;
    TetrisBlock(const TetrisBlock&) = delete;
    int getType() override { return color; }
};
