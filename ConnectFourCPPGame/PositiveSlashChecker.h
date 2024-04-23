#pragma once
#include "WinningConditionChecker.h"

class PositiveSlashChecker : public WinningConditionChecker {
public:
    bool Check(const std::vector<std::pair<int, int>>& occupiedBoxes,
        char playerCharacter,
        const Board& board) override;
};
