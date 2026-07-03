#include "WordleGame.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring> // For string manipulation
#include <SFML/Audio.hpp>
using namespace std;

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 800;
const int CELL_SIZE = 35;
const int GRID_PADDING = 275;

// Constructor for WordleGame class
WordleGame::WordleGame(sf::RenderWindow *window) : Game(window), attemptsLeft(6), score(0)
{
    this->window = window;

    if (!window)
    {
         cerr << "Window pointer is null!" <<  endl;
        exit(1); // Exit if window pointer is invalid
    }

    // Print window size to debug
     cerr << "Window size: " << window->getSize().x << "x" << window->getSize().y <<  endl;

    // Load words from file
    loadFromFile("word_list.txt"); // Adjust the filename as needed

    srand(time(0));                     // Initialize random seed
    int wordIndex = rand() % wordCount; // Pick a random word from the list

    // Convert target word to C-string
     string targetWordStr = wordList[wordIndex];
    strncpy(targetWord, targetWordStr.c_str(), 6);
    targetWord[5] = '\0'; // Ensure null-termination

    // Debugging: print the target word to ensure it's correctly assigned
     cerr << "Target word: " << targetWord <<  endl;

    // Initialize currentGuess to all null characters
    memset(currentGuess, 0, sizeof(currentGuess)); // Clear out any junk data in currentGuess

    // Load font for SFML text
    if (!font.loadFromFile("Montserrat-Light.otf"))
    { // Ensure font is loaded correctly
         cerr << "Failed to load font!" <<  endl;
        exit(1);
    }
    if (!soundSystem.loadBackgroundMusic("background_pink.mp3"))
    {
         cerr << "Error loading background music!" <<  endl;
        exit(1); // Exit if the music file is not loaded
    }

    soundSystem.playBackgroundMusic(); //

    // Initialize cell colors and tries arrays
    for (int i = 0; i < MAX_ATTEMPTS; ++i)
    {
        for (int j = 0; j < WORD_LENGTH; ++j)
        {
            cellColors[i][j] = CELL_EMPTY;
            previousTries[i][j] = '\0';
        }
    }

    for (int i = 0; i < MAX_ATTEMPTS; ++i)
    {
        memset(previousTries[i], 0, sizeof(previousTries[i]));
    }

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
}

void WordleGame::loadFromFile(const  string &filename)
{
     ifstream file(filename);
    if (!file.is_open())
    {
         cerr << "Error: Could not open word list file " << filename <<  endl;
        exit(1); // Exit if file can't be opened
    }

     string word;
    wordCount = 0;
    while (file >> word && wordCount < MAX_WORDS)
    {
        // Convert word to lowercase
         transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Only add 5-letter words
        if (word.length() == 5)
        {
            wordList[wordCount++] = word;
        }
    }
    file.close();

    if (wordCount == 0)
    {
         cerr << "Error: No valid words found in the file." <<  endl;
        exit(1);
    }
}
// Start the game
void WordleGame::start()
{
     cout << "Wordle Game Started!" <<  endl;

    run(); // Call the run method to start the game loop
}

// Handle Input
void WordleGame::handleInput(sf::Uint32 unicode)
{
    if (unicode >= 'a' && unicode <= 'z' && strlen(currentGuess) < 5)
    {
        currentGuess[strlen(currentGuess)] = static_cast<char>(unicode);
    }
    else if (unicode == 8 && strlen(currentGuess) > 0)
    { // Handle backspace
        currentGuess[strlen(currentGuess) - 1] = '\0';
    }
}

// Main game loop
// Modify run() to handle end screen events
void WordleGame::run()
{
    feedback = "";

    bool playing = true;

    while (playing && window->isOpen())
    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                // window->close();
                return;
                playing = false;
            }

            // If game is not over, handle normal input
            if (!isGameOver())
            {
                if (event.type == sf::Event::TextEntered)
                {
                    handleInput(event.text.unicode);
                }
            }
            soundSystem.playSound("click.mp3");
        }

        // Existing game logic
        if (!isGameOver())
        {
            if (strlen(currentGuess) == WORD_LENGTH)
            {
                if (validateGuess(currentGuess))
                {
                    updateCellColors(currentGuess);

                    if (compareStrings(currentGuess, targetWord))
                    {
                        score += (attemptsLeft * 10);
                        attemptsLeft = -1; // Win condition
                    }

                    // Only reset and decrement attempts if the guess is valid
                    memset(currentGuess, 0, sizeof(currentGuess));
                    --attemptsLeft;
                }
                else
                {
                    // If guess is invalid, just clear the current guess
                    memset(currentGuess, 0, sizeof(currentGuess));
                }
            }
        }

        render();
    }
}

// // Display the current game status (attempts left and other details)
// void WordleGame::displayGameStatus()
// {
//     text.setString("Attempts left: " +  to_string(attemptsLeft));
//     text.setPosition(10.f, 10.f);
//     window->draw(text);

//     text.setString("Enter your guess (5-letter word): ");
//     text.setPosition(10.f, 50.f);
//     window->draw(text);

//     window->display(); // Refresh the window to show the updated content
// }
void WordleGame::updateCellColors(const char *guess)
{
    // Find the correct row index
    int currentAttempt = MAX_ATTEMPTS - attemptsLeft;

    // Ensure we don't go out of bounds
    if (currentAttempt < 0 || currentAttempt >= MAX_ATTEMPTS)
    {
         cerr << "Invalid attempt index: " << currentAttempt <<  endl;
        return;
    }

    // Copy current guess to previous tries
    strncpy(previousTries[currentAttempt], guess, WORD_LENGTH);
    previousTries[currentAttempt][WORD_LENGTH] = '\0'; // Null-terminate

    // Determine cell colors
    for (int i = 0; i < WORD_LENGTH; ++i)
    {
        if (guess[i] == targetWord[i])
        {
            // Correct letter in correct position
            cellColors[currentAttempt][i] = CELL_CORRECT;
        }
        else if (containsChar(targetWord, guess[i]))
        {
            // Letter exists in word but wrong position
            cellColors[currentAttempt][i] = CELL_MISPLACED;
        }
        else
        {
            // Letter not in word
            cellColors[currentAttempt][i] = CELL_INCORRECT;
        }
    }
}

void WordleGame::drawGameStatus()
{
    // Title
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("WORDLE");

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top);
    titleText.setPosition((WINDOW_WIDTH / 2.0f) + 75, 25);
    window->draw(titleText);

    // Attempts Left
    sf::Text attemptsText;
    attemptsText.setFont(font);
    attemptsText.setCharacterSize(24);
    attemptsText.setFillColor(sf::Color(200, 200, 200));
    attemptsText.setString("Attempts Left: " +  to_string(attemptsLeft));
    attemptsText.setPosition(GRID_PADDING, 100);
    window->draw(attemptsText);
    // // Display the score
    // sf::Text scoreText;
    // scoreText.setFont(font);
    // scoreText.setCharacterSize(24);
    // scoreText.setFillColor(sf::Color(200, 200, 200));
    // scoreText.setString("Score: " +  to_string(score));
    // scoreText.setPosition(GRID_PADDING, 140);
    // window->draw(scoreText);
    // Feedback Text
    if (!feedback.empty())
    {
        sf::Text feedbackText;
        feedbackText.setFont(font);
        feedbackText.setCharacterSize(20);
        feedbackText.setFillColor(sf::Color::Yellow);
        feedbackText.setString(feedback);

        sf::FloatRect feedbackBounds = feedbackText.getLocalBounds();
        feedbackText.setOrigin(feedbackBounds.left + feedbackBounds.width / 2.0f, feedbackBounds.top);
        feedbackText.setPosition((WINDOW_WIDTH / 2.0f) + 100, 75);
        window->draw(feedbackText);
    }
}

// Validate the player's guess (checks if it is a valid 5-letter word)
bool WordleGame::validateGuess(const char *guess)
{
    if (strlen(guess) != 5)
    {
        feedback = "Invalid guess. Please enter a 5-letter word.";
        return false;
    }

     string guessStr(guess);

     transform(guessStr.begin(), guessStr.end(), guessStr.begin(), ::tolower);

    bool validWord = false;
    for (int i = 0; i < wordCount; ++i)
    {
        if (wordList[i] == guessStr)
        {
            validWord = true;
            break;
        }
    }

    if (!validWord)
    {
        feedback = "The word is not in the list. Please try again.";
    }
    else
    {
        // Clear feedback if the word is valid
        feedback = "";
    }

    return validWord;
}
// Provide feedback after each guess
void WordleGame::provideFeedback()
{
     string feedback = "Feedback: ";
    for (int i = 0; i < 5; ++i)
    {
        if (currentGuess[i] == targetWord[i])
        {
            feedback += currentGuess[i]; // Correct letter, correct position
            feedback += " (Green) ";
        }
        else if (containsChar(targetWord, currentGuess[i]))
        {
            feedback += currentGuess[i]; // Correct letter, wrong position
            feedback += " (Yellow) ";
        }
        else
        {
            feedback += currentGuess[i]; // Incorrect letter
            feedback += " (Gray) ";
        }
    }

    this->feedback = feedback;
}

// Copy a C-string (null-terminated) into another with a max length
void WordleGame::copyCString(char *dest, const char *src, int maxLength)
{
    for (int i = 0; i < maxLength; ++i)
    {
        dest[i] = src[i];
    }
    dest[maxLength - 1] = '\0'; // Null-terminate the string
}
// Compare two C-strings
bool WordleGame::compareStrings(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
        ++i;
    }
    return str1[i] == str2[i];
}

// Check if a character is contained in a string
bool WordleGame::containsChar(const char *str, char ch)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ch)
        {
            return true;
        }
        ++i;
    }
    return false;
}

// Implement the abstract methods from Game class
void WordleGame::end()
{
     cout << "Game Over! The correct word was: " << targetWord <<  endl;
}

bool WordleGame::isGameOver() const
{
    return attemptsLeft <= 0; // Game is over if no attempts left
}

// Render Game State
void WordleGame::render()
{
    window->clear(sf::Color(20, 20, 20)); // Dark background

    // If game is over, render end screen
    if (isGameOver())
    {
        renderEndScreen();
        return;
    }

    // Draw game grid
    drawGameGrid();

    // Draw current status information
    drawGameStatus();

    // Draw keyboard
    drawGameKeyboard();

    window->display();
}

void WordleGame::drawGameKeyboard()
{
    // Create keyboard layout with rows and columns
     vector< string> keyboardRows = {
        "QWERTYUIOP", // Row 1
        "ASDFGHJKL",  // Row 2
        "ZXCVBNM"     // Row 3
    };

    // Keyboard positions
    float xOffset = 200.0f;  // Start position for the keyboard
    float yOffset = 450.0f;  // Position from the top for the keyboard rows
    float keyWidth = 35.0f;  // Width of each key
    float keyHeight = 35.0f; // Height of each key
    float xSpacing = 5.0f;   // Horizontal spacing between keys
    float ySpacing = 5.0f;   // Vertical spacing between rows

    // Loop through each row in the keyboard
    for (int row = 0; row < keyboardRows.size(); ++row)
    {
        const  string &rowString = keyboardRows[row];

        // Loop through each key in the row
        for (int col = 0; col < rowString.size(); ++col)
        {
            char letter = rowString[col];

            // Create a rectangle for the key
            sf::RectangleShape key(sf::Vector2f(keyWidth, keyHeight));
            key.setPosition(xOffset + col * (keyWidth + xSpacing), yOffset + row * (keyHeight + ySpacing));

            // Set color based on the letter's status (correct, misplaced, or incorrect)
            sf::Color keyColor = sf::Color(50, 50, 50); // Default: gray for unpressed keys

            // Check if the key is part of any previous guesses (to color based on status)
            for (int i = 0; i < MAX_ATTEMPTS; ++i)
            {
                for (int j = 0; j < WORD_LENGTH; ++j)
                {
                    //  cout << previousTries[i][j] <<  endl;
                    if (previousTries[i][j] == (letter + 32))
                    {
                        switch (cellColors[i][j])
                        {
                        case CELL_CORRECT:
                            keyColor = sf::Color(0, 128, 0); // Green for correct letter
                            break;
                        case CELL_MISPLACED:
                            keyColor = sf::Color(255, 165, 0); // Orange for misplaced letter
                            break;
                        case CELL_INCORRECT:
                            keyColor = sf::Color(128, 128, 128); // Gray for incorrect letter
                            break;
                        default:
                            keyColor = sf::Color(50, 50, 50); // Default color for unused letters
                        }
                    }
                }
            }

            // Set the key color
            key.setFillColor(keyColor);

            // Draw the key
            window->draw(key);

            // Set up the letter text on top of the key
            sf::Text letterText;
            letterText.setFont(font);
            letterText.setCharacterSize(24);
            letterText.setFillColor(sf::Color::White);
            letterText.setString( string(1, letter)); // Set the letter

            // Center the letter in the key
            sf::FloatRect bounds = letterText.getLocalBounds();
            letterText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
            letterText.setPosition(
                key.getPosition().x + keyWidth / 2.0f,
                key.getPosition().y + keyHeight / 2.0f);

            // Draw the letter on the key
            window->draw(letterText);
        }
    }
}

void WordleGame::drawGameGrid()
{
    // Create grid cells for guesses
    for (int row = 0; row < MAX_ATTEMPTS; ++row)
    {
        for (int col = 0; col < WORD_LENGTH; ++col)
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(
                GRID_PADDING + col * (CELL_SIZE + 10),
                150 + row * (CELL_SIZE + 10));

            // Set cell color based on game state
            if (row < MAX_ATTEMPTS - attemptsLeft)
            {
                // Previous tries
                switch (cellColors[row][col])
                {
                case CELL_CORRECT:
                    cell.setFillColor(sf::Color(0, 128, 0)); // Green
                    break;
                case CELL_MISPLACED:
                    cell.setFillColor(sf::Color(255, 165, 0)); // Orange
                    break;
                case CELL_INCORRECT:
                    cell.setFillColor(sf::Color(128, 128, 128)); // Gray
                    break;
                default:
                    cell.setFillColor(sf::Color(50, 50, 50));
                }

                // Add letter to the cell
                sf::Text letterText;
                letterText.setFont(font);
                letterText.setCharacterSize(36);

                // Ensure high contrast text color
                letterText.setFillColor(sf::Color::White); // Always white for visibility

                // Only set letter if it exists in the previous tries
                if (previousTries[row][col] != '\0')
                {
                    letterText.setString( string(1, previousTries[row][col]));

                    // Center the letter in the cell
                    sf::FloatRect bounds = letterText.getLocalBounds();
                    letterText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
                    letterText.setPosition(
                        cell.getPosition().x + CELL_SIZE / 2.0f,
                        cell.getPosition().y + CELL_SIZE / 2.0f);

                    window->draw(cell);
                    window->draw(letterText);
                }
                else
                {
                    window->draw(cell);
                }
            }
            else if (row == MAX_ATTEMPTS - attemptsLeft && col < strlen(currentGuess))
            {
                // Current guess
                cell.setFillColor(sf::Color(100, 100, 100)); // Light gray for current guess

                sf::Text letterText;
                letterText.setFont(font);
                letterText.setCharacterSize(36);
                letterText.setFillColor(sf::Color::White);
                letterText.setString( string(1, currentGuess[col]));

                // Center the letter in the cell
                sf::FloatRect bounds = letterText.getLocalBounds();
                letterText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
                letterText.setPosition(
                    cell.getPosition().x + CELL_SIZE / 2.0f,
                    cell.getPosition().y + CELL_SIZE / 2.0f);

                window->draw(cell);
                window->draw(letterText);
            }
            else
            {
                // Empty cells
                cell.setFillColor(sf::Color(50, 50, 50)); // Dark gray for empty cells
                window->draw(cell);
            }
        }
    }
}

void WordleGame::renderEndScreen()
{
    window->clear(sf::Color(30, 30, 30)); // Slightly different background

    // Game Over Text
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(attemptsLeft <= -1 ? sf::Color(0, 200, 0) : sf::Color(200, 0, 0));

    gameOverText.setString(attemptsLeft <= -1 ? "YOU WON!" : "YOU LOSE!");

    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverBounds.left + gameOverBounds.width / 2.0f,
                           gameOverBounds.top + gameOverBounds.height / 2.0f);
    gameOverText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - 100);
    window->draw(gameOverText);

    // Target Word
    sf::Text targetWordText;
    targetWordText.setFont(font);
    targetWordText.setCharacterSize(36);
    targetWordText.setFillColor(sf::Color::White);
    targetWordText.setString("The word was: " +  string(targetWord));

    sf::FloatRect targetWordBounds = targetWordText.getLocalBounds();
    targetWordText.setOrigin(targetWordBounds.left + targetWordBounds.width / 2.0f,
                             targetWordBounds.top + targetWordBounds.height / 2.0f);
    targetWordText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    window->draw(targetWordText);

    // Final Score
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color(0, 200, 0));
    scoreText.setString("Your Score: " +  to_string(score));

    sf::FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(scoreBounds.left + scoreBounds.width / 2.0f, scoreBounds.top + scoreBounds.height / 2.0f);
    scoreText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 50);
    window->draw(scoreText);

    // Restart/Close Instructions
    sf::Text instructionText;
    instructionText.setFont(font);
    instructionText.setCharacterSize(24);
    instructionText.setFillColor(sf::Color(150, 150, 150));
    instructionText.setString("Press ESC to Close");

    sf::FloatRect instructionBounds = instructionText.getLocalBounds();
    instructionText.setOrigin(instructionBounds.left + instructionBounds.width / 2.0f,
                              instructionBounds.top + instructionBounds.height / 2.0f);
    instructionText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 100);
    window->draw(instructionText);

    window->display();
}

void WordleGame::update()
{
    // Handle Input and update currentGuess
    if (strlen(currentGuess) == 5)
    { // When a full word is guessed
        if (validateGuess(currentGuess))
        {
            provideFeedback();

            if (compareStrings(currentGuess, targetWord))
            {

                score += (attemptsLeft * 10);
                 cout << "Congratulations! You guessed the word!" <<  endl;
                attemptsLeft = 0; // End the game
            }
        }

        memset(currentGuess, 0, sizeof(currentGuess)); // Reset guess
        --attemptsLeft;
    }
}
