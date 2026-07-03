# GameBoy Gaming Platform

Compile the project with g++ and run the generated executable.

## Build

```bash
g++ -std=c++11 -o gameboy main.cpp Game.cpp HangmanGame.cpp GameBoy.cpp SnakeGame.cpp WordleGame.cpp Player.cpp Menu.cpp InputSystem.cpp SoundSystem.cpp \
  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

## Run

```bash
./gameboy
```

## Notes

- This project uses SFML for graphics and audio.
- Keep the audio files and fonts in the same folder as the executable when running.
