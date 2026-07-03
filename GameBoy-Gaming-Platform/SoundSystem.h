#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <SFML/Audio.hpp>
#include <string>
using namespace std;
class SoundSystem
{
private:
    sf::SoundBuffer buffer; // Sound buffer to hold the sound data
    sf::Sound sound;        // Sound object to play the sound
    sf::Music backgroundMusic;

public:
    // Constructor
    SoundSystem();

    // Method to play a sound from a file
    void playSound(const  string &soundFile);
    bool loadBackgroundMusic(const  string &filePath);

    void playBackgroundMusic();
    void stopBackgroundMusic();
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();
    // Method to play music from a file
    void playMusic(const  string &musicFile);
};

#endif
