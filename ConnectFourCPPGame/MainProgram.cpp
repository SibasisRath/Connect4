#include <iostream>
#include <string>

class Game {
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
        std::cout << "Press \"S\" or \"s\" to start the Game.\nPress \"Q\" or \"q\" to exit.\n";
        std::string input;
        std::getline(std::cin, input); // Read a full line input
        while (input != "S" && input != "s" && input != "Q" && input != "q") {
            std::cin >> input;
        }

        if (input == "S" || input == "s") {
            std::cout << "game is starting.";
            Run();
        }

        if (input == "Q" || input == "q") {
            std::cout << "game is ending.";
        }
       
    }

    void Run() {

       
    }


};

int main() {
    Game game;
    game.StartGame();
}