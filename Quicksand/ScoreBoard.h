#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class ScoreBoard {
    private:
        multimap<int, string> board;
        multimap<int, string>::iterator ptr;
    public:
        ScoreBoard();
        const multimap<int, string> getBoard() const {return board;}
        void serializeTo(string);
        bool deserializeFrom(string);
        void newPlayerScore(int score, string playerName);
};

