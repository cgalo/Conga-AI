//
// Created by Carlos Galo on 10/23/20.
//

#include "Board.h"
Board::Board()
{
    board = new Space** [size];
    for (int i = 0; i < size; i++)
        board[i] = new Space* [size];

    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            board[row][col] = new Space(row, col, 0);
}

Board::~Board()
{
    delete []board;
}

bool Board::setMove(int row, int col, int val, int player)
{
    board[row][col]->setValue(10);
    board[row][col]->setPlayer(player);
    return false;
}

Space * Board::getValue(int row, int col)
{
    // First we check that the row and col are within the size of the board/matrix
    if ((row < 0 || col < 0) ||                 // If either row and column are less than 0
        (row > getSize() || col > getSize()))   // Or row and column are greater than the size of the board
        return nullptr;                         // Return a nullptr
    else                                        // Else the row and column are within the size of the matrix
        return board[row][col];                 // Return the Space object in that element location of the matrix
}

void Board::printBoard()
{
    /**
     * Method prints the current state of the board
     */

    for (int row = 0; row < getSize(); row++)       // Iterate through the every row
    {
        for (int col = 0; col < getSize(); col++)   // Iterate through every column
        {
            Space* space = board[row][col];

            if (space->getValue() == 0)
                std::cout << "  " << "  " << "  ";

            else if (space->getPlayer() == 0)
                std::cout << "  " << Color1 << space->getValue() << "  ";
            else
                std::cout << "  " << Color2 << space->getValue() << "  ";

            if (col < getSize() - 1)
                std::cout << "|";
        }
        std::cout << std::endl;
        if (row < getSize() -1)
        {
            for (int j = 0; j < getSize(); j++)
                std::cout << "-------";
            std::cout << std::endl;
        }
    }
}

int Board::getSize() const
{
    return size;
}

std::vector<std::vector<Space *>> Board::getMoves(Player *player)
{
    
}