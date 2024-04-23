#include "VerticalChecker.h"

bool VerticalChecker::Check(const std::vector<std::pair<int, int>>& occupiedBoxes,
    char playerCharacter,
    const Board& board) {
    return checkDirection(occupiedBoxes, playerCharacter, board, 1, 0);
}