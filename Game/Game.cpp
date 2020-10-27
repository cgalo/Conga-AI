//
// Created by Carlos Galo on 10/23/20.
//

#include "Game.h"

Game::Game()
{
    masterBoard = new Board();                              // Build the board for this game with all values to 0
    // Now we set the players and their rocks in their respective positions of the board
    const int initVal = 10;                                 // Each player starts with 10 rocks in their space
    // Setup player white/1
    Space * p1Space = masterBoard->getValue(0, 0);          // We get the 0,0 corner for white/player 1
    p1Space->setPlayer(white);                              // Set the player 1 as owner of this space
    p1Space->setValue(initVal);                             // Set the rocks for the player
    // Now we set up the player black/2
    Space* p2Space = masterBoard->getValue(3, 3);           // Get the right-end most corner for p2/black
    p2Space->setPlayer(black);                              // Set the black player as owner of this space
    p2Space->setValue(initVal);                             // Set the initial rocks for the player

}

Game::~Game()
{
    /**
     * Destructor for garbage collection of the Game object
    */

    delete masterBoard;
}

void Game::start()
{
     masterBoard->printBoard();
}