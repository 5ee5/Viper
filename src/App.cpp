#include "App.hpp"

#include <array>
#include <ncurses.h>

#include "Config.hpp"
#include "Game.hpp"

App::App()
    : highScore_(config::kHighScoreFile) {}

void App::run() {
    while (true) {
        const Difficulty difficulty = showStartScreen();
        Game game(renderer_, config::kBoardWidth, config::kBoardHeight, difficulty, highScore_.load());
        const GameResult result = game.run();
        highScore_.saveIfHigher(result.score);
        if (!showGameOverScreen(result.score, result.newHighScore)) {
            break;
        }
    }
}

Difficulty App::showStartScreen() {
    const std::array<Difficulty, 3> options {
        Difficulty::Easy,
        Difficulty::Normal,
        Difficulty::Hard,
    };

    int selectedIndex = 1;

    while (true) {
        renderer_.drawStartScreen(selectedIndex, highScore_.load());
        const int input = getch();

        switch (input) {
            case KEY_UP:
            case 'w':
            case 'W':
                selectedIndex = (selectedIndex + static_cast<int>(options.size()) - 1) % static_cast<int>(options.size());
                break;
            case KEY_DOWN:
            case 's':
            case 'S':
                selectedIndex = (selectedIndex + 1) % static_cast<int>(options.size());
                break;
            case '\n':
            case KEY_ENTER:
            case ' ':
                return options[static_cast<std::size_t>(selectedIndex)];
            default:
                break;
        }
    }
}

bool App::showGameOverScreen(int score, bool newHighScore) {
    const int bestScore = highScore_.load();
    renderer_.drawGameOver(score, bestScore, newHighScore);

    while (true) {
        const int input = getch();
        if (input == 'r' || input == 'R') {
            return true;
        }
        if (input == 'q' || input == 'Q' || input == 27) {
            return false;
        }
    }
}
