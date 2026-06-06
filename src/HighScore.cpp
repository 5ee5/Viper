#include "HighScore.hpp"

#include <fstream>

HighScore::HighScore(std::filesystem::path filePath)
    : filePath_(std::move(filePath)) {}

int HighScore::load() const {
    std::ifstream input(filePath_);
    int score = 0;
    if (input >> score && score >= 0) {
        return score;
    }
    return 0;
}

void HighScore::saveIfHigher(int score) const {
    if (score <= load()) {
        return;
    }

    std::ofstream output(filePath_, std::ios::trunc);
    if (output) {
        output << score;
    }
}
