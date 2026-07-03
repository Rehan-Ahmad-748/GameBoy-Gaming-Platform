# GameBoy Gaming Platform — Snake, Wordle & Hangman

A C++ gaming platform built as an Object-Oriented Programming project. Three classic games — Snake, Wordle, and Hangman — run under a single GameBoy-style interface with a unified menu, player profiles, achievements, and saved high scores. Every feature, from game logic to sound and UI, is built from scratch using OOP principles and SFML.

---

## What It Does

- **Snake** — classic snake gameplay with food, collision, and score tracking
- **Wordle** — word-guessing game with letter validation and attempt tracking  
- **Hangman** — word puzzle with lives system and a word list file
- Unified **GameBoy-style menu** to switch between games
- **Player profiles** with persistent high scores saved to file
- **Sound effects** and custom fonts throughout
- **Pause/resume**, game over screens, and settings

---

## OOP Concepts Applied

`Inheritance` `Polymorphism` `Abstract Classes` `Virtual Functions` `Encapsulation` `Composition` `Aggregation`

---

## Tech Stack

`C++` `SFML` `OOP` `File Handling` `GCC`

---

## Project Structure

```
Project/
├── main.cpp            → entry point
├── GameBoy.cpp/h       → main platform controller
├── Game.cpp/h          → base game class
├── SnakeGame.cpp/h     → snake game logic
├── WordleGame.cpp/h    → wordle game logic
├── HangmanGame.cpp/h   → hangman game logic
├── Player.cpp/h        → player profile and score management
├── Menu.cpp/h          → main menu system
├── InputSystem.cpp/h   → input handling
├── SoundSystem.cpp/h   → audio management
├── word_list.txt       → word bank for Wordle and Hangman
├── highest_score.txt   → persistent high score storage
├── *.ttf               → custom fonts
└── *.mp3 / *.wav       → sound effects
```

---

## How to Build

```bash
g++ -std=c++11 -o gameboy main.cpp Game.cpp HangmanGame.cpp GameBoy.cpp SnakeGame.cpp WordleGame.cpp Player.cpp Menu.cpp InputSystem.cpp SoundSystem.cpp \
  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

## How to Run

```bash
./gameboy
```

> Keep all audio files and fonts in the same folder as the executable, otherwise sounds and visuals will not load.

---

*Built as part of Object-Oriented Programming coursework at FAST-NUCES Islamabad.*
