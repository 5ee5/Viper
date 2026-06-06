#pragma once

struct Position {
    int x {};
    int y {};

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

enum class Difficulty {
    Easy,
    Normal,
    Hard
};

enum class FoodType {
    Apple,
    Gem,
    Star
};
