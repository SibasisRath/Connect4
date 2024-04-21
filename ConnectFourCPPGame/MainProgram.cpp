#include <iostream>
#include <string>
#include <vector>

#define ROW 6
#define COLUMN 7
#define TOTAL_CONNECT 4

class Player {
private:
    std::string playerName;
    char playerCharacter;
    std::vector<std::pair<int, int>> occupiedBoxes;
public:
    Player(std::string playerName, char playerCharacter) {
        this->playerName = playerName;
        this->playerCharacter = playerCharacter;
    }

    std::string GetPlayerName() const {
        return playerName;
    }
    char GetPlayerCharacter() const {
        return playerCharacter;
    }

    void UpdateOccupiedBoxes(int row, int column) {
        std::pair<int, int> newOccupiedBox = {row,column};
        occupiedBoxes.push_back(newOccupiedBox);
    }

    std::vector<std::pair<int, int>> GetOccupiedBoxes () const{
        return occupiedBoxes;
    }
};

class Board {
private:
    static constexpr char PLACE_HOLDER_CHARACTER = 'O';
    std::vector<std::vector<char>> entireBoard;

public:
    Board() {
        entireBoard.resize(ROW, std::vector<char>(COLUMN, PLACE_HOLDER_CHARACTER));
    }

    void PrintBoard() const {
        for (auto row = entireBoard.begin(); row != entireBoard.end(); ++row) {
            for (auto column = row->begin(); column != row->end(); ++column) {
                char value = *column;
                std::cout << value << ' ';
            }
            std::cout << std::endl; 
        }
    }

    std::vector<std::vector<char>>& GetBoard(){
        return entireBoard;
    }

    bool UpdateBoard(int columnIndex, Player& player) {
        bool shouldPlayerChangeTurn = false;
        for (int i = ROW - 1; i >= 0; i-- ) {
            if(entireBoard[i][columnIndex] == PLACE_HOLDER_CHARACTER) {
                entireBoard[i][columnIndex] = player.GetPlayerCharacter();
                shouldPlayerChangeTurn = true;
                player.UpdateOccupiedBoxes(i, columnIndex);
                break;
            }
        }
        return shouldPlayerChangeTurn;
    }
    // public get value method for not sharing the board with the result class.
    char GetCharacter(int row, int column) {
        return entireBoard[row][column];
    }
};

class ResultPrinter {
public:
    static void PrintResult(const std::string& playerName) {
        if (playerName == "NoOne") {
            std::cout << "Game ended. It is a draw." << std::endl;
        }
        else {
            std::cout << "Game ended. Congratulations " << playerName << "!" << std::endl;
        }
    }
};

class ResultChecker {
private:
    std::vector<std::pair<int, int>> occupiedBoxes;
    Board board;
    //std::vector<std::vector<char>> entireArray;
    int boardFillCounter = 0;
    ResultPrinter resultPrinter;
public:
    bool CheckResult(Player &player, Board &board) {
        occupiedBoxes = player.GetOccupiedBoxes();
        //entireArray = board.GetBoard();
        char playerCharacter = player.GetPlayerCharacter();
        bool shouldGameContinue = true;
        const std::vector<std::pair<int, int>>& playerOccupiedBoxes = player.GetOccupiedBoxes();

        boardFillCounter++;


        if (occupiedBoxes.size() >= TOTAL_CONNECT) {
            for (auto& box : occupiedBoxes) {

                if (COLUMN - box.second >= TOTAL_CONNECT &&
                    board.GetCharacter(box.first, box.second) == playerCharacter &&
                    board.GetCharacter(box.first, box.second + 1) == playerCharacter &&
                    board.GetCharacter(box.first, box.second + 2) == playerCharacter &&
                    board.GetCharacter(box.first, box.second + 3) == playerCharacter) {
                    shouldGameContinue = false;
                    resultPrinter.PrintResult(player.GetPlayerName());
                    break;
                }
                if (ROW - box.first >= TOTAL_CONNECT &&
                    board.GetCharacter(box.first, box.second) == playerCharacter &&
                    board.GetCharacter(box.first + 1, box.second) == playerCharacter &&
                    board.GetCharacter(box.first + 2, box.second) == playerCharacter &&
                    board.GetCharacter(box.first + 3, box.second) == playerCharacter) {
                    shouldGameContinue = false;
                    resultPrinter.PrintResult(player.GetPlayerName());
                    break;
                }

                if (box.first >= TOTAL_CONNECT && COLUMN - box.second >= TOTAL_CONNECT &&
                    board.GetCharacter(box.first, box.second) == playerCharacter &&
                    board.GetCharacter(box.first - 1, box.second + 1) == playerCharacter &&
                    board.GetCharacter(box.first - 2, box.second + 2) == playerCharacter &&
                    board.GetCharacter(box.first - 3, box.second + 3) == playerCharacter) {
                    shouldGameContinue = false;
                    resultPrinter.PrintResult(player.GetPlayerName());
                    break;
                }

                if (ROW - box.first >= TOTAL_CONNECT && COLUMN - box.second >= TOTAL_CONNECT &&
                    board.GetCharacter(box.first, box.second) == playerCharacter &&
                    board.GetCharacter(box.first + 1, box.second + 1) == playerCharacter &&
                    board.GetCharacter(box.first + 2, box.second + 2) == playerCharacter &&
                    board.GetCharacter(box.first + 3, box.second + 3) == playerCharacter) {
                    shouldGameContinue = false;
                    resultPrinter.PrintResult(player.GetPlayerName());
                    break;
                }

            }
        }

        if (shouldGameContinue && boardFillCounter == ROW * COLUMN) {
            resultPrinter.PrintResult("NoOne");
            shouldGameContinue = false;
        }

        return shouldGameContinue;
    }
};

class MainGameLoop {
private:
    Board board;
    Player redPlayer;
    Player yellowPlayer;
    Player players[2];
    int counter = 0;

    ResultChecker result;

    static constexpr int ASCII_VALUE_FOR_ZERO = '0';
    static constexpr int ASCII_VALUE_FOR_SIX = '6';

public:
    MainGameLoop() : redPlayer("Red_Player", 'R'),
        yellowPlayer("Yellow_Player", 'Y'),
        players{ redPlayer, yellowPlayer } {}

    void GameLoop() {
        bool shouldTheGameLoopContinue = true;
        bool willPlayerTurnChange = false;
        while (shouldTheGameLoopContinue) {
            std::cout << "\n";
            board.PrintBoard();
            std::cout << players[counter].GetPlayerName() << " will be placed in column no: ";
            std::string columnNumInput;
            int columnNum;
            std::cin >> columnNumInput;

            if (columnNumInput.length() == 1 && columnNumInput[0] >= ASCII_VALUE_FOR_ZERO && columnNumInput[0] <= ASCII_VALUE_FOR_SIX) {
                columnNum = std::stoi(columnNumInput);
                willPlayerTurnChange = board.UpdateBoard(columnNum, players[counter]);
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
};

class Game {
private:
    MainGameLoop mainGameLoop;
public:
    Game() {
        std::cout << R"(

 .d8888b.                                               888             d8888  
d88P  Y88b                                              888            d8P888  
888    888                                              888           d8P 888  
888         .d88b.  88888b.  88888b.   .d88b.   .d8888b 888888       d8P  888  
888        d88""88b 888 "88b 888 "88b d8P  Y8b d88P"    888         d88   888  
888    888 888  888 888  888 888  888 88888888 888      888  888888 8888888888 
Y88b  d88P Y88..88P 888  888 888  888 Y8b.     Y88b.    Y88b.             888  
 "Y8888P"   "Y88P"  888  888 888  888  "Y8888   "Y8888P  "Y888            888  
                                                                                                                             
                                                                               
)" << std::endl;

        std::cout << "Welcome to CONNECT-4 Game."
            <<"\nRules:"
            <<"\n1. Two-Player(red (R) and blue (b)) game."
            <<"\n2. Board size 6 rows and 7 columns."
            <<"\n3. A player wins if he/she is able to connect 4 dots horizontaly or vertically or digonally."
            <<"\n4. Draw when the matrix is filled.\n"
            <<"\nHow to play:"
            <<"\n1. Game will always starts with player 1. i.e. red |R|."
            <<"\n2. In each step choose the column number in which you want to drop the ball."
            <<"\n3. Rows will be filled from the bottom to top.\n";
    }

    void StartGame() {
        std::string input;
        char inputCharacter;
        bool canStartMainGameLoop = false;
        bool hasNotGotTheCorrectInputYet = true;

        while (hasNotGotTheCorrectInputYet)
        {
            std::cout << "Press \"S\" or \"s\" to start the Game.\nPress \"Q\" or \"q\" to exit.\n";
            std::getline(std::cin, input);
            if (input.length() != 1) {
                continue;
            }
            inputCharacter = std::tolower(input[0]);
            switch (inputCharacter) {
            case 's':
                std::cout << "game is starting.\n";
                canStartMainGameLoop = true;
                hasNotGotTheCorrectInputYet = false;
                break;
            case 'q':
                std::cout << "game is ending.";
                hasNotGotTheCorrectInputYet = false;
                break;
            default:
                std::cout << "Invalid input. Please try again.\n";
                break;
            }
        } 

        if (canStartMainGameLoop) {
            mainGameLoop.GameLoop();
        }
    }

};

int main() {
    Game game;
    game.StartGame();
}