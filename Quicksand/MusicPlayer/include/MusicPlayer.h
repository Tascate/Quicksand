#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class MusicPlayer {
private:
    sf::Music music;
    sf::Sound secondSound;
    sf::Sound thirdSound;

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