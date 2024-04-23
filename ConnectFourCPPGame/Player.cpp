#include "Player.h"
#include <iostream>

Player::Player(std::string playerName, char playerCharacter)
    : playerName(playerName), playerCharacter(playerCharacter) {}

std::string Player::GetPlayerName() const {
    return playerName;
}

char Player::GetPlayerCharacter() const {
    return playerCharacter;
}

void Player::UpdateOccupiedBoxes(int row, int column) {
    std::pair<int, int> newOccupiedBox = { row, column };
    occupiedBoxes.push_back(newOccupiedBox);
}

std::vector<std::pair<int, int>> Player::GetOccupiedBoxes() const {
    return occupiedBoxes;
}