//
// Created by Carlos Galo on 10/23/20.
//

#ifndef CONGA_AI_GAME_H
#define CONGA_AI_GAME_H


#include "../Player/Player.h"
#include "../Board/Board.h"
class Game {
private:
    enum PlayerOptions{ white, black};
    Board* masterBoard;                 // Master board for this game
    Player* p1;                         // Player 1 -> White
    Player*p2;                          // Player 2 -> Black


public:
    Game();
    ~Game();
    void start();
};


#endif //CONGA_AI_GAME_H
