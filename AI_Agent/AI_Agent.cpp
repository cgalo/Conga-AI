//
// Created by Carlos Galo on 11/12/20.
//

#include "AI_Agent.h"

AI_Agent::AI_Agent(int maxP, int minP, int depth)
{
    this->maxP = maxP;
    this->minP = minP;
    this->maxDepth = depth;
}

std::vector<Space *> AI_Agent::getBestMove(Board *board, std::vector<std::vector<Space *>> currMoves)
{
    /**
     *
     * */
     
    std::vector<std::vector <Space*>> moves = currMoves;
    if (currMoves.empty())
        moves = board->getMoves(maxP); // Get the available moves for the AI player

    std::vector<Space*> bestMove;                       // This will be the best move
    int bestScore = INT_MIN;                            // To keep track of the best score
    for (int i = 0; i < moves.size(); i++)
    {
        const auto move = moves[i];
        Board* tempBoard = board->getDeepCopy();        // Create a copy of the board
        auto tempMove = getMove(tempBoard, move);
        tempBoard->setMove(tempMove, maxP);
        int tempScore = MiniMax(tempBoard, maxDepth, 0, false, INT_MIN, INT_MAX);   // Get the score for this move
        if (tempScore > bestScore)                      // If the tempScore is greater than bestScore
        {
            bestScore = tempScore;                      // Make the tempScore the new best score
            bestMove = move;                            // Set the current move as the best move
        }
        delete tempBoard;                               // Delete the tempBoard
    }

    return bestMove;
}

int AI_Agent::evalBoard(Board *board) const {
    /**
     *
     * */

    auto maxMoves = board->getMoves(maxP); // Get all the moves for the max player
    auto minMoves = board->getMoves(minP); // Get all the moves for the min player
    auto maxSpaces = board->getPlayerSpaces(maxP);  // Get the list of spaces the max player holds in the given board
    auto minSpaces = board->getPlayerSpaces(minP);  // Get the list of spaces that the min player holds in the board

    if (minMoves.size() == 0)               // If the min player has no available moves
        return 100;                         // Then is winning state and we give it a score of 100
    else if (maxMoves.size() == 0)          // If the max player has no available moves
        return -100;                        // Return -100 as it is a loosing state
    else                                    // Else this not an end state
    {
       int score = 0;
       for (auto minSpace: minSpaces)
       {
           auto neighbors = board->getNeighbors(minSpace);  //Get the neighbors for the given space
           for (auto neighbor: neighbors)                   // For every neighbor in the list of neighbors
           {
              if (neighbor->getPlayer() == maxP)            // If the maxPlayer already holds this neighbor
                  score++;                                  // Then we add + 1 to the score
              else                                          // Else the neighbor is either open or owned by the other
                  score--;                                  // We subtract -1 to the score
           }
       }
       int evalMoves = maxMoves.size() - minMoves.size();
       return score + evalMoves;

    }
}

int AI_Agent::MiniMax(Board *board, int maxDepth, int depth, bool isMax, int alpha, int beta)
{
    /**
     *
     * */

    const int score = evalBoard(board);
    // Check if we reached a terminal state
    if (score == 100)
        return score - depth;
    if (score == -100)
        return score + depth;
    if (depth == maxDepth)
        return score;

    std::vector<std::vector<Space*>> moves;

    if (isMax)
    {
        int maxScore = INT_MIN;
        moves = board->getMoves(maxP);
        for (const auto& move: moves)
        {
            Board* tempBoard = board->getDeepCopy();
            auto tempMove = getMove(tempBoard, move);
            tempBoard->setMove(tempMove, maxP);
            int tempScore = MiniMax(tempBoard,maxDepth, depth+1, false, alpha, beta);
            maxScore = (score > maxScore) ? tempScore : maxScore;   // If maxScore is less than score, make score the new maxScore
            alpha = (maxScore > alpha) ? maxScore : alpha;          // If alpha is less than maxScore, make maxScore the new alpha
            delete tempBoard;
            // Perform alpha-beta pruning
            if (beta <= alpha)                                      // If beta es less than or equal than alpha
                break;

        }
        return maxScore;
    }
    else
    {
        int minScore = INT_MAX;
        moves = board->getMoves(minP);
        for (const auto move: moves)
        {
            Board* tempBoard = board->getDeepCopy();
            auto tempMove = getMove(tempBoard, move);
            tempBoard->setMove(tempMove, minP);
            int tempScore = MiniMax(tempBoard, maxDepth, depth+1, true, alpha, beta);
            minScore = (score < minScore) ? tempScore : minScore;   // If the score is less than minScore, make the score the new minScore
            beta = (minScore < beta) ? minScore : beta;             // If minScore is less than beta, make minScore the new beta
            delete tempBoard;
            if (beta <= alpha)                                      // If beta es less than or equal than alpha
                break;                                              // We break, we stop evaluating
        }
        return minScore;
    }
}

std::vector<Space *> AI_Agent::getMove(Board *copiedBoard, std::vector<Space *> orgMove)
{
    /**
     *
     * */

    std::vector<Space*> move;
    for (const auto& orgSpace: orgMove)
    {
        const auto orgRow = orgSpace->getRow(), orgCol = orgSpace->getColumn();
        auto tempSpace = copiedBoard->getValue(orgRow, orgCol);
        move.push_back(tempSpace);
    }
    return move;
}