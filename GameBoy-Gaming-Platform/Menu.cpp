// Menu.cpp
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Constructor for the Menu class
Menu::Menu(sf::RenderWindow *window, const sf::Font &font) : window(window), font(font)
{
    float windowWidth = window->getSize().x;
    float windowHeight = window->getSize().y;

    // Set the font for all text elements
    title.setFont(this->font);
    option1.setFont(this->font);
    option2.setFont(this->font);
    option3.setFont(this->font);
    option4.setFont(this->font);

    // Title configuration
    title.setCharacterSize(windowHeight / 15); // Relative sizing based on window height
    title.setFillColor(sf::Color::White);
    title.setString("Select a Game:");
    title.setPosition(windowWidth / 4, windowHeight / 10);

    // Option 1: Play Snake Game
    option1.setCharacterSize(windowHeight / 25);
    option1.setFillColor(sf::Color::White);
    option1.setString("1. Play Snake Game");
    option1.setPosition(windowWidth / 4, windowHeight / 4);

    // Option 2: Play Wordle Game
    option2.setCharacterSize(windowHeight / 25);
    option2.setFillColor(sf::Color::White);
    option2.setString("2. Play Wordle Game");
    option2.setPosition(windowWidth / 4, (windowHeight / 4) + 50);

    // Option 3: Play Hangman Game
    option3.setCharacterSize(windowHeight / 25);
    option3.setFillColor(sf::Color::White);
    option3.setString("3. Play Hangman Game");
    option3.setPosition(windowWidth / 4, (windowHeight / 4) + 100);

    // Option 3: Exit the game
    option4.setCharacterSize(windowHeight / 25);
    option4.setFillColor(sf::Color::White);
    option4.setString("4. Exit");
    option4.setPosition(windowWidth / 4, (windowHeight / 4) + 150);
}
void Menu::display()
{
    window->clear(sf::Color::Black);

    title.setCharacterSize(30);   // Smaller size for the title
    option1.setCharacterSize(20); // Smaller size for options
    option2.setCharacterSize(20);
    option3.setCharacterSize(20);
    option4.setCharacterSize(20);

    window->draw(title);
    window->draw(option1);
    window->draw(option2);
    window->draw(option3);
    window->draw(option4);

    window->display();
}

int Menu::navigate()
{
    sf::Event event;
    while (window->waitEvent(event))
    { // Block until an event occurs
        if (event.type == sf::Event::Closed)
        {
            window->close();
            return 3; // Exit choice
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            // Handle the number keys for navigation
            if (event.key.code == sf::Keyboard::Num1)
            {
                return 1; // Play Snake Game
            }
            else if (event.key.code == sf::Keyboard::Num2)
            {
                return 2; // Play Wordle Game
            }
            else if (event.key.code == sf::Keyboard::Num3)
            {
                return 3; // Play Hangman Game
            }
            else if (event.key.code == sf::Keyboard::Num4)
            {
                return 4; // Exit
            }
        }
    }
    return 0; // Default return value
}
