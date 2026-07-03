#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu
{
private:
    sf::RenderWindow *window; // Pointer to the render window for displaying the menu
    sf::Font font;            // Font for rendering text
    sf::Text title;           // Title of the menu
    sf::Text option1;         // Option 1: Play Snake Game
    sf::Text option2;         // Option 2: Play Wordle Game
    sf::Text option3;         // Option 2: Play Wordle Game
    sf::Text option4;         // Option 2: Play Wordle Game
    sf::Text option5;         // Option 3: Exit the game

public:
    // Constructor to initialize the menu with a window reference and font
    Menu(sf::RenderWindow *window, const sf::Font &font);

    // Function to display the menu to the user
    void display();

    // Function to handle user navigation (key presses)
    int navigate();
};

#endif // MENU_H
