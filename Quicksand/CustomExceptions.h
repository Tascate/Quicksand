#pragma once

#include "GameGraphics.h"
#include <cstdlib>
#include <iostream>

namespace BlockEx {
    class InvalidSpawn{
    private:
        bool height, width;
        int advHeight, advWidth;
    public:
        InvalidSpawn(bool h, bool w, int ah, int aw) : height(h), width(w), advHeight(ah), advWidth(aw) {}
        bool hasHeightIssue() const { return height; }
        bool hasWidthIssue() const { return width; }
        int recommendHeight() const { return advHeight; }
        int recommendWidth() const { return advWidth; }
    };
}

namespace ListEx {
    class OutofBounds{
    private:
        std::string err;
        int index, size;
    public:
        OutofBounds(int i, int s) : err("Tried to Access Invalid Index In LinkedList "), index(i), size(s) {}
        void display(){
            std::cerr << err << "\n" << "Index: " << index <<" Size: " << size;
        }
    };
}

namespace MapEx {
    class OutOfBounds{
    private:
        int row, col;
    public:
        OutOfBounds(int r, int c): row(r), col(c){}
        int getRow() const{return row;}
        int getCol() const{return col;}
    };
    
    class InvalidOperation{
    private:
        int row, col;
    public:
        InvalidOperation(int r, int c): row(r), col(c){}
        int getRow() const{return row;}
        int getCol() const{return col;}
    };

    class GameOver {
    public:
        GameOver() {}
        void display(sf::RenderWindow& window, GameGraphics& drawer, const ScoreBoard& board) {
            window.clear();
            drawer.drawGameOver(board);
            window.display();
        }
    };
}