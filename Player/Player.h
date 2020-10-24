//
// Created by Carlos Galo on 10/23/20.
//

#ifndef CONGA_AI_PLAYER_H
#define CONGA_AI_PLAYER_H


#include "../Space/Space.h"
#include <vector>                                       // To hold dynamic list of Space objects
class Player {
private:
    int value;                                          // The name/value for the player
    std::vector<Space> Spaces;                          // Keep track of spaces the player holds in the current state of the board

public:
    Player(int value);                                  // Given a value for this player
    explicit Player(int value, Space& space);           // Constructor given a value and an initial space

    // Methods
    int getValue() const;                               // Getter for value
    const std::vector<Space> &getSpaces() const;        // Get Spaces of the player
    void updateSpaces(const std::vector<Space> &spaces);    // Update the spaces for the player
};

#endif //CONGA_AI_PLAYER_H
