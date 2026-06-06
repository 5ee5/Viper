#pragma once

#include "HighScore.hpp"
#include "Renderer.hpp"
#include "Types.hpp"

class App {
public:
    App();

    void run();

private:
    Difficulty showStartScreen();
    bool showGameOverScreen(int score, bool newHighScore);

    Renderer renderer_;
    HighScore highScore_;
};
