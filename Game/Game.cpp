//
// Created by Carlos Galo on 10/23/20.
//

#include "Game.h"

Game::Game()
{
    p1 = new Player(white);                     // Create the player 1
    p2 = new Player(black);                     // Create the player 2
    masterBoard = new Board();                  // Build the board for this game with all values to 0
    masterBoard->setMove(0, 0, 10, white);      // Set the player 1 in the 0,0 index with 10 stones
    masterBoard->setMove(3, 3, 10, black);      // Set player 2 in the end-right most index of the board with 10 stones

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