#pragma once

#include "GameObject.h"
#include "CustomExceptions.h"

class Bomb : public GameObject {
private:
    int radius;
    bool ticker;
    coords* explosion;
    int explosionLength;
public:
    Bomb() = delete;
    Bomb(int, int, coords);
    ~Bomb() override { delete[] explosion; }
    Bomb(const Bomb&) = delete;
    void shift(int, int) override;
    int getType() override;
    coords* getExplosion(int i) { return i >= 0 && i < explosionLength ? &explosion[i] : nullptr; }
};