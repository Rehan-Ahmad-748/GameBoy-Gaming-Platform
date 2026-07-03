#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <fstream>
using namespace std;
class Player
{
private:
     string name;             // Player's name
    int score;                    // Player's score
     string achievements[10]; // Array to hold achievements (max 10)
    int numAchievements;          // Keeps track of how many achievements have been added

public:
    // Constructor that initializes the player's name and score
    Player(const  string &playerName);

    // Get the player's name
     string getName() const;

    // Set the player's name
    void setName(const  string &playerName);

    // Save the player's progress (score and potentially more) to a file
    void saveProgress();

    // Load the player's progress from a file
    void loadProgress();

    // Add an achievement to the player's list (up to 10 achievements)
    void addAchievement(const  string &achievement);

    // Get the player's score
    int getScore() const;

    // Set the player's score
    void setScore(int newScore);
};

#endif // PLAYER_H
