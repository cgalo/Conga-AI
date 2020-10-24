//
// Created by Carlos Galo on 10/23/20.
//

#include "Game.h"

Game::Game()
{
    masterBoard = new Board();                              // Build the board for this game with all values to 0
    masterBoard->setMove(0, 0, 10, white);                  // Set the player 1 in the 0,0 index with 10 stones
    masterBoard->setMove(3, 3, 10, black);                  // Set player 2 in the end-right most index of the board with 10 stones
    p1 = new Player(white, masterBoard->getValue(0, 0));    // Create the player 1 with the Space (0,0) for the list of spaces it holds
    p2 = new Player(black, masterBoard->getValue(3, 3));    // Create the player 2 with the Space (3,3) for the list of spaces it holds
}

Game::~Game()
{
    /**
     * Destructor for garbage collection of the Game object
    */

    delete p1;
    delete p2;
    delete masterBoard;
}

void Game::start()
{
     masterBoard->printBoard();
}