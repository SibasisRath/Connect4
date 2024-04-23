#pragma once
#include <vector>
#include <utility>
#include "Board.h"

class WinningConditionChecker {
protected:
    const int maxCounter = 3;

    bool checkDirection(const std::vector<std::pair<int, int>>& occupiedBoxes,
        char playerCharacter,
        const Board& board,
        int rowOffset,
        int colOffset);

public:
    virtual ~WinningConditionChecker() = default;
    virtual bool Check(const std::vector<std::pair<int, int>>& occupiedBoxes,
        char playerCharacter,
        const Board& board) = 0;
};