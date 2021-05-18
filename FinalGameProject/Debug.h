#pragma once

#include "GameMap.h"

using namespace std;

class Debug {
private:
    GameMap* dMap;
    GameObject* dObj;
public:
    Debug() = delete;
    Debug(GameMap* map, GameObject* obj): dMap(map), dObj(obj){}
    void moveBlock(int, int);
    GameObject* spawn(char);
};