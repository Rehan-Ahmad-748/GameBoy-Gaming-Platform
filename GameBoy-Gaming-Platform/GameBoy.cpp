#include "GameBoy.h"
#include "SnakeGame.h"
#include "WordleGame.h"
#include "HangmanGame.h"
#include <iostream>

// Constructor for the GameBoy class
GameBoy::GameBoy() 
    : currentGame(nullptr), menu(nullptr), window(new sf::RenderWindow(sf::VideoMode(800, 600), "GameBoy"))
{
    // Load the font for the menu
    sf::Font font;
    if (!font.loadFromFile("game_over.ttf")) // Load custom font file
    {
        std::cerr << "Failed to load font!" << std::endl; // Log error if font loading fails
        return;
    }

    // Create a Player object with the name "Ifham"
    player = new Player("Ifham");

    // Initialize the Menu object using the game window and loaded font
    menu = new Menu(window, font);
}

// Main loop to run the GameBoy application
void GameBoy::run()
{
    // Continue running while the game window is open
    while (window->isOpen())
    {
        menu->display();               // Display the menu to the player
        int choice = menu->navigate(); // Get the player's choice from the menu

        // Handle the player's menu choice
        switch (choice)
        {
        case 1: // Play Snake Game
        {
            // Dynamically calculate the grid size and dimensions based on window size
            const int windowWidth = window->getSize().x;
            const int windowHeight = window->getSize().y;
            const int gridSize = windowWidth / 40; // Adjust grid size for 40 columns
            const int rows = windowHeight / gridSize;
            const int cols = windowWidth / gridSize;

            // Initialize SnakeGame with grid properties
            currentGame = new SnakeGame(window, gridSize, rows, cols);
            std::cout << "Starting Snake Game..." << std::endl;
            currentGame->start(); // Start the Snake game
            break;
        }
        case 2: // Play Wordle Game
        {
            currentGame = new WordleGame(window); // Initialize WordleGame
            std::cout << "Starting Wordle Game..." << std::endl;
            currentGame->start(); // Start the Wordle game
            break;
        }
        case 3: // Play Hangman Game
        {
            currentGame = new HangmanGame(window); // Initialize HangmanGame
            std::cout << "Starting Hangman Game..." << std::endl;
            currentGame->start(); // Start the Hangman game
            break;
        }
        case 4: // Exit the application
        {
            window->close(); // Close the game window
            break;
        }
        default: // Handle invalid menu choices
        {
            std::cerr << "Invalid choice! Returning to menu." << std::endl;
            break;
        }
        }

        // Ensure proper cleanup and transition after a game ends
        if (currentGame)
        {
            currentGame->run(); // Run the selected game
            delete currentGame; // Free memory allocated for the game
            currentGame = nullptr; // Reset the pointer to avoid dangling reference
        }
    }
}

