# Viper

`Viper` is a terminal snake game written in C++ with `ncurses`.

## Features

- Colored snake, food, and borders
- Wall wrapping
- Increasing speed as score rises
- Multiple food types with different point values
- Persistent high score tracking in `.highscore`
- Start screen with difficulty selection
- Game over screen with restart option

## Requirements

- CMake 3.16 or newer
- A C++17 compiler
- `ncurses` development libraries

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/Viper
```

## Controls

- `Arrow keys` or `WASD`: move
- `Enter` or `Space`: start game from the menu
- `R`: restart after game over
- `Q` or `Esc`: quit from the game over screen

## Project Structure

- `include/`: headers for game systems
- `src/`: implementation files
- `CMakeLists.txt`: build configuration
