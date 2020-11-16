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
    /**
     * This method handles the turn by turn of the game, as well as who is the winner
     * */
     AI_Agent* AI = new AI_Agent(white, black, 15);  // Create the AI player
     int currPlayer = white;                            // We set the white player as the initial player
     std::vector<std::vector<Space*>> currMoves;        // Vector will hold the moves of a player
     currMoves = masterBoard->getMoves(currPlayer);     // Get the moves for the current player
     int totPlays = 0, AIMoves = 0;                     // Keep track of total moves done and the moves of the AI
     while (!currMoves.empty())                         // While the current player has moves
     {
         totPlays++;
         std::cout << "\n\tPlay #: " << totPlays << "\n\n";
         masterBoard->printBoard();                     // Print the board
         std::vector <Space*> move;                     // This will be used to hold the final moved selected for the current player

         if (currPlayer == white)                       // If it's the AI/white/player1 turn's
         {
             AIMoves++;                                 // Update the total moves of the AI
             std::vector<Space*> tempMove = AI->getBestMove(masterBoard->getDeepCopy(), currMoves);
             move = tempMove;
         }
         else                                           // Else it's the black player's turn
         {
             // We'll pick a random available move for the player
             int moveIndex = getRandNum(currMoves.size());  // Get a random number to pick a move from the move list
             move = currMoves[moveIndex];               // Save a random move
         }
         masterBoard->setMove(move, currPlayer);        // Make the move in the board for the current player
         currMoves.clear();                             // Clear the available moves to make space for the next player
         // Now we swap players and get the moves for them
         currPlayer = (currPlayer == white) ? black : white;    // If the player is white then change to black, else vice versa
         currMoves = masterBoard->getMoves(currPlayer); // Get the moves for the new current player
     }
     std::cout << std::endl;
     masterBoard->printBoard();
     std::cout << "Congratulations player ";
     // Check who is the winner/looser
     if (currPlayer == white)                           // This means that white ran out of possible moves
        std::cout << "black!" << std::endl;
     else                                               // Else the black ran out of possible moves
         std::cout << "white!" << std::endl;
     std::cout << "Total moves made: " << totPlays << std::endl;
}

int Game::getRandNum(int max)
{
    /**
     * This method generates a random number between 0 and the max number: 0 <= randNUm <= max
     * For random we are not using srand and rand(), here is more information why we implemented something different:
     *  - https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
     *
     * @param The int max value of the range to generate a random value
     * @return a random number between 0 and the max value - 1
     * */

//    std::default_random_engine generator;                               // To assist in generating a random number
//    std::uniform_int_distribution<int> distribution(0,max - 1);     // Range to pick a random number
//    int randomNum = distribution(generator);                        // Generate # between 0 and max - 1
    srand(time(NULL));
    return rand() % (max);
}