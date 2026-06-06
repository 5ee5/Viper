#include "Game.hpp"

#include <algorithm>
#include <chrono>
#include <thread>

#include <ncurses.h>

#include "Config.hpp"
#include "Renderer.hpp"

Game::Game(Renderer& renderer, int boardWidth, int boardHeight, Difficulty difficulty, int highScore)
    : boardWidth_(boardWidth),
      boardHeight_(boardHeight),
      difficulty_(difficulty),
      highScore_(highScore),
      renderer_(renderer),
      rng_(static_cast<std::mt19937::result_type>(
          std::chrono::steady_clock::now().time_since_epoch().count())) {
    reset();
}

GameResult Game::run() {
    gameOver_ = false;

    while (!gameOver_) {
        timeout(currentDelay());
        processInput(getch());
        update();

        FrameData frame;
        frame.score = score_;
        frame.highScore = std::max(highScore_, score_);
        frame.difficulty = difficulty_;
        frame.speedMs = currentDelay();
        frame.currentFood = food_;
        frame.borders = buildBorders();
        renderer_.drawGame(snake_, frame);
    }

    return GameResult {
        score_,
        score_ > highScore_,
    };
}

void Game::reset() {
    score_ = 0;
    gameOver_ = false;
    snake_.reset();
    spawnFood();
}

void Game::processInput(int input) {
    switch (input) {
        case KEY_UP:
        case 'w':
        case 'W':
            snake_.setDirection(Direction::Up);
            break;
        case KEY_DOWN:
        case 's':
        case 'S':
            snake_.setDirection(Direction::Down);
            break;
        case KEY_LEFT:
        case 'a':
        case 'A':
            snake_.setDirection(Direction::Left);
            break;
        case KEY_RIGHT:
        case 'd':
        case 'D':
            snake_.setDirection(Direction::Right);
            break;
        default:
            break;
    }
}

void Game::update() {
    const Position newHead = snake_.nextHeadPosition(boardWidth_, boardHeight_);
    const bool ateFood = newHead == food_.position;

    if (snake_.hitsBody(newHead, !ateFood)) {
        gameOver_ = true;
        return;
    }

    snake_.moveTo(newHead, ateFood);

    if (ateFood) {
        score_ += food_.points();
        spawnFood();
    }
}

void Game::spawnFood() {
    std::uniform_int_distribution<int> xDist(1, boardWidth_ - 2);
    std::uniform_int_distribution<int> yDist(1, boardHeight_ - 2);

    Position pos {};
    do {
        pos = Position {xDist(rng_), yDist(rng_)};
    } while (snake_.occupies(pos));

    food_.position = pos;
    food_.type = randomFoodType();
}

FoodType Game::randomFoodType() {
    int totalWeight = 0;
    for (const auto& definition : kFoodDefinitions) {
        totalWeight += definition.spawnWeight;
    }

    std::uniform_int_distribution<int> dist(1, totalWeight);
    int roll = dist(rng_);

    for (const auto& definition : kFoodDefinitions) {
        roll -= definition.spawnWeight;
        if (roll <= 0) {
            return definition.type;
        }
    }

    return kFoodDefinitions.front().type;
}

int Game::currentDelay() const {
    const int baseDelay = config::delayForDifficulty(difficulty_);
    const int speedBonus = (score_ / config::kSpeedIncreaseEveryPoints) * config::kSpeedStepMs;
    return std::max(config::kMinFrameDelayMs, baseDelay - speedBonus);
}

bool Game::isBorder(const Position& pos) const {
    return pos.x == 0 || pos.y == 0 || pos.x == boardWidth_ - 1 || pos.y == boardHeight_ - 1;
}

std::vector<Position> Game::buildBorders() const {
    std::vector<Position> borders;
    borders.reserve(static_cast<std::size_t>(boardWidth_ * 2 + boardHeight_ * 2));

    for (int x = 0; x < boardWidth_; ++x) {
        borders.push_back(Position {x, 0});
        borders.push_back(Position {x, boardHeight_ - 1});
    }

    for (int y = 1; y < boardHeight_ - 1; ++y) {
        borders.push_back(Position {0, y});
        borders.push_back(Position {boardWidth_ - 1, y});
    }

    return borders;
}
