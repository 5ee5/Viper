#pragma once

#include <deque>

#include "Types.hpp"

class Snake {
public:
    Snake();

    void reset();
    void setDirection(Direction nextDirection);
    Direction direction() const;
    Position nextHeadPosition(int boardWidth, int boardHeight) const;
    void moveTo(const Position& newHead, bool grow);
    bool occupies(const Position& pos) const;
    bool hitsBody(const Position& pos, bool ignoreTail) const;

    const std::deque<Position>& segments() const;
    Position head() const;
    std::size_t size() const;

private:
    static bool isOpposite(Direction a, Direction b);

    std::deque<Position> segments_;
    Direction direction_ {Direction::Right};
};
