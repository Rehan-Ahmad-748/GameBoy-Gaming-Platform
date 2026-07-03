#include "SoundSystem.h"
#include <iostream>
#include <SFML/Audio.hpp>
using namespace std;
SoundSystem::SoundSystem() {}

void SoundSystem::playSound(const  string &soundFile)
{
    if (buffer.loadFromFile(soundFile))
    {
        sound.setBuffer(buffer);
        sound.play();
    }
    else
    {
         cout << "Error loading sound file: " << soundFile <<  endl;
    }
}

void SoundSystem::playMusic(const  string &musicFile)
{
    sf::Music music;
    if (music.openFromFile(musicFile))
    {
        music.play();
    }
    else
    {
         cout << "Error loading music file: " << musicFile <<  endl;
    }
}
bool SoundSystem::loadBackgroundMusic(const  string &filePath)
{
    if (!backgroundMusic.openFromFile(filePath))
    {
         cerr << "Error loading background music from " << filePath <<  endl;
        return false;
    }
     cout << "Background music loaded successfully!" <<  endl;
    return true;
}

void SoundSystem::playBackgroundMusic()
{
    if (backgroundMusic.getStatus() != sf::Music::Playing)
    {
         cout << "Playing background music..." <<  endl;
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(25.0);
        backgroundMusic.play();
    }
}

// Stop the background music
void SoundSystem::stopBackgroundMusic()
{
    backgroundMusic.stop();
}

// Pause the background music
void SoundSystem::pauseBackgroundMusic()
{
    backgroundMusic.pause();
}

// Resume the background music
void SoundSystem::resumeBackgroundMusic()
{
    backgroundMusic.play();
}
