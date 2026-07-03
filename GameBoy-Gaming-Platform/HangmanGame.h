#ifndef HANGMAN_H
#define HANGMAN_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SoundSystem.h"
#include <SFML/Audio.hpp>
#include <string>

// Base class for all categories
class Category
{
protected:
    char words_list[10][20]; // Array to store a list of words for the category
    char word[20];           // Stores the randomly selected word for the game
    char word_hidden[20];    // Stores the hidden version of the word (e.g., with asterisks for unrevealed letters)
    int life;                // Tracks the remaining attempts/lives for the player

public:
    // Pure virtual function to populate the list of words specific to the category
    virtual void populateWordsList() = 0;

    // Pure virtual function to return the name of the category
    virtual const char *getCategoryName() const = 0;

    // Selects a random word from the word list
    void selectRandomWord();

    // Returns the actual selected word
    const char *getWord() const;

    // Returns the current state of the word with revealed letters and asterisks
    const char *getHiddenWord() const;

    // Updates the hidden word based on a guessed letter; reduces lives for incorrect guesses
    void updateHiddenWord(char guess);

    // Checks if the game is over (either all lives are lost or the word is fully guessed)
    bool isGameOver() const;

    // Checks if the player has successfully guessed the entire word
    bool isWin() const;

    // Returns the number of lives left
    int getLives() const;

    // Resets the player's lives to the initial value (e.g., 6)
    void resetLives();

    // Virtual destructor to ensure proper cleanup for derived classes
    virtual ~Category() {}
};

// Derived class for the "Countries" category
class Countries : public Category
{
public:
    // Populates the word list with names of countries
    void populateWordsList() override;

    // Returns the name of the category
    const char *getCategoryName() const override;
};

// Derived class for the "Cities" category
class Cities : public Category
{
public:
    // Populates the word list with names of cities
    void populateWordsList() override;

    // Returns the name of the category
    const char *getCategoryName() const override;
};

// Derived class for the "Cars" category
class Cars : public Category
{
public:
    // Populates the word list with names of cars
    void populateWordsList() override;

    // Returns the name of the category
    const char *getCategoryName() const override;
};

// Main class for the Hangman game
class HangmanGame : public Game
{
private:
    sf::RenderWindow *window; // Pointer to the SFML window for rendering the game
    sf::Font font;            // Font used for text rendering in the game

    Category *currentCategory; // Pointer to the currently selected category
    bool game_over;            // Flag to track if the game has ended

    // Draws the hangman figure based on the number of lives left
    void drawHangman(sf::RenderWindow *window, int lives);

    // Displays the category selection screen and sets the selected category
    void selectCategory(sf::RenderWindow *window, sf::Font &font);

public:
    // Constructor to initialize the game with the given window
    HangmanGame(sf::RenderWindow *window);

    // Starts the game and contains the main gameplay logic
    void start() override;

    // Main game loop (to be implemented as needed)
    void run() override;

    // Updates the game state per frame
    void update() override;

    // Handles rendering the current game state to the window
    void render() override;

    // Handles cleanup and exiting the game
    void end() override;

    // Checks if the game is over (override from base class Game)
    bool isGameOver() const override;
};

#endif // HANGMAN_H

