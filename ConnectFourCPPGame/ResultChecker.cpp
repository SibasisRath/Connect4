#include "ResultChecker.h"
#include "HorizontalChecker.h"
#include "VerticalChecker.h"
#include "PositiveSlashChecker.h"
#include "NegetiveSlashChecker.h"


ResultChecker::ResultChecker() {
    winningConditionCheckers.emplace_back(std::make_unique<HorizontalChecker>());
    winningConditionCheckers.emplace_back(std::make_unique<VerticalChecker>());
    winningConditionCheckers.emplace_back(std::make_unique<PositiveSlashChecker>());
    winningConditionCheckers.emplace_back(std::make_unique<NegetiveSlashChecker>());
}

bool ResultChecker::CheckResult(Player& player, Board& board) {
    occupiedBoxes = player.GetOccupiedBoxes();
    char playerCharacter = player.GetPlayerCharacter();
    bool shouldGameContinue = true;
    const std::vector<std::pair<int, int>>& playerOccupiedBoxes = player.GetOccupiedBoxes();

    boardFillCounter++;

    if (occupiedBoxes.size() >= TOTAL_CONNECT) {
        for (const auto& winningConditionChecker : winningConditionCheckers) {
            if (winningConditionChecker->Check(occupiedBoxes, playerCharacter, board)) {
                shouldGameContinue = false;
                resultPrinter.PrintResult(player.GetPlayerName(), board);
                break;
            }
        }
    }

    if (shouldGameContinue && boardFillCounter == ROW * COLUMN) {
        resultPrinter.PrintResult("NoOne", board);
        shouldGameContinue = false;
    }

    return shouldGameContinue;
}