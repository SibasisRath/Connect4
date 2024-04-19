#include <iostream>
#include <string>
#include <vector>
enum PlayerEnum {
    RedPlayer,
    YellowPlayer
};

class Player {
private:
    PlayerEnum playerType;
    char playerCharacter;
    std::vector<std::pair<int, int>> occupiedBoxes;
public:
    Player(PlayerEnum playerType, char playerCharacter) {
        this->playerType = playerType;
        this->playerCharacter = playerCharacter;
    }

    PlayerEnum GetPlayerType() {
        return playerType;
    }
    char GetPlayerCharacter() {
        return playerCharacter;
    }

    void UpdateOccupiedBoxes(int row, int column) {
        std::pair<int, int> newOccupiedBox = {row,column};
        occupiedBoxes.push_back(newOccupiedBox);
    }
    std::vector<std::pair<int, int>> GetOccupiedBoxes() {
        return occupiedBoxes;
    }

};

class Board {
private:
    static constexpr int ROW = 6;
    static constexpr int COLUMN = 7;
    static constexpr char PLACE_HOLDER_CHARACTER = 'O';

    char entireBoard[ROW][COLUMN];
public:
    Board() {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COLUMN; j++) {
                entireBoard[i][j] = PLACE_HOLDER_CHARACTER;
            }
        }
    }

    void GetBoard() {
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COLUMN; j++) {
                std::cout << " " << entireBoard[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    bool UpdateBoard(int columnIndex, char playerCharacter) {
        bool shouldPlayerTurnChange = false;
        for (int i = ROW - 1; i >= 0; i-- ) {
            if(entireBoard[i][columnIndex] == PLACE_HOLDER_CHARACTER) {
                entireBoard[i][columnIndex] = playerCharacter;
                shouldPlayerTurnChange = true;
                break;
            }
        }
        return shouldPlayerTurnChange;
    }
};

class MainGameLoop {
private:
    Board board;
    Player redPlayer;
    Player yellowPlayer;
    Player players[2];
    int counter = 0;
    bool willPlayerTurnChange = false;

    static constexpr int ASCII_VALUE_FOR_ZERO = 48;
    static constexpr int ASCII_VALUE_FOR_SIX = 53; //total number of column 7 . So we are taking 0 to 6

public:
    MainGameLoop() : redPlayer(PlayerEnum::RedPlayer, 'R'),
        yellowPlayer(PlayerEnum::YellowPlayer, 'Y'),
        players{ redPlayer, yellowPlayer } {}
    void GameLoop() {
        bool shouldTheGameLoopContinue = true;

        while (shouldTheGameLoopContinue) {
            std::cout << "\n";
            board.GetBoard();
            std::cout << std::to_string(players[counter].GetPlayerType()) << " will be placed in column no: ";
            std::string columnNumInput;
            int columnNum;
            std::cin >> columnNumInput;
            if (columnNumInput.size() != 1) {
                continue;
            }
            else if (columnNumInput[0] >= ASCII_VALUE_FOR_ZERO && columnNumInput[0] <= ASCII_VALUE_FOR_SIX) {
                columnNum = std::stoi(columnNumInput);
                willPlayerTurnChange = board.UpdateBoard(columnNum, players[counter].GetPlayerCharacter());
            }

            if (willPlayerTurnChange) {
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

        do {
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
        } while (hasNotGotTheCorrectInputYet);

        if (canStartMainGameLoop) {
            mainGameLoop.GameLoop();
        }
    }

};

int main() {
    Game game;
    game.StartGame();
}