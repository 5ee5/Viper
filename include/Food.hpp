#pragma once

#include <array>
#include <string_view>

#include "Types.hpp"

struct FoodDefinition {
    FoodType type;
    std::string_view name;
    char glyph;
    short colorPair;
    int points;
    int spawnWeight;
};

inline constexpr std::array<FoodDefinition, 8> kFoodDefinitions {{
    {FoodType::Apple, "Apple", '@', 5, 1, 28},
    {FoodType::Gem, "Gem", '$', 6, 3, 20},
    {FoodType::Star, "Star", '*', 7, 5, 16},
    {FoodType::Ring, "Ring", '0', 8, 7, 12},
    {FoodType::Bolt, "Bolt", '!', 9, 9, 9},
    {FoodType::Plus, "Plus", '+', 10, 11, 7},
    {FoodType::Coin, "Coin", '&', 11, 13, 5},
    {FoodType::Crown, "Crown", '^', 12, 15, 3},
}};

inline constexpr const FoodDefinition& foodDefinition(FoodType type) {
    for (const auto& definition : kFoodDefinitions) {
        if (definition.type == type) {
            return definition;
        }
    }
    return kFoodDefinitions.front();
}

struct Food {
    Position position {};
    FoodType type {FoodType::Apple};

    int points() const {
        return foodDefinition(type).points;
    }

    char glyph() const {
        return foodDefinition(type).glyph;
    }
};
