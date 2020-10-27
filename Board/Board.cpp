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
    if (isValidLocation(row, col))              // If the given row/col are valid locations then we can return a valid space
        return board[row][col];                 // Return the Space object in that element location of the matrix
    else                                        // Else the row and column are NOT within the size of the matrix
        return (new Space(-1, -1, -1, -1)); // Return a space with all attributes set to -1

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
                std::cout << "\033  " << Color1 << space->getValue() << "\033[0m  ";
            else
                std::cout << "\033  " << Color2 << space->getValue() << "\033[0m  ";

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

bool Board::isValidLocation(int row, int column) const
{
    bool isValid = true;                                // Variable to return, set as true unless we find a case it's false
    if (row < 0 || column < 0)                          // If either row/column are less than 0
        isValid = false;                                // Set the isValid to false
    if (row >= getSize() || column >= getSize())        // If either row/column are equal or greater than the size of the board
        isValid = false;                                // Set isValid to false
    return isValid;                                     // Return isValid
}

std::vector<std::vector<Space *>> Board::getMoves(Player *player)
{
    std::vector<std::vector<Space*>> paths;                 // Create list of lists of spaces, this is every possible path the player can do as a move
    std::vector<Space*> currSpaces = player->getSpaces();   // We get the current spaces that the player holds
    const int totSpaces = currSpaces.size();                // Save the size of currSpaces of this player
    const int playerVal = player->getValue();               // Save the value of the current player as playerVal

    // Now we loop through all the current spaces the player is in, we are going to see if there is a possible path per each space
    for (int i = 0; i < totSpaces; i++)                     // Initiate loop through every space in the list
    {
        int tempRow, tempCol;                               // This will be updated as needed depending on what path we are testing
        // Now we check if there is an open space by checking is there is an open space either left, right, up or down of the current space
        Space* space = currSpaces[i];                       // Get the current element of the list and save it as space
        const int row = space->getRow(), col = space->getColumn();// Get the row and column locations of the current space

        // First we check if the space above is a possible path -> row -1, col remains the same
        tempRow = row - 1, tempCol = col;
        Space* aboveSpace = getValue(tempRow, tempCol);     // Get the space that would be above this one in the board
        if (isValidLocation(tempRow, tempCol) &&            // If the the location is valid
            (aboveSpace->getValue() == 0 || aboveSpace->getPlayer() == playerVal))  // And either the space is empty or owned by our player
        {
            std::vector <Space*> upPath;                    // Create a list of of spaces
            // We found a possible path, now we keep going up to find the whole path we can have
            for (tempRow = row; tempRow >= 0; tempRow--)    // Keep iterating up the matrix until we get to the first row
            {
                aboveSpace = getValue(tempRow, col);        // Save the current space element for this indexes
                // Save the player and value for the current space we are in
                int tempPlayer = aboveSpace->getPlayer(), tempVal = aboveSpace->getValue();
                if(isValidLocation(tempRow, tempCol) &&     // If the indexes are valid locations in the board
                  (tempVal == 0 || tempPlayer == playerVal))// And either the space is open or owned by the player
                    upPath.push_back(aboveSpace);           // Then we add the space to the path
                else                                        // Else we got to either an invalid index in the board or the other
                    break;                                  // player owns the location, so we reached the end of this path
            }
            paths.push_back(upPath);                        // Add this path to the list of paths
        }
        // Now we check if there is a path south of the current space -> row + 1, col remains the same
        tempRow = row + 1, tempCol = col;
        Space* belowSpace = getValue(tempRow, tempCol);     // Get the space below of the current one
        if (isValidLocation(tempRow, tempCol) &&            // If the indexes are within the board
            (belowSpace->getValue() == 0 || belowSpace->getPlayer() == playerVal))   // And either the space is open or owned by the player
        {
            std::vector <Space*> belowPath;                 // Create a list for all the open spaces below the current one
            for (tempRow = row; tempRow < getSize(); tempRow++) // Keep iterating down the board/matrix until we get to the last row
            {
                belowSpace = getValue(tempRow, col);        // Save the space for the current index
                // Save the player and value for the current space we are in
                int tempPlayer = belowSpace->getPlayer(), tempVal = belowSpace->getValue();
                if(isValidLocation(tempRow, tempCol) &&     // If the current indexes are valid locations
                  (tempVal == 0 || tempPlayer == playerVal))// And either the tempSpace is open or it's own by the player
                    belowPath.push_back(belowSpace);        // Then insert the space in that location to the path
                else                                        // Else the locations is invalid or it's not owned by the player
                    break;                                  // We break as we reached the end of this path
            }
            paths.push_back(belowPath);                     // Add the path to the list of paths
        }
        // Now we can check if there is a path to our left -> row stayrs the same, col - 1
        tempRow = row, tempCol = col - 1;
        Space* leftSpace = getValue(tempRow, tempCol);      // Get the left space
        if (isValidLocation(tempRow, tempCol) && leftSpace->getValue() == 0) // If the location is valid & the it's an open space
        {
            std::vector <Space*> leftPath;                  // Create new vector to hold the path to our left
            for (tempCol = col; tempCol >= 0; tempCol--)    // Keep iterating to our left until we reach the left most column
            {
                leftSpace = getValue(tempRow, tempCol);     // Get the space for the current indexes
                // Save the player and value for the current space we are in
                int tempPlayer = leftSpace->getPlayer(), tempVal = leftSpace->getValue();
                if (isValidLocation(tempRow, tempCol) &&    // If the indexes are within the board/matrix
                   (tempVal == 0 || tempPlayer == playerVal))   // And, either, the space is open or owned by the player
                    leftPath.push_back(leftSpace);          // Then we insert the element in the current indexes
                else                                        // Else the space is not open or we are out of bound of the board
                    break;                                  // Then we are done with this path
            }
            paths.push_back(leftPath);                      // Insert the left path into our list of paths
        }
        // Now we check if there is a path to our right -> row stays the same, col + 1
        tempRow = row, tempCol = col + 1;
        Space* rightSpace = getValue(tempRow, tempCol);     // Get the space on our right
        if (isValidLocation(tempRow, tempCol) &&            // If the indexes are within the matrix
            (rightSpace->getValue() == 0 || rightSpace->getPlayer() == playerVal))   // If the space is open or its owned by the player
        {
             std::vector <Space*> rightPath;                // Create path to add our spaces to our right
             for (tempCol = col; tempCol < getSize(); tempCol++)    // Iterate to the right until we reach the last/right-most column
             {
                 rightSpace = getValue(tempRow, tempCol);   // Save the current space for the current indexes
                 // Save the player and value for the current space we are in
                 int tempPlayer = rightSpace->getPlayer(), tempVal = rightSpace->getValue();
                 if (isValidLocation(tempRow, tempCol) &&   // If the current indexes are valid locations
                    (tempVal == 0 || tempPlayer == playerVal))   // And, either, the space is open or it's owned by the player
                     rightPath.push_back(rightSpace);       // Then we insert the space in the location to the path
                 else                                       // Else the space is out of the board or it's owned by the other player
                     break;                                 // Then we are this path is done
             }
             paths.push_back(rightPath);                    // Insert the right path into our list of paths
        }

        /**
         * Now we need to get the diagonal paths for the space
         * Diagonal paths are like getting: North-East, North-west, South-East, and South-West
         * Or equivalent: up-right, up-left, down-right, down-left paths
         * */

        // Evaluate the up-right path -> row-1, col+1
        tempRow = row - 1, tempCol = col + 1;
        Space* upRightSp = getValue(tempRow, tempCol);  // Get the up-right space
        if (isValidLocation(tempRow, tempCol) &&        // If the indexes are within the board
           (upRightSp->getValue() == 0 || upRightSp->getPlayer() == playerVal))     // And, either, the space is open or it's own by the player
        {
            std::vector<Space*> upRightPath;            // Create a new path
            tempRow = row, tempCol = col;
            while (isValidLocation(tempRow, tempCol))   // While the indexes are within the size of the board
            {
                upRightSp = getValue(tempRow, tempCol); // Get the current space for the indexes
                int tempPlayer =  upRightSp->getPlayer(), tempVal = upRightSp->getValue();
                if (tempVal == 0 || tempPlayer == playerVal)    // If the space is open or if the player owns it
                    upRightPath.push_back(upRightSp);   // Then we add this path to the path
                else                                    // Else we got to the end of the path
                    break;                              // We leave the loop
                tempRow--, tempCol++;                   // Update the row and column
            }
            paths.push_back(upRightPath);               // Insert the path into the list of paths
        }

        // Evaluate the up-left path -> row-1, col-1
        tempRow = row - 1, tempCol = col - 1;
        Space* upLeftSp = getValue(tempRow, tempCol);   // Get the up-left space
        if (isValidLocation(tempRow, tempCol) &&
            (upLeftSp->getValue() == 0 || upLeftSp->getPlayer() == playerVal))
        {
            std::vector <Space*> upLeftPath;            // Create a new list of spaces for the new path
            tempRow = row, tempCol = col;               // Reset the row and column
            while (isValidLocation(row, col))           // While the indexes are valid
            {
                upLeftSp = getValue(tempRow, tempCol);  // Get the space of the current index
                int tempPlayer = upLeftSp->getPlayer(), tempVal = upLeftSp->getValue();
                if (tempPlayer == playerVal || tempVal == 0)    // If the player owns this space or if it's open
                    upLeftPath.push_back(upLeftSp);     // Insert the space into the path
                else                                    // Else this we got to a space owned by the other player
                    break;                              // We break off the loop as we reached the end of this path
                tempRow--, tempCol--;                   // Update the row and column
            }
            paths.push_back(upLeftPath);                // Add the path to the list of paths
        }

        // Evaluate the down-right path -> row+1, col+1
        tempRow = row + 1, tempCol = col + 1;
        Space* downRightSp = getValue(tempRow, tempCol);    // Get the down-right space
        if (isValidLocation(tempRow, tempCol) &&    // If the location is within the board
            (downRightSp->getValue() == 0 || downRightSp->getPlayer() == playerVal))    // And, either, the space is open or owned by the player
        {
            std::vector <Space*> downRightPath;                 // Create path to add the spaces in this diagonal direction
            tempRow = row, tempCol = col;
            while (isValidLocation(tempRow, tempCol))           // While both the indexes are within the board
            {
                downRightSp = getValue(tempRow, tempCol);       // Get the space for the current indexes
                // Save the player & value of the current space
                int tempPlayer = downRightSp->getPlayer(), tempVal = downRightSp->getValue();
                if (tempVal == 0 || tempPlayer == playerVal)    // If the space is open or it's owned by the player
                    downRightPath.push_back(downRightSp);       // Then we can add the space to the path
                else                                            // Else the space is not available
                    break;                                      // We are done with this path
                tempRow++, tempCol++;                           // Update both the row and column for the next space
            }
            paths.push_back(downRightPath);                     // Add this diagonal path to the list of paths
        }

        // Evaluate the down-left path -> row-1, col-1
        tempRow = row + 1, tempCol = col - 1;
        Space* downLeftSp = getValue(tempRow, tempCol);         // Get the down-left space
        if (isValidLocation(tempRow, tempCol) &&                // If the indexes are within the board
           (downLeftSp->getValue() == 0 && downLeftSp->getPlayer() == playerVal))   // If the space is open or is owned by the player
        {
            std::vector<Space*> downLeftPath;                   // We create a new list for this new path]
            tempRow = row, tempCol = col;                       // Reset el row y el column
            while (isValidLocation(tempRow, tempCol))           // While the indexes are inside the board
            {
                downLeftSp = getValue(tempRow, tempCol);        // Get the space for the current index
                int tempPlayer = downLeftSp->getPlayer(), tempVal = downLeftSp->getValue();
                if (tempPlayer == playerVal || tempVal == 0)    // If either the space is open or it's owned by the player
                    downLeftPath.push_back(downLeftSp);         // Then add the space in the path
                else                                            // Else we got to the end of this path
                    break;                                      // We break off the loop
                tempRow++, tempCol--;                           // Update the row and column
            }
            paths.push_back(downLeftPath);                      // Add the path to the list of paths
        }
    }
    // We get here after reviewing all the spaces and their potential paths
    return paths;                                           // We return the paths
}

std::vector<Space *> Board::getSpaces(int player)
{
    /**
     * Method iterates through the 2D matrix of Spaces to get all the Spaces hold by the player requested
     * Each player holds a minimum of one space at any time of the game
     * @param the enum player value that we want to get the spaces they hold
     * @return List of spaces that the player holds
     * */

    std::vector <Space*> spaces;                            // Create the list that will hold and return the spaces of the player
    for (int row = 0; row < getSize(); row++)               // Iterate by every row
    {
        for (int col = 0; col < getSize(); col++)           // Iterate through every column
        {
            Space* space = getValue(row, col);              // Get the space for the current row/col
            if (space->getPlayer() == player)               // If the current space is owned by the player
                spaces.push_back(space);                    // Then we add the space in the list
            else                                            // Else it's not owned by the player
                continue;                                   // We move to the next element
        }
    }

    return spaces;                                          // Return the list of spaces hold by the player
}