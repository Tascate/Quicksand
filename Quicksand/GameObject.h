#pragma once

#include <cstdlib>

using namespace std;

class Debug;

struct coords {
    int row = 0;
    int col = 0;

    bool operator==(const coords& other) const {
        return row == other.row && col == other.col;
    }
    bool operator!=(const coords& other) const {
        return !(*this == other);
    }
    coords& operator=(const coords& rhs) {
        row = rhs.row;
        col = rhs.col;
        return *this;
    }
};

class GameObject {
protected:
    coords* blockArea = nullptr;
    int numberOfBlocks = 0;
    int color = 1;
    coords origin;
public:
    GameObject() = delete;
    GameObject(int n, int c, coords s) : blockArea(new coords[n]), numberOfBlocks(n), color(c), origin(s) {}
    virtual ~GameObject(){ delete[] blockArea; }
    GameObject(const GameObject&) = delete;
    virtual void rotateCW() {
        int temp;
        for (int i = 0; i < numberOfBlocks; i++) {
            temp = origin.row - blockArea[i].row;
            blockArea[i].row = origin.row - (origin.col - blockArea[i].col);
            blockArea[i].col = origin.col + temp;
        }
    }
    virtual void rotateCCW() {
        int temp;
        for (int i = 0; i < numberOfBlocks; i++) {
            temp = origin.row - blockArea[i].row;
            blockArea[i].row = origin.row + (origin.col - blockArea[i].col);
            blockArea[i].col = origin.col - temp;
        }
    }
    virtual void shift(int rowU, int colU) {
        for (int i = 0; i < numberOfBlocks; i++) {
            blockArea[i].row += rowU;
            blockArea[i].col += colU;
        }
        origin.row += rowU;
        origin.col += colU;
    }
    virtual coords* getCoords(int i) { return (i < numberOfBlocks&& i >= 0) ? &blockArea[i] : nullptr;}
    virtual int getType() = 0;

    friend class Debug;
};
