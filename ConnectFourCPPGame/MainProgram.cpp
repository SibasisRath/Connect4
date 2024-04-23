#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "DefineValues.h"
#include "Player.h"
#include "Board.h"
#include "ResultPrinter.h"
#include "WinningConditionChecker.h"
#include "HorizontalChecker.h"
#include "VerticalChecker.h"
#include "PositiveSlashChecker.h"
#include "NegetiveSlashChecker.h"
#include "ResultChecker.h"
#include "MainGameLoop.h"
#include "Game.h"

int main() {
    Game game;
    game.StartGame();
}