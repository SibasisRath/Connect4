#pragma once
#include <vector>
#include <string>

class Player {
private:
    std::string playerName;
    char playerCharacter;
    std::vector<std::pair<int, int>> occupiedBoxes;

public:
    Player(std::string playerName, char playerCharacter);

    std::string GetPlayerName() const;
    char GetPlayerCharacter() const;
    void UpdateOccupiedBoxes(int row, int column);
    std::vector<std::pair<int, int>> GetOccupiedBoxes() const;
};