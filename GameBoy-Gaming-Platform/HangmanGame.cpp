#include "HangmanGame.h"
#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

// Empty implementation of the HangmanGame class methods for now
void HangmanGame::run() {}
void HangmanGame::render() {}
void HangmanGame::end() {}
void HangmanGame::update() {}
bool HangmanGame::isGameOver() const {}

// Category methods

// Selects a random word from the list and initializes the hidden word with '*'
void Category::selectRandomWord()
{
    srand(time(0)); // Initialize random seed based on current time
    int random_pick = rand() % 10; // Randomly pick an index from the list of 10 words
    strcpy(word, words_list[random_pick]); // Copy selected word to word
    memset(word_hidden, '*', strlen(word)); // Initialize hidden word with '*' characters
    word_hidden[strlen(word)] = '\0'; // Null-terminate the hidden word
}

// Returns the actual word (the one to guess)
const char *Category::getWord() const
{
    return word;
}

// Returns the current hidden word (with '*' characters where the word is hidden)
const char *Category::getHiddenWord() const
{
    return word_hidden;
}

// Updates the hidden word based on the user's guess
void Category::updateHiddenWord(char guess)
{
    bool found = false;
    for (int i = 0; word[i] != '\0'; ++i) // Loop through the word to check for the guessed character
    {
        if (tolower(word[i]) == tolower(guess)) // If the guess matches a character, update it in the hidden word
        {
            word_hidden[i] = word[i]; // Update the hidden word with the correct character
            found = true;
        }
    }
    if (!found) // If the guessed character was not found, reduce life by 1
    {
        --life;
    }
}

// Checks if the game is over (either all lives are lost or the word is guessed)
bool Category::isGameOver() const
{
    return life == 0 || strcmp(word, word_hidden) == 0; // Game ends if lives are 0 or the word is guessed
}

// Checks if the player has won (word is completely guessed)
bool Category::isWin() const
{
    return strcmp(word, word_hidden) == 0; // Win if the word is fully revealed
}

// Returns the number of lives left
int Category::getLives() const
{
    return life;
}

// Resets the number of lives to 6
void Category::resetLives()
{
    life = 6; // Start with 6 lives
}

// Countries class methods

// Populates the word list for countries
void Countries::populateWordsList()
{
    const char *temp_words_list[] = {"china", "india", "spain", "italy", "egypt", "brazil", "france", "germany", "australia", "canada"};
    for (int i = 0; i < 10; ++i)
    {
        strcpy(words_list[i], temp_words_list[i]); // Copy the words into the words_list
    }
}

// Returns the category name ("Countries")
const char *Countries::getCategoryName() const
{
    return "Countries";
}

// Cities class methods

// Populates the word list for cities
void Cities::populateWordsList()
{
    const char *temp_words_list[] = {"paris", "london", "tokyo", "dubai", "berlin", "newyork", "mumbai", "sydney", "amsterdam", "rome"};
    for (int i = 0; i < 10; ++i)
    {
        strcpy(words_list[i], temp_words_list[i]); // Copy the words into the words_list
    }
}

// Returns the category name ("Cities")
const char *Cities::getCategoryName() const
{
    return "Cities";
}

// Cars class methods

// Populates the word list for car brands
void Cars::populateWordsList()
{
    const char *temp_words_list[] = {"tesla", "bmw", "audi", "ford", "kia", "chevy", "toyota", "honda", "mercedes", "nissan"};
    for (int i = 0; i < 10; ++i)
    {
        strcpy(words_list[i], temp_words_list[i]); // Copy the words into the words_list
    }
}

// Returns the category name ("Cars")
const char *Cars::getCategoryName() const
{
    return "Cars";
}

// Hangman class methods

// Constructor for HangmanGame, initializes the window and other variables
HangmanGame::HangmanGame(sf::RenderWindow *window) : Game(window), currentCategory(nullptr), game_over(false)
{
    this->window = window; // Assign window to member variable
}

// Draws the hangman graphics based on the number of lives remaining
void HangmanGame::drawHangman(sf::RenderWindow *window, int lives)
{
    sf::Color hangmanColor = sf::Color::Red;
    sf::Color ropeColor = sf::Color::Yellow;
    sf::Color poleColor = sf::Color::Blue;

    // Draw base of the hangman
    sf::RectangleShape base(sf::Vector2f(200, 10));
    base.setPosition(150, 500);
    base.setFillColor(poleColor);
    window->draw(base);

    // Draw the pole
    sf::RectangleShape pole(sf::Vector2f(10, 300));
    pole.setPosition(220, 200);
    pole.setFillColor(poleColor);
    window->draw(pole);

    // Draw the beam
    sf::RectangleShape beam(sf::Vector2f(150, 10));
    beam.setPosition(220, 200);
    beam.setFillColor(poleColor);
    window->draw(beam);

    // Draw the rope
    sf::RectangleShape rope(sf::Vector2f(5, 50));
    rope.setPosition(360, 210);
    rope.setFillColor(ropeColor);
    window->draw(rope);

    // Draw different body parts depending on the remaining lives
    if (lives <= 5) // Head
    { 
        sf::CircleShape head(30);
        head.setPosition(340, 260);
        head.setFillColor(sf::Color::Transparent);
        head.setOutlineThickness(5);
        head.setOutlineColor(hangmanColor);
        window->draw(head);
    }
    if (lives == 0) // Eyes
    { 
        sf::Vertex leftEye[] = {
            sf::Vertex(sf::Vector2f(360, 280), sf::Color::White),
            sf::Vertex(sf::Vector2f(370, 290), sf::Color::White),
            sf::Vertex(sf::Vector2f(370, 280), sf::Color::White),
            sf::Vertex(sf::Vector2f(360, 290), sf::Color::White)};
        window->draw(leftEye, 4, sf::Lines);

        sf::Vertex rightEye[] = {
            sf::Vertex(sf::Vector2f(380, 280), sf::Color::White),
            sf::Vertex(sf::Vector2f(390, 290), sf::Color::White),
            sf::Vertex(sf::Vector2f(390, 280), sf::Color::White),
            sf::Vertex(sf::Vector2f(380, 290), sf::Color::White)};
        window->draw(rightEye, 4, sf::Lines);
    }
    if (lives <= 4) // Body
    { 
        sf::RectangleShape body(sf::Vector2f(10, 100));
        body.setPosition(366, 326);
        body.setFillColor(hangmanColor);
        window->draw(body);
    }
    if (lives <= 3) // Left Arm
    { 
        sf::RectangleShape leftArm(sf::Vector2f(60, 5));
        leftArm.setPosition(370, 326);
        leftArm.setRotation(135);
        leftArm.setFillColor(hangmanColor);
        window->draw(leftArm);
    }
    if (lives <= 2) // Right Arm
    { 
        sf::RectangleShape rightArm(sf::Vector2f(60, 5));
        rightArm.setPosition(374, 322);
        rightArm.setRotation(45);
        rightArm.setFillColor(hangmanColor);
        window->draw(rightArm);
    }
    if (lives <= 1) // Left Leg
    { 
        sf::RectangleShape leftLeg(sf::Vector2f(60, 5));
        leftLeg.setPosition(370, 426);
        leftLeg.setRotation(135);
        leftLeg.setFillColor(hangmanColor);
        window->draw(leftLeg);
    }
    if (lives <= 0) // Right Leg
    { 
        sf::RectangleShape rightLeg(sf::Vector2f(60, 5));
        rightLeg.setPosition(374, 421);
        rightLeg.setRotation(45);
        rightLeg.setFillColor(hangmanColor);
        window->draw(rightLeg);
    }
}

// Displays the category selection menu and sets the current category based on user input
void HangmanGame::selectCategory(sf::RenderWindow *window, sf::Font &font)
{
    sf::Text title, countriesButton, citiesButton, carsButton;

    // Set up title
    title.setFont(font);
    title.setString("Select a Category");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 50);

    // Set up buttons for each category
    countriesButton.setFont(font);
    countriesButton.setString("1. Countries");
    countriesButton.setCharacterSize(30);
    countriesButton.setFillColor(sf::Color::White);
    countriesButton.setPosition(250, 150);

    citiesButton.setFont(font);
    citiesButton.setString("2. Cities");
    citiesButton.setCharacterSize(30);
    citiesButton.setFillColor(sf::Color::White);
    citiesButton.setPosition(250, 250);

    carsButton.setFont(font);
    carsButton.setString("3. Cars");
    carsButton.setCharacterSize(30);
    carsButton.setFillColor(sf::Color::White);
    carsButton.setPosition(250, 350);

    // Event loop to handle category selection
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                {
                    currentCategory = new Countries(); // Set category to Countries
                    return;
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    currentCategory = new Cities(); // Set category to Cities
                    return;
                }
                else if (event.key.code == sf::Keyboard::Num3)
                {
                    currentCategory = new Cars(); // Set category to Cars
                    return;
                }
            }
        }

        window->clear(sf::Color::Black); // Clear the window with black background
        window->draw(title);
        window->draw(countriesButton);
        window->draw(citiesButton);
        window->draw(carsButton);
        window->display();
    }
}

// Starts the Hangman game by loading the font, selecting a category, and initializing the game state
void HangmanGame::start()
{
    if (!font.loadFromFile("Sansation_Bold_Italic.ttf")) // Check if font is loaded successfully
    {
         cout << "Error loading font!" << endl; // Print error if font fails to load
        return;
    }

    selectCategory(window, font); // Let the player choose a category
    currentCategory->populateWordsList(); // Populate words for the selected category
    currentCategory->resetLives(); // Reset lives to 6
    currentCategory->selectRandomWord(); // Select a random word from the list

    // Main game loop
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            // Handle user input for guesses (only if the game isn't over)
            if (!game_over && event.type == sf::Event::TextEntered)
            {
                char guess = static_cast<char>(event.text.unicode); // Convert entered character to char
                if (isalpha(guess)) // Only process alphabetic characters
                {
                    currentCategory->updateHiddenWord(guess); // Update the hidden word with the guess
                    game_over = currentCategory->isGameOver(); // Check if the game is over
                }
            }
        }

        window->clear(sf::Color::Black); // Set background color to black
        drawHangman(window, currentCategory->getLives()); // Draw the hangman based on lives

        // Set up text to display the current game state
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);

        // Display win or loss message if game is over
        if (game_over)
        {
            if (currentCategory->isWin())
            {
                text.setString("You Win! The word was: " + string(currentCategory->getWord()));
            }
            else
            {
                text.setString("You Lose! The word was: " + string(currentCategory->getWord()));
            }
        }
        else // Display ongoing game info
        {
            text.setString("Category: " + string(currentCategory->getCategoryName()) +
                           "\nWord: " + string(currentCategory->getHiddenWord()) +
                           "\nLives: " + to_string(currentCategory->getLives()));
        }

        text.setPosition(50, 50); // Position the text
        window->draw(text);

        window->display(); // Display the updated window
    }

    delete currentCategory; // Clean up the dynamically allocated memory for the current category
}

