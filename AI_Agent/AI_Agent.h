//
// Created by Carlos Galo on 11/12/20.
//

#ifndef CONGA_AI_AI_AGENT_H
#define CONGA_AI_AI_AGENT_H

#include <vector>
#include "../Board/Board.h"

class AI_Agent {
private:
    int maxP, minP, maxDepth;                           // Who is the player we are maximizing and minimizing

    // Methods
    int MiniMax(Board* board, int maxDepth, int depth, bool isMax, int alpha, int beta);      // Recurse to return the best value/option for the given board
    std::vector<Space*> getMove(Board* copiedBoard, std::vector<Space*> orgMove);

public:
    AI_Agent(int maxP, int minP, int depth=3);          // Constructor that asks for the value of min & max player
    int evalBoard(Board* board) const;                  // Evaluate the current state of the given board
    std::vector<Space*> getBestMove(Board* board, std::vector<std::vector<Space*>> currMoves);      // Get the best move given the current state of the board
};


#endif //CONGA_AI_AI_AGENT_H
