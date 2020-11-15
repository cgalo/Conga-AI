/**
 * Board Class
 * This class is called by the Game class to create and handle the moves and rocks for the Conga game
 * The object consists in a 4x4 2D matrix of Space object
 * */

#ifndef CONGA_AI_BOARD_H
#define CONGA_AI_BOARD_H

// Colors are used to differentiate if the space is owned by P1 or P2
#define Color1 "[37m"                                      // Color for the P1 spaces
#define Color2 "[35m"                                      // Color for the P2 spaces

#include <iostream>                                         // For output
#include <vector>                                           // To return list of possible moves for a player


#include "../Space/Space.h"                                 // Space class to create a 2D matrix of them as a board
class Board {
private:
    const int size = 4;                                     // Size of the matrix/board is a 4x4
    Space*** board;                                         // 2D matrix of Space pointers
    bool isValidLocation(int row, int column) const;        // Check if the given indexes are inside the board
    std::vector <Space*> getSpaces(int player);             // Get a list of spaces that the player holds

public:
    Board();                                                // Constructor
    ~Board();                                               // Destructor

    void setMove(std::vector<Space*> move, int player);     // Given a list of spaces we move the values in the board for the player
    Space* getValue(int row, int col);                      // Get the element in the given position of the board
    void printBoard();                                      // Print the current state of the board
    int getSize() const;                                    // Getter for the size of the board
    std::vector<std::vector<Space*>> getMoves(int player);  // List of lists of valid moves for the given player
    Board* getDeepCopy();                                   // Return a copy of the current state of the board
    int getTotPlayerSpaces(int player);                     // Returns total spaces that the player holds
};


#endif //CONGA_AI_BOARD_H
