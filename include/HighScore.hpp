#pragma once

#include <filesystem>

class HighScore {
public:
    explicit HighScore(std::filesystem::path filePath);

    int load() const;
    void saveIfHigher(int score) const;

private:
    std::filesystem::path filePath_;
};
