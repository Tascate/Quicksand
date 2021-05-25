#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class AudioPlayer {
private:
    sf::Music music;
    sf::SoundBuffer buffer;
    sf::Sound secondSound;
    sf::Sound thirdSound;

    float mainVolume = 20;
    std::string fileLocation;
public:
    AudioPlayer(std::string location = "Music/"): fileLocation(location) {}
    void playOne(const std::string& fileName);
    void pauseMusic();
    void continueMusic();
    void adjVolume(int dir);
    void playThree(const std::string& fileName);
    void playTwo(const std::string& fileName);
};