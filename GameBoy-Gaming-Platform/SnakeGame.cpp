#include "SnakeGame.h"
#include <cstdlib> // For rand()
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
using namespace std;
// Constructor
SnakeGame::SnakeGame(sf::RenderWindow *window, int gridSize, int rows, int cols)
    : Game(window), gridSize(gridSize), rows(rows), cols(cols), snakeSize(3), score(0), direction('r'), endGameFlag(false)
{

    loadHighestScore();

    for (int i = 0; i < snakeSize; ++i)
    {
        snake[i][0] = cols / 2 - i; // Set initial X positions
        snake[i][1] = rows / 2;     // Set initial Y position (same row)
    }

    deployFood();

    if (!font.loadFromFile("game_over.ttf"))
    {
         cerr << "Error loading font!" <<  endl;
        exit(1);
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    // Load sound buffers
    if (!foodSoundBuffer.loadFromFile("food.mp3") || !gameOverSoundBuffer.loadFromFile("gameover.wav"))
    {
         cerr << "Error loading sound files!" <<  endl;
        exit(1);
    }

    foodSound.setBuffer(foodSoundBuffer);
    gameOverSound.setBuffer(gameOverSoundBuffer);
}

void SnakeGame::loadHighestScore()
{
     ifstream file("highest_score.txt");
    if (file.is_open())
    {
        file >> highestScore;
        file.close();
    }
    else
    {
        highestScore = 0; // Default to 0 if file doesn't exist
    }
}

void SnakeGame::saveHighestScore()
{
     ofstream file("highest_score.txt");
    if (file.is_open())
    {
        file << highestScore;
        file.close();
    }
}

SnakeGame::~SnakeGame()
{
    // Destructor (cleanup if needed)
}
// Start the game
void SnakeGame::start()
{

     cout << "Starting Snake Game!" <<  endl;

    // Difficulty menu
    int difficulty = 0;
    while (difficulty < 1 || difficulty > 3)
    {
         cout << "\n=== SELECT DIFFICULTY ===\n";
         cout << "1. Easy\n";
         cout << "2. Medium\n";
         cout << "3. Hard\n";
         cout << "Enter your choice: ";
         cin >> difficulty;

        if (difficulty < 1 || difficulty > 3)
        {
             cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }

    // Adjust speed based on difficulty
    int speed = 100; // Default speed (Medium)
    if (difficulty == 1)
    {
        speed = 200; // Easy
    }
    else if (difficulty == 2)
    {
        speed = 120; // Medium
    }
    else if (difficulty == 3)
    {
        speed = 80; // Hard
    }

     cout << "Difficulty selected: "
              << (difficulty == 1 ? "Easy" : difficulty == 2 ? "Medium"
                                                             : "Hard")
              << ". Speed set to " << speed << "ms.\n";

    // Set the game speed
    gameSpeed = speed;

    if (!backgroundMusic.openFromFile("songofsnakegame.mp3"))
    {
         cerr << "Error loading music!" <<  endl;
        exit(1); // Exit if music file fails to load
    }
    backgroundMusic.setLoop(true); // Loop the music
    backgroundMusic.play();        // Play the music

    run();
}
// Main game loop
void SnakeGame::run()
{
    sf::Clock clock; // Clock to control snake movement speed

    while (window->isOpen() && !endGameFlag)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                handleInput(event.key.code);
            }
        }

        if (clock.getElapsedTime().asMilliseconds() >= gameSpeed)
        { // Move every 100ms
            update();
            render();
            clock.restart();
        }
    }

    end(); // Show game over screen
}

// Update game state
void SnakeGame::update()
{
    moveSnake();
    checkCollision();
}

// Render game state
void SnakeGame::render()
{
    window->clear(sf::Color::Black);

    drawSnake(*window);
    drawFood(*window);

    // Display the score
    scoreText.setString("Score: " +  to_string(score) + "\nHighest: " +  to_string(highestScore));
    window->draw(scoreText);

    window->display();
}
// End the game

void SnakeGame::end()
{
     cout << "Game Over! Final Score: " << score <<  endl;

    if (score > highestScore)
    {
        highestScore = score;
        saveHighestScore(); // Save new highest score
    }

    gameOverSound.play(); // Play game over sound
    endGameFlag = true;
}

// Implement the missing pure virtual function from Game class
bool SnakeGame::isGameOver() const
{
    return endGameFlag;
}
// Check for collisions
void SnakeGame::checkCollision()
{
    if (snake[0][0] < 0 || snake[0][0] >= cols || snake[0][1] < 0 || snake[0][1] >= rows)
    {
        endGameFlag = true; // Snake hit the wall
    }

    for (int i = 1; i < snakeSize; ++i)
    {
        if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1])
        {
            endGameFlag = true; // Snake hit itself
        }
    }
}

// Move the snake
void SnakeGame::moveSnake()
{
    int newHeadX = snake[0][0];
    int newHeadY = snake[0][1];

    // Update head position
    switch (direction)
    {
    case 'u':
        newHeadY--;
        break;
    case 'd':
        newHeadY++;
        break;
    case 'l':
        newHeadX--;
        break;
    case 'r':
        newHeadX++;
        break;
    }

    // Move the rest of the body
    for (int i = snakeSize; i > 0; --i)
    {
        snake[i][0] = snake[i - 1][0];
        snake[i][1] = snake[i - 1][1];
    }

    snake[0][0] = newHeadX;
    snake[0][1] = newHeadY;

    // Check if food is eaten
    if (snake[0][0] == food[0] && snake[0][1] == food[1])
    {
        snakeSize++;
        score += 10;
        deployFood();
        // Play sound for eating food
        foodSound.play();
    }
}

// Deploy food at a random position on the grid
void SnakeGame::deployFood()
{
    food[0] = rand() % cols;
    food[1] = 1 + rand() % (rows - 2);
}

// Draw the snake on the window
void SnakeGame::drawSnake(sf::RenderWindow &window)
{
    sf::CircleShape segment(gridSize / 2.0f); // Circle with radius half of gridSize
    segment.setFillColor(sf::Color::Green);

    for (int i = 0; i < snakeSize; ++i)
    {
        segment.setPosition(snake[i][0] * gridSize, snake[i][1] * gridSize);
        segment.setOrigin(gridSize / 2.0f, gridSize / 2.0f); // Center the circle
        window.draw(segment);
    }
}

// Draw the food on the window
// Draw the food on the window
void SnakeGame::drawFood(sf::RenderWindow &window)
{
    sf::CircleShape foodShape(gridSize / 2.0f); // Circle with radius half of gridSize
    foodShape.setFillColor(sf::Color::Red);
    foodShape.setPosition(food[0] * gridSize, food[1] * gridSize);
    foodShape.setOrigin(gridSize / 2.0f, gridSize / 2.0f); // Center the circle
    window.draw(foodShape);
}

// Update the score text
void SnakeGame::updateScoreText()
{
    scoreText.setString("Score: " +  to_string(score));
}
// Render the score text on the window
void SnakeGame::renderScore(sf::RenderWindow &window)
{
    window.draw(scoreText);
}
char SnakeGame::getDirection() const
{
    return direction;
}

void SnakeGame::setDirection(const char &newDirection)
{
    direction = newDirection;
}
// Handle keyboard input for direction
void SnakeGame::handleInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up && direction != 'd')
    {
        direction = 'u';
    }
    else if (key == sf::Keyboard::Down && direction != 'u')
    {
        direction = 'd';
    }
    else if (key == sf::Keyboard::Left && direction != 'r')
    {
        direction = 'l';
    }
    else if (key == sf::Keyboard::Right && direction != 'l')
    {
        direction = 'r';
    }
}
// Get the end game flag
bool SnakeGame::getEndGameFlag() const
{
    return endGameFlag;
}
