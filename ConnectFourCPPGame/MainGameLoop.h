#pragma once
#include "Board.h"
#include "ResultChecker.h"

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

    void GameLoop();
};