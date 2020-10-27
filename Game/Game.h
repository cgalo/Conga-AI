//
// Created by Carlos Galo on 10/23/20.
//

#ifndef CONGA_AI_GAME_H
#define CONGA_AI_GAME_H

#include <random>                       // To assist in getting a

#include "../Board/Board.h"
class Game {
private:
    enum Players { white, black };      // White for p1 and black for p2
    Board* masterBoard;                 // Master board for this game
    int getRandNum(int max);            // Get a random number between 0 and the int max value

public:
    Game();                             // Constructor
    ~Game();                            // Destructor for garbage collecion
    void start();                       // Main method that will run the game until it's done
};


#endif //CONGA_AI_GAME_H
