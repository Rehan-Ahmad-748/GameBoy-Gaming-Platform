#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Menu.h"
#include "Player.h"

// Base class for all games
class Game {
protected:
    sf::RenderWindow* window;  // Pointer to the SFML window for rendering graphics
    Player* player;            // Pointer to a Player object, representing the player
    Menu* menu;                // Pointer to a Menu object for navigation
    sf::Font font;             // Font object for displaying text
    int score;                 // Score variable to track the player's score

public:
    // Constructor: Initializes the Game with a pointer to an SFML RenderWindow
    Game(sf::RenderWindow* window) 
        : window(window), player(nullptr), menu(nullptr) {}

    // Virtual destructor: Ensures proper cleanup of dynamically allocated objects
    virtual ~Game() {
        delete player;  // Free memory allocated for the Player object
        delete menu;    // Free memory allocated for the Menu object
    }

    // Pure virtual functions (abstract methods) to be implemented by derived classes:
    virtual void start() = 0;          // Initialize and start the game
    virtual void run() = 0;            // Main game loop to run the game
    virtual void update() = 0;         // Update game logic (e.g., player movement, collisions)
    virtual void render() = 0;         // Render game objects to the window
    virtual void end() = 0;            // End the game (e.g., display game over screen)
    virtual bool isGameOver() const = 0; // Check if the game has ended

    // Note: Derived classes must override all pure virtual functions, making this class an abstract base.
};

#endif // GAME_H

