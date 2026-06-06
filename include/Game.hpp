#pragma once

#include <random>
#include <vector>

#include "Food.hpp"
#include "Renderer.hpp"
#include "Snake.hpp"
#include "Types.hpp"

struct GameResult {
    int score {};
    bool newHighScore {};
};

class Game {
public:
    Game(Renderer& renderer, int boardWidth, int boardHeight, Difficulty difficulty, int highScore);

    GameResult run();

private:
    void reset();
    void processInput(int input);
    void update();
    void spawnFood();
    FoodType randomFoodType();
    int currentDelay() const;
    bool isBorder(const Position& pos) const;
    std::vector<Position> buildBorders() const;

    int boardWidth_;
    int boardHeight_;
    Difficulty difficulty_;
    int highScore_;
    Renderer& renderer_;
    int score_ {};
    bool gameOver_ {};
    Snake snake_;
    Food food_ {};
    std::mt19937 rng_;
};
