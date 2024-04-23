#include <iostream>
#include "Board.h"

void Board::PrintBoard() const{
    for (auto row = entireBoard.begin(); row != entireBoard.end(); ++row) {
        for (auto column = row->begin(); column != row->end(); ++column) {
            char value = *column;
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }
}

bool Board::UpdateBoard(int columnIndex, Player& player) {
    bool shouldPlayerChangeTurn = false;
    for (int i = ROW - 1; i >= 0; i--) {
        if (entireBoard[i][columnIndex] == PLACEHOLDER_CHARACTER) {
            entireBoard[i][columnIndex] = player.GetPlayerCharacter();
            shouldPlayerChangeTurn = true;
            player.UpdateOccupiedBoxes(i, columnIndex);
            break;
        }
    }
    return shouldPlayerChangeTurn;
}

char Board::GetCharacter(int row, int column) const{
    return entireBoard[row][column];
}