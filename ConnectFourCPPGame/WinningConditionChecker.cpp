#include "WinningConditionChecker.h"

bool WinningConditionChecker::checkDirection(const std::vector<std::pair<int, int>>& occupiedBoxes,
    char playerCharacter,
    const Board& board,
    int rowOffset,
    int colOffset) {
    for (const auto& box : occupiedBoxes) {
        int row = box.first;
        int col = box.second;

        // Check if there's enough space in the given direction
        if (row + (TOTAL_CONNECT - 1) * rowOffset < ROW &&
            row + (TOTAL_CONNECT - 1) * rowOffset >= 0 &&
            col + (TOTAL_CONNECT - 1) * colOffset < COLUMN &&
            col + (TOTAL_CONNECT - 1) * colOffset >= 0) {
            bool win = true;
            for (int j = 0; j < TOTAL_CONNECT; j++) {
                if (board.GetCharacter(row + j * rowOffset, col + j * colOffset) != playerCharacter) {
                    win = false;
                    break;
                }
            }

            if (win) {
                return true;
            }
        }
    }
    return false;
}