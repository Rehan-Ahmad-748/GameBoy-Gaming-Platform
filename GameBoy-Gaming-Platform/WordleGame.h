#ifndef WORDLEGAME_H
#define WORDLEGAME_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SoundSystem.h"
#include <SFML/Audio.hpp>
using namespace std;
const int CELL_EMPTY = 0;
const int CELL_INCORRECT = 1;
const int CELL_MISPLACED = 2;
const int CELL_CORRECT = 3;

class WordleGame : public Game
{
private:
    static const int MAX_ATTEMPTS = 6;
    static const int WORD_LENGTH = 5;
    int score;
    SoundSystem soundSystem;

    // Arrays to track previous tries
    char previousTries[MAX_ATTEMPTS][WORD_LENGTH + 1]; // Stores previous guesses
    int cellColors[MAX_ATTEMPTS][WORD_LENGTH];         // Stores color state for each cell

    char targetWord[6];   // Target word to guess (5 letters + null terminator)
    char currentGuess[6]; // Current guess (5 letters + null terminator)
    int attemptsLeft;     // Number of attempts left
    static const int MAX_WORDS = 1000;
     string wordList[MAX_WORDS];
    int wordCount = 0;

    sf::RenderWindow *window; // Pointer to the window for rendering
    sf::Font font;            // Font for displaying text
    sf::Text text;            // Text object for displaying messages
     string feedback;     // Feedback message (correct/incorrect letters)

public:
    WordleGame(sf::RenderWindow *window); // Constructor
    void start() override;                // Start the game
    void run() override;                  // Main game loop
    void update() override;               // Update the game state
    void render() override;               // Render game state to the window
    void end() override;                  // End the game
    bool isGameOver() const override;     // Check if the game is over

    // Input handling function
    void handleInput(sf::Uint32 unicode);

    // Helper functions
    void loadFromFile(const  string &filename);

    void drawGameStatus();
    void drawGameGrid();
    void drawGameKeyboard();
    void renderEndScreen();
    void updateCellColors(const char *guess);

    bool validateGuess(const char *guess);
    void provideFeedback();
    void copyCString(char *dest, const char *src, int maxLength);
    bool compareStrings(const char *str1, const char *str2);
    bool containsChar(const char *str, char ch);
};

#endif // WORDLEGAME_H
