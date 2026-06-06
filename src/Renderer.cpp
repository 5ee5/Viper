#include "Renderer.hpp"

#include <array>
#include <string>

#include <ncurses.h>

#include "Config.hpp"

namespace {

constexpr short kColorTitle = 1;
constexpr short kColorBorder = 2;
constexpr short kColorSnakeHead = 3;
constexpr short kColorSnakeBody = 4;
constexpr short kColorHighlight = 13;
constexpr short kColorInfo = 14;

const char* difficultyLabel(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy:
            return "Easy";
        case Difficulty::Normal:
            return "Normal";
        case Difficulty::Hard:
            return "Hard";
    }
    return "Normal";
}

}  // namespace

Renderer::Renderer() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    initColors();
}

Renderer::~Renderer() {
    endwin();
}

void Renderer::drawStartScreen(int selectedIndex, int highScore) const {
    clear();
    attron(COLOR_PAIR(kColorTitle) | A_BOLD);
    centerText(3, "VIPER");
    attroff(COLOR_PAIR(kColorTitle) | A_BOLD);

    centerText(5, "Neon snake across a wrapped arena", kColorInfo);
    centerText(7, "Select difficulty", kColorInfo);

    const std::array<std::string, 3> options {"Easy", "Normal", "Hard"};
    for (int i = 0; i < static_cast<int>(options.size()); ++i) {
        const bool selected = i == selectedIndex;
        const std::string label = selected ? "> " + options[static_cast<std::size_t>(i)] + " <" : options[static_cast<std::size_t>(i)];
        centerText(10 + i * 2, label, selected ? kColorHighlight : kColorInfo);
    }

    centerText(17, "Move: WASD or arrow keys", kColorInfo);
    centerText(18, "Enter or Space: start", kColorInfo);
    centerText(20, "High score: " + std::to_string(highScore), kColorTitle);
    refresh();
}

void Renderer::drawGame(const Snake& snake, const FrameData& frame) const {
    clear();

    attron(COLOR_PAIR(kColorInfo));
    mvprintw(1, 2, "Score: %d", frame.score);
    mvprintw(1, 16, "Best: %d", frame.highScore);
    mvprintw(1, 30, "Mode: %s", difficultyLabel(frame.difficulty));
    mvprintw(1, 44, "Speed: %dms", frame.speedMs);
    attroff(COLOR_PAIR(kColorInfo));

    for (const Position& border : frame.borders) {
        attron(COLOR_PAIR(kColorBorder));
        mvaddch(border.y + 3, border.x + 2, '#');
        attroff(COLOR_PAIR(kColorBorder));
    }

    const FoodDefinition& currentFood = foodDefinition(frame.currentFood.type);
    attron(COLOR_PAIR(currentFood.colorPair) | A_BOLD);
    mvaddch(frame.currentFood.position.y + 3, frame.currentFood.position.x + 2, frame.currentFood.glyph());
    attroff(COLOR_PAIR(currentFood.colorPair) | A_BOLD);

    const auto& segments = snake.segments();
    for (std::size_t i = 0; i < segments.size(); ++i) {
        const Position& segment = segments[i];
        const short color = i == 0 ? kColorSnakeHead : kColorSnakeBody;
        attron(COLOR_PAIR(color) | (i == 0 ? A_BOLD : A_NORMAL));
        mvaddch(segment.y + 3, segment.x + 2, i == 0 ? 'O' : 'o');
        attroff(COLOR_PAIR(color) | (i == 0 ? A_BOLD : A_NORMAL));
    }

    attron(COLOR_PAIR(kColorInfo));
    mvprintw(27, 2, "Controls: Arrows/WASD   Wrap through walls. Avoid your body.");
    mvprintw(28, 2, "@=1 Apple  $=3 Gem  *=5 Star  0=7 Ring");
    mvprintw(29, 2, "!=9 Bolt  +=11 Plus  &=13 Coin  ^=15 Crown");
    attroff(COLOR_PAIR(kColorInfo));
    refresh();
}

void Renderer::drawGameOver(int score, int highScore, bool newHighScore) const {
    clear();
    attron(COLOR_PAIR(kColorTitle) | A_BOLD);
    centerText(6, "GAME OVER");
    attroff(COLOR_PAIR(kColorTitle) | A_BOLD);

    centerText(10, "Score: " + std::to_string(score), kColorInfo);
    centerText(12, "High score: " + std::to_string(highScore), newHighScore ? kColorHighlight : kColorInfo);
    if (newHighScore) {
        centerText(14, "New high score", kColorHighlight);
    }

    centerText(18, "Press R to restart", kColorInfo);
    centerText(19, "Press Q or Esc to quit", kColorInfo);
    refresh();
}

void Renderer::drawMessage(const std::string& message) const {
    clear();
    centerText(LINES / 2, message, kColorInfo);
    refresh();
}

void Renderer::initColors() const {
    if (!has_colors()) {
        return;
    }

    start_color();
    use_default_colors();
    init_pair(kColorTitle, COLOR_GREEN, -1);
    init_pair(kColorBorder, COLOR_CYAN, -1);
    init_pair(kColorSnakeHead, COLOR_YELLOW, -1);
    init_pair(kColorSnakeBody, COLOR_GREEN, -1);
    init_pair(5, COLOR_RED, -1);
    init_pair(6, COLOR_MAGENTA, -1);
    init_pair(7, COLOR_YELLOW, -1);
    init_pair(8, COLOR_CYAN, -1);
    init_pair(9, COLOR_BLUE, -1);
    init_pair(10, COLOR_GREEN, -1);
    init_pair(11, COLOR_YELLOW, -1);
    init_pair(12, COLOR_WHITE, -1);
    init_pair(kColorHighlight, COLOR_WHITE, COLOR_BLUE);
    init_pair(kColorInfo, COLOR_WHITE, -1);
}

void Renderer::centerText(int row, const std::string& text, int colorPair) const {
    const int col = (COLS - static_cast<int>(text.size())) / 2;
    if (colorPair != 0) {
        attron(COLOR_PAIR(colorPair));
    }
    mvprintw(row, std::max(0, col), "%s", text.c_str());
    if (colorPair != 0) {
        attroff(COLOR_PAIR(colorPair));
    }
}
