#include "Snake.hpp"

Snake::Snake() {
    reset();
}

void Snake::reset() {
    segments_.clear();
    segments_.push_back(Position {8, 10});
    segments_.push_back(Position {7, 10});
    segments_.push_back(Position {6, 10});
    direction_ = Direction::Right;
}

void Snake::setDirection(Direction nextDirection) {
    if (!isOpposite(direction_, nextDirection)) {
        direction_ = nextDirection;
    }
}

Direction Snake::direction() const {
    return direction_;
}

Position Snake::nextHeadPosition(int boardWidth, int boardHeight) const {
    Position next = head();
    switch (direction_) {
        case Direction::Up:
            --next.y;
            break;
        case Direction::Down:
            ++next.y;
            break;
        case Direction::Left:
            --next.x;
            break;
        case Direction::Right:
            ++next.x;
            break;
    }

    if (next.x < 0) {
        next.x = boardWidth - 1;
    } else if (next.x >= boardWidth) {
        next.x = 0;
    }

    if (next.y < 0) {
        next.y = boardHeight - 1;
    } else if (next.y >= boardHeight) {
        next.y = 0;
    }

    return next;
}

void Snake::moveTo(const Position& newHead, bool grow) {
    segments_.push_front(newHead);
    if (!grow) {
        segments_.pop_back();
    }
}

bool Snake::occupies(const Position& pos) const {
    for (const Position& segment : segments_) {
        if (segment == pos) {
            return true;
        }
    }
    return false;
}

bool Snake::hitsBody(const Position& pos, bool ignoreTail) const {
    const std::size_t limit = ignoreTail && !segments_.empty() ? segments_.size() - 1 : segments_.size();
    for (std::size_t i = 0; i < limit; ++i) {
        if (segments_[i] == pos) {
            return true;
        }
    }
    return false;
}

const std::deque<Position>& Snake::segments() const {
    return segments_;
}

Position Snake::head() const {
    return segments_.front();
}

std::size_t Snake::size() const {
    return segments_.size();
}

bool Snake::isOpposite(Direction a, Direction b) {
    return (a == Direction::Up && b == Direction::Down) ||
           (a == Direction::Down && b == Direction::Up) ||
           (a == Direction::Left && b == Direction::Right) ||
           (a == Direction::Right && b == Direction::Left);
}
