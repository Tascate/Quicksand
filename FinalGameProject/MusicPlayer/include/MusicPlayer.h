#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class MusicPlayer {
private:
    Music music;
    Sound secondSound;
    Sound thirdSound;

    float mainVolume = 20;
    std::string fileLocation;
public:
    MusicPlayer(std::string location = "Music/"): fileLocation(location) {}
    void playOne(const std::string& fileName);
    void pauseMusic();
    void continueMusic();
    void adjVolume(int dir);
    void playThree(const std::string& fileName);
    void playTwo(const std::string& fileName);
};

