#include "Debug.h"

void Debug::moveBlock(int row, int col) {
    // get difference
    row -= (dObj->origin).row;
    col -= (dObj->origin).col;
    if(row != 0 || col != 0)
        dMap -> shiftObj(dObj, row, col); // move
}

GameObject* Debug::spawn(char c) {
    // create new block Object
    coords spawnPoint;
    spawnPoint.row = dMap->spawnH / 2;
    spawnPoint.col = dMap->mapWidth / 2;
    GameObject* newObj;
    switch(c) {
    case 'b':
        newObj = dMap->generator(2, spawnPoint);
        break;
    case 'r':
        newObj = dMap->generator(1, spawnPoint);
        break;
    case 't':
        newObj = dMap->generator(3, spawnPoint);
        break;
    default:
        newObj = dMap->generator(4, spawnPoint);
        break;
    }
    try {
        // attempt to put it into map
        coords* coordP = newObj->getCoords(0);
        for (int i = 1; coordP != nullptr; i++) {
            dMap->addSqAt(coordP->row, coordP->col, newObj->getType());
            coordP = newObj->getCoords(i);
        }
    } catch(const MapEx::InvalidOperation& badSq) {
        // clean up mess
        coords stopped;
        stopped.row = badSq.getRow();
        stopped.col = badSq.getCol();
        coords* coordP = newObj->getCoords(0);
        for (int i = 1; *coordP != stopped ; i++) {
            dMap->removeSqAt(coordP->row, coordP->col);
            coordP = newObj->getCoords(i);
        }
        delete newObj;
        return nullptr;
    }
    // update if successful
    coords* coordP = dObj->getCoords(0);
    for (int i = 1; coordP != nullptr; i++) {
        dMap->removeSqAt(coordP->row, coordP->col);
        coordP = dObj->getCoords(i);
    }
    dObj = newObj;
    return newObj;
}