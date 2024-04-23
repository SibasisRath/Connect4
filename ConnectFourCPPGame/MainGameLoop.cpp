#include "MainGameLoop.h"

void MainGameLoop::GameLoop() {
    bool shouldTheGameLoopContinue = true;
    bool willPlayerTurnChange = false;
    while (shouldTheGameLoopContinue) {
        std::cout << "\n";
        board.PrintBoard();
        std::cout << players[counter].GetPlayerName() << " will be placed in column no: ";
        std::string columnNumInput;
        int columnNum;
        std::cin >> columnNumInput;

        try {
            columnNum = std::stoi(columnNumInput);

            // Check if columnNum is between 0 and 6
            if (columnNum >= 0 && columnNum <= 6) {
                // Valid input
                willPlayerTurnChange = board.UpdateBoard(columnNum, players[counter]);
            }
            else {
                // Invalid input
                std::cout << "Input is not between 0 and 6." << std::endl;
                continue;
            }
        }
        catch (const std::invalid_argument& e) {
            // Invalid input
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
            continue;
        }
        catch (const std::out_of_range& e) {
            // Input out of range
            std::cout << "Input is out of range." << std::endl;
            continue;
        }

        if (willPlayerTurnChange) {
            shouldTheGameLoopContinue = result.CheckResult(players[counter], board);
            counter++;
        }
        if (counter > 1) {
            counter = 0;
        }
    }
}