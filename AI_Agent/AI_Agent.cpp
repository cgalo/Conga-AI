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
     * Function returns the 'best' move for the given state of the board.
     * This is done by either using the given currMoves, or by getting the maximizer player's available moves
     * in the board. We start evaluating every move from the list of moves, where we only keep the move with
     * the highest score.
     * After iterating through every move in the list of moves, we return the 'best' move, aka the move that had the
     * highest score.
     *
     * @param board - Board (pointer) object that holds the current state of the board
     * @param currMoves - list of legal/available moves for the player we want the 'best' move for
     * @return The best possible move as a vector of spaces
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
     * Function evaluates the given state of the board and tries to give it a 'score'. A positive score means that the
     * maximizer player, the AI, is doing better than the minimizer player. Negative scores reflect a better 'board'
     * for the minimizer player. Max scores are -100 or 100, -100 means that the minimizer player won in this board
     * while 100 means that the maximizer player won.
     *
     * @param board - Board (pointer) object for a Conga game
     * @return a number, or score, for the given state of the board
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
        /**
         * Here we apply my own algorithm called 'Neighbor-Move Heuristic'.
         * A neighbor(s) of a space would be any adjacent space(s) of a given space.
         *
         * This algorithm consists on giving a score by iterating through every space that the minimizer player
         * holds, where we get every neighbor(s) of every space that the minimizer players holds. Then we iterate
         * through each neighbor space and check if the maximizer player already holds this space, if they do then we
         * add add +1 to the score, if they don't, or no one holds it, we give add a -1.
         *
         * After getting the Neighbor score, we now get the Moves scores. This score consists on evaluating the total
         * possible moves of the maximizer player minus(-) the total possible moves of the minimizer player.
         *
         * We finish the Neighbor-Move heuristic by returning the Neighbor score + Move score
         * */

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
     * Function returns the the list of spaces equivalent in the copiedBoard.
     * This function was created due to a bug with deep copies of board objects, this was we can get the space pointers
     * of the space list we want from the new deep-copied board.
     *
     * @param copiedBoard - A deep-copy pointer object of a Board
     * @param orgMove - list of spaces, or move, that we want to get the equivalent in copiedBoard/new board
     * @return Vector of spaces that contain the equivalent spaces of the given orgMove
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