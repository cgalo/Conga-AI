//
// Created by Carlos Galo on 11/12/20.
//

#ifndef CONGA_AI_AI_AGENT_H
#define CONGA_AI_AI_AGENT_H

#include <vector>
#include "../Board/Board.h"

class AI_Agent {
private:
    int maxP, minP;                                     // Who is the player we are maximizing and minimizing

    // Methods
    int MiniMax(Board* board, int depth, bool isMax);   // Recurse to return the best value/option for the given board
public:
    AI_Agent(int maxP, int minP);                       // Constructor that asks for the value of min & max player
    std::vector<Space*> getBestMove(Board* board);      // Get the best move given the current state of the board
};


#endif //CONGA_AI_AI_AGENT_H
