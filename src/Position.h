#pragma once

struct Position {
    int row, col;

    bool isValid() const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }

    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};
