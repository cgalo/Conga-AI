//
// Created by Carlos Galo on 10/23/20.
//

#ifndef CONGA_AI_BOARD_H
#define CONGA_AI_BOARD_H

#define Color1 "[37m"
#define Color2 "[35m"

#include <iostream>                                         // For output
#include <vector>                                           // To return list of possible moves for a player

#include "../Player/Player.h"                               // Player and Space classes
class Board {
private:
    const int size = 4;                                     // Size of the matrix/board is a 4x4
    Space*** board;                                         // 2D matrix of Space pointers

public:
    Board();                                                // Constructor
    ~Board();                                               // Destructor

    bool setMove(int row, int col, int val, int player);    // Set the new value in the space
    Space* getValue(int row, int col);                      // Get the element in the given position of the board
    void printBoard();                                      // Print the current state of the board
    int getSize() const;                                    // Getter for the size of the board
    std::vector<std::vector<Space*>> getMoves(Player* player);  // List of lists of valid moves for the given player
};


#endif //CONGA_AI_BOARD_H
