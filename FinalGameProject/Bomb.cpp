#include "Bomb.h"

Bomb::Bomb(int h, int w, coords s) :GameObject(9, 7, s), radius(1), ticker(false), explosion(new coords[25]), explosionLength(0) {
    if(h*w < 9)
        throw BlockEx::InvalidSpawn(false, false, 3,3);
    // intailize block
    numberOfBlocks = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            blockArea[numberOfBlocks].row = s.row + i;
            blockArea[numberOfBlocks].col = s.col + j;
            numberOfBlocks++;
        }
    }
    // intialize explosion radius
    coords buffer;
    for (int i = -1 * (1 + radius); i < 2 + radius; i++) {
        for (int j = -1 * (1 + radius); j < 2 + radius; j++) {
            buffer.row = s.row + i;
            buffer.col = s.col + j;
            explosion[explosionLength] = buffer;
            explosionLength++;
        }
    }
}

void Bomb::shift(int rowU, int colU){
    // shift bomb
    GameObject::shift(rowU, colU);
    // shift explosion
    for (int i = 0; i < explosionLength; i++) {
        explosion[i].row += rowU;
        explosion[i].col += colU;
    }
}

int Bomb::getType(){
    // animation feel but using @override feature
    ticker = !ticker;
    if (ticker) {
        return color;
    } else {
        return color - 1;
    }
}