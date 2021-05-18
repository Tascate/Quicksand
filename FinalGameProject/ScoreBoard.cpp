#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
    ptr = board.end();
}

void ScoreBoard::serializeTo(string fileName)
{
    ofstream fout(fileName, ios::binary);
    if (!fout) {
        std::cerr << "Unable to open Score Board to Update: " << fileName << endl;
        exit(1);
    }
    int i = 0;
    for (auto it : board) {
        if (i >= 10)
            break;
        fout.write(reinterpret_cast<const char*>(&(it.first)), sizeof(int));
        size_t size = it.second.size();
        fout.write(reinterpret_cast<const char*>(&(size)), sizeof(size));
        fout.write(it.second.c_str(), size);
        i++;
    }
    fout.close();
}

bool ScoreBoard::deserializeFrom(string fileName)
{
    ifstream fin(fileName, ios::binary);
    if (!fin) {
        return false;
    }
    int scoreBuffer;
    size_t size;
    string nameBuffer;
    int i = 0;
    while (i < 10 && fin.read(reinterpret_cast<char*>(&scoreBuffer), sizeof(scoreBuffer))) {
        fin.read(reinterpret_cast<char*>(&size), sizeof(size));
        nameBuffer.resize(size);
        fin.read(const_cast<char*>(nameBuffer.c_str()), size);

        board.insert(pair<int, string>(scoreBuffer, nameBuffer));
        i++;
    }
    fin.close();
    ptr = board.end(); // signifies score is not on leaderboard
    newPlayerScore(0, playerName);
    return true;
}

void ScoreBoard::newPlayerScore(int score, string playerName)
{
    if(board.empty()) { // edge case
        ptr = board.insert(pair<int, string>(score, playerName));
        return;
    }
    if(ptr != board.end())    // remove previous score from map or lowest score if its the first time
        board.erase(ptr);
    ptr = board.insert(pair<int, string>(score, playerName)); // insert & update tracker
}