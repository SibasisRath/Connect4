#include "ResultPrinter.h"

void ResultPrinter::PrintResult(const std::string& playerName, Board& board) {
    std::cout << "\n";
    board.PrintBoard();
    if (playerName == "NoOne") {
        std::cout << "Game ended. It is a draw." << std::endl;
    }
    else {
        std::cout << "Game ended. Congratulations " << playerName << "!" << std::endl;
    }
}