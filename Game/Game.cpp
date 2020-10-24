//
// Created by Carlos Galo on 10/23/20.
//

#include "Game.h"

Game::Game()
{
    p1 = new Player(white);
    p2 = new Player(black);
    masterBoard = new Board();
    Space* p1Init = masterBoard->getValue(3,3);
    masterBoard->setMove(0,0,10,white);
    Space* p2Init = masterBoard->getValue(3,3);
    masterBoard->setMove(3,3,10,black);

}

Game::~Game()
{
    delete p1;
    delete p2;
    delete masterBoard;
}

void Game::start()
{
    //std::cout << masterBoard->getValue(0,0)->getValue() << std::endl;
    masterBoard->printBoard();
}