#pragma once

#include <string>
#include <vector>

#include "Food.hpp"
#include "Snake.hpp"
#include "Types.hpp"

struct FrameData {
    int score {};
    int highScore {};
    Difficulty difficulty {Difficulty::Normal};
    int speedLevel {};
    Food currentFood {};
    std::vector<Position> borders;
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    void drawStartScreen(int selectedIndex, int highScore) const;
    void drawGame(const Snake& snake, const FrameData& frame) const;
    void drawGameOver(int score, int highScore, bool newHighScore) const;
    void drawMessage(const std::string& message) const;

private:
    void initColors() const;
    void centerText(int row, const std::string& text, int colorPair = 0) const;
};
