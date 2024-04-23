#pragma once
#include <iostream>
#include <string>
#include "Board.h"

class ResultPrinter {
public:
    static void PrintResult(const std::string& playerName, Board& board);
};