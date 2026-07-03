#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "Game.h"
#include "Menu.h"
#include "InputSystem.h"
#include "SoundSystem.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

// The GameBoy class serves as the main controller for managing games, input, sound, and rendering.
class GameBoy {
private:
    Game* currentGame;          // Pointer to the currently active game (e.g., Snake, Wordle, Hangman).
    InputSystem inputSystem;    // Object to handle player inputs (keyboard, mouse, etc.).
    SoundSystem soundSystem;    // Object to manage and play game sounds and music.
    Menu* menu;                 // Menu object for game selection and navigation.
    Player* player;             // Pointer to a Player object to track player details like name and score.
    sf::RenderWindow* window;   // Pointer to the SFML RenderWindow for rendering the game interface.

public:
    // Constructor: Initializes the GameBoy system, creating necessary objects.
    GameBoy();

    // Main game loop: Manages the display of the menu, handling game transitions, and overall application flow.
    void run();
};

#endif // GAMEBOY_H

