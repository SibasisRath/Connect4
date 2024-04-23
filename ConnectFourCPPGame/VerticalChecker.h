#pragma once
#include "WinningConditionChecker.h"

class VerticalChecker : public WinningConditionChecker {
public:
    bool Check(const std::vector<std::pair<int, int>>& occupiedBoxes,
        char playerCharacter,
        const Board& board) override;
};
