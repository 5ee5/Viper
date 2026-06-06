#pragma once

#include "Types.hpp"

struct Food {
    Position position {};
    FoodType type {FoodType::Apple};

    int points() const {
        switch (type) {
            case FoodType::Apple:
                return 1;
            case FoodType::Gem:
                return 3;
            case FoodType::Star:
                return 5;
        }
        return 1;
    }

    char glyph() const {
        switch (type) {
            case FoodType::Apple:
                return '@';
            case FoodType::Gem:
                return '$';
            case FoodType::Star:
                return '*';
        }
        return '@';
    }
};
