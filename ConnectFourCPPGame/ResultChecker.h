#pragma once

#include <vector>
#include "ResultPrinter.h"
#include "WinningConditionChecker.h"

class ResultChecker {
private:
    std::vector<std::pair<int, int>> occupiedBoxes;
    int boardFillCounter = 0;
    ResultPrinter resultPrinter;
    std::vector<std::unique_ptr<WinningConditionChecker>> winningConditionCheckers;
public:
    ResultChecker();
    bool CheckResult(Player& player, Board& board);
};