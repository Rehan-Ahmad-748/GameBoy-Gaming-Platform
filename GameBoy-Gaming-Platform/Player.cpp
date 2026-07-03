#include "Player.h"
#include <iostream>
#include <fstream>
using namespace std;
Player::Player(const  string& playerName) 
    : name(playerName), score(0), numAchievements(0) {}

 string Player::getName() const {
    return name;
}

void Player::setName(const  string& playerName) {
    name = playerName;
}

void Player::saveProgress() {
     ofstream file(name + "_progress.txt");
    if (file.is_open()) {
        file << score <<  endl;  // Save the score to the file
        file << numAchievements <<  endl;  // Save the number of achievements
        for (int i = 0; i < numAchievements; ++i) {
            file << achievements[i] <<  endl; // Save each achievement
        }
        file.close();
    } else {
         cout << "Error saving player progress!" <<  endl;
    }
}

void Player::loadProgress() {
     ifstream file(name + "_progress.txt");
    if (file.is_open()) {
        file >> score;  // Load the score from the file
        file >> numAchievements;  // Load the number of achievements
        for (int i = 0; i < numAchievements; ++i) {
            file >> achievements[i];  // Load each achievement
        }
        file.close();
    } else {
         cout << "Error loading player progress!" <<  endl;
    }
}

void Player::addAchievement(const  string& achievement) {
    if (numAchievements < 10) {  // Check if there is space for more achievements
        achievements[numAchievements] = achievement;
        ++numAchievements;
    } else {
         cout << "Achievement list is full!" <<  endl;
    }
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int newScore) {
    score = newScore;
}
