
#include "MusicPlayer.h"

// function to control volume by press key up and dowm

void MusicPlayer::adjVolume(int dir) {
    if (mainVolume + dir >= 0 && mainVolume + dir <= 100)     {
        mainVolume += dir;

        music.setVolume(mainVolume);
        secondSound.setVolume(mainVolume);
        thirdSound.setVolume(mainVolume);
    }
}


// function to play music in whole game: use with "Tetris.ogg" for game music
void MusicPlayer::playOne(const std::string& fileName) {
    // music play fileName : "Tetris.ogg"
    if (!music.openFromFile(fileLocation + fileName)) {
        std::cout << "Can not open game music file " << fileName << std::endl;
        return;
    }
    music.setVolume(mainVolume);
    music.play();
    music.setLoop(true);
}

void MusicPlayer::continueMusic() {
    music.play();
}

void MusicPlayer::pauseMusic() {
    music.pause();
}


// function to play sound effects when the blocks got cancel: use with "Tetris_DX.ogg" for cancel blocks sound effects
void MusicPlayer::playTwo(const std::string& fileName) {
    sf::SoundBuffer buffer;
    // music play fileName : "Tetris_DX.ogg"
    if (!buffer.loadFromFile(fileLocation + fileName)) {
        std::cout << "Can not open cancel block music file " << fileName << std::endl;
        return;
    }
    secondSound.setBuffer(buffer);
    secondSound.setVolume(mainVolume);
    secondSound.play();
}


// function to play sound effects when game is over: use with "Tetris_Jingle.ogg" for game over sound effects
void MusicPlayer::playThree(const std::string& fileName) {
    sf::SoundBuffer buffer;
    // music play fileName : "Tetris_DX.ogg"
    if (!buffer.loadFromFile(fileLocation + fileName)) {
        std::cout << "Can not open game over music file " << fileName << std::endl;
        return;
    }
    music.stop();
    thirdSound.setBuffer(buffer);
    thirdSound.setVolume(mainVolume);
    thirdSound.play();
}