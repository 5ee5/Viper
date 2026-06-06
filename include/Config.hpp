#pragma once

#include "Types.hpp"

namespace config {

constexpr int kBoardWidth = 50;
constexpr int kBoardHeight = 22;

constexpr int kMinFrameDelayMs = 55;
constexpr int kSpeedIncreaseEveryPoints = 8;
constexpr int kSpeedStepMs = 4;

constexpr int kEasyDelayMs = 150;
constexpr int kNormalDelayMs = 120;
constexpr int kHardDelayMs = 95;

constexpr const char* kHighScoreFile = ".highscore";

inline int delayForDifficulty(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy:
            return kEasyDelayMs;
        case Difficulty::Normal:
            return kNormalDelayMs;
        case Difficulty::Hard:
            return kHardDelayMs;
    }
    return kNormalDelayMs;
}

}  // namespace config
