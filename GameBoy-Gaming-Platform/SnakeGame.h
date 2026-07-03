#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <SFML/Audio.hpp>
#include "SoundSystem.h"

class SnakeGame : public Game
{
private:
    static const int maxSnake = 100;
    int snake[maxSnake][2]; // Snake body positions
    int snakeSize;
    int food[2];    // Food position
    int score;      // Current score
    char direction; // Direction of movement ('u', 'd', 'l', 'r')
    bool endGameFlag;
    int highestScore;

    const int gridSize; // Size of grid cells
    const int rows;     // Number of rows
    const int cols;     // Number of columns

    sf::Text scoreText;
    sf::Font font;
    sf::SoundBuffer foodSoundBuffer;     // Sound buffer for food
    sf::SoundBuffer gameOverSoundBuffer; // Sound buffer for game over
    sf::Sound foodSound;                 // Sound for eating food
    sf::Sound gameOverSound;             // Sound for game over
    int gameSpeed;                       // Speed of snake movement in milliseconds
    sf::Music backgroundMusic;

public:
    SnakeGame(sf::RenderWindow *window, int gridSize, int rows, int cols);
    virtual ~SnakeGame();

    void start() override;
    void run() override;
    void update() override;
    void render() override;
    void end() override;

    void loadHighestScore();
    void saveHighestScore();
    void handleInput(sf::Keyboard::Key key);
    void moveSnake();
    void checkCollision();
    void deployFood();
    void drawSnake(sf::RenderWindow &window);
    void drawFood(sf::RenderWindow &window);
    void updateScoreText();
    void renderScore(sf::RenderWindow &window);
    char getDirection() const;
    void setDirection(const char &newDirection);
    bool getEndGameFlag() const;

    // Implement the missing pure virtual function from Game class
    bool isGameOver() const override; // Implement this function
};

#endif // SNAKEGAME_H