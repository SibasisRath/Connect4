#pragma once
#include <vector>
#include "Player.h"
#include "DefineValues.h"

class Board {
private:
    std::vector<std::vector<char>> entireBoard;

public:
   
    Board() : entireBoard(ROW, std::vector<char>(COLUMN, PLACEHOLDER_CHARACTER)){}

    void PrintBoard() const;

    bool UpdateBoard(int columnIndex, Player& player) ;

    // public get value method for not sharing the board with the result class.
    char GetCharacter(int row, int column) const;
};