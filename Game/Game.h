/**
 * Game class header file
 * Game class handles the turn-to-turn operation of each player, and verifies who is the winner/looser.
 * This class utilizes the Board class to create a Board to play in and the AI_Agent class to get the
 * best possible move.
 * */

#ifndef CONGA_AI_GAME_H
#define CONGA_AI_GAME_H

#include <random>                       // To assist in selecting a random move

#include "../Board/Board.h"             // Import the Board class
#include "../AI_Agent/AI_Agent.h"       // Import the AI agent

class Game {
private:
    enum Players { white, black };      // White for p1 and black for p2
    Board* masterBoard;                 // Master board for this game
    int getRandNum(int max);            // Get a random number between 0 and the int max value

public:
    Game();                             // Constructor
    ~Game();                            // Destructor for garbage collection
    void start();                       // Main method that will run the game until it's done
};

#endif //CONGA_AI_GAME_H
