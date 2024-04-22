#include <iostream>
#include <string>
#include <vector>
#include <limits>

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
    char& GetPlayerCharacter() {
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
    char GetCharacter(int row, int column) const{
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

class WinningConditionChecker {
protected:
    const int maxCounter = 3;
public:
    virtual ~WinningConditionChecker() = default;
    virtual bool Check(const std::vector<std::pair<int, int>>& occupiedBoxes, char playerCharacter, const Board& board) = 0;
};

class HorizontalChecker : public WinningConditionChecker {
private:
    bool isItAWin = false;
    int counter = 0;
public:
    bool Check(const std::vector<std::pair<int, int>>& occupiedBoxes,
        char playerCharacter,
        const Board& board) override {
        for (const auto& box : occupiedBoxes) {
            int row = box.first;
            int col = box.second;

            // Check if there's enough space to the right
            if (COLUMN - col >= TOTAL_CONNECT) {
                bool horizontalWin = true;
                for (int j = 1; j < TOTAL_CONNECT; j++) {
                    if (board.GetCharacter(row, col + j) != playerCharacter) {
                        horizontalWin = false;
                        break;
                    }
                }

                if (horizontalWin) {
                    isItAWin = true;
                    break;
                }
            }
        }
        return isItAWin;
    }
};
class VerticalChecker : public WinningConditionChecker {
private:
    bool isItAWin = false;
    int counter = 0;
public:
    bool Check(const std::vector<std::pair<int, int>>& occupiedBoxes,
        char playerCharacter,
        const Board& board) override {
        for (const auto& box : occupiedBoxes) {
            int row = box.first;
            int col = box.second;

            // Check if there's enough space to the top
            if (ROW - box.first >= TOTAL_CONNECT) {
                bool verticalalWin = true;
                for (int j = 1; j < TOTAL_CONNECT; j++) {
                    if (board.GetCharacter(row + j, col) != playerCharacter) {
                        verticalalWin = false;
                        break;
                    }
                }

                if (verticalalWin) {
                    isItAWin = true;
                    break;
                }
            }
        }

        return isItAWin;
    }
};

class ForwardSlashChecker : public WinningConditionChecker {
private:
    bool isItAWin = false;
    int counter = 0;
public:
    bool Check(const std::vector<std::pair<int, int>>& occupiedBoxes,
        char playerCharacter,
        const Board& board) override {
        for (const auto& box : occupiedBoxes) {
            int row = box.first;
            int col = box.second;

            // Check if there's enough space to the top
            if (box.first >= TOTAL_CONNECT && COLUMN - box.second >= TOTAL_CONNECT) {
                bool forwardSlashlWin = true;
                for (int j = 1; j < TOTAL_CONNECT; j++) {
                    if (board.GetCharacter(box.first - j, box.second + j) != playerCharacter) {
                        forwardSlashlWin = false;
                        break;
                    }
                }

                if (forwardSlashlWin) {
                    isItAWin = true;
                    break;
                }
            }
        }

        return isItAWin;
    }
};

class BackwardSlashChecker : public WinningConditionChecker {
private:
    bool isItAWin = false;
    int counter = 0;
public:
    bool Check(const std::vector<std::pair<int, int>>& occupiedBoxes,
        char playerCharacter,
        const Board& board) override {
        for (const auto& box : occupiedBoxes) {
            int row = box.first;
            int col = box.second;

            // Check if there's enough space to the top
            if (ROW - box.first >= TOTAL_CONNECT && COLUMN - box.second >= TOTAL_CONNECT) {
                bool backwardSlashlWin = true;
                for (int j = 1; j < TOTAL_CONNECT; j++) {
                    if (board.GetCharacter(box.first + j, box.second + j) != playerCharacter) {
                        backwardSlashlWin = false;
                        break;
                    }
                }

                if (backwardSlashlWin) {
                    isItAWin = true;
                    break;
                }
            }
        }

        return isItAWin;
    }
};

class ResultChecker {
private:
    std::vector<std::pair<int, int>> occupiedBoxes;
    int boardFillCounter = 0;
    ResultPrinter resultPrinter;
    std::vector<std::unique_ptr<WinningConditionChecker>> winningConditionCheckers;
public:
    ResultChecker(){
        winningConditionCheckers.emplace_back(std::make_unique<HorizontalChecker>());
        winningConditionCheckers.emplace_back(std::make_unique<VerticalChecker>());
        winningConditionCheckers.emplace_back(std::make_unique<ForwardSlashChecker>());
        winningConditionCheckers.emplace_back(std::make_unique<BackwardSlashChecker>());
    }
    bool CheckResult(Player &player, Board &board) {
        occupiedBoxes = player.GetOccupiedBoxes();
        char playerCharacter = player.GetPlayerCharacter();
        bool shouldGameContinue = true;
        const std::vector<std::pair<int, int>>& playerOccupiedBoxes = player.GetOccupiedBoxes();

        boardFillCounter++;

        if (occupiedBoxes.size() >= TOTAL_CONNECT) {
            for (const auto& winningConditionChecker : winningConditionCheckers) {
                if (winningConditionChecker->Check(occupiedBoxes, playerCharacter, board)) {
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

// This class is running the main game loop.
class MainGameLoop {
private:
    Board board;
    Player redPlayer;
    Player yellowPlayer;
    Player players[2];
    int counter = 0;

    ResultChecker result;

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
};

//This class is responsible for game introduction.
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