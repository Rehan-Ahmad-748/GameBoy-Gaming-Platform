#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameBoy.h" // Include GameBoy header

int main()
{
    // sf::RenderWindow window(sf::VideoMode(800, 600), "GameBoy");

    // Load the font for the menu
    sf::Font font;
    if (!font.loadFromFile("game_over.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    // Create a GameBoy instance and start the game loop
    GameBoy gameBoy;
    gameBoy.run();

    return 0;
}
