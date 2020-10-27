//
// Created by Carlos Galo on 10/23/20.
//

#ifndef CONGA_AI_SPACE_H
#define CONGA_AI_SPACE_H


class Space {
private:
    int value;                              // Value for this space
    int player;                             // Player who holds this space
    int row;                                // Row location in the matrix/graph
    int column;                             // Column location in the matrix graph

public:
    Space(int row, int col, int val=0, int player=-1);   // Constructor, value is set to 0 if non is given

    // Getters and setters
    int getValue() const;
    void setValue(int value);

    int getPlayer() const;
    void setPlayer(int player);

    int getRow() const;
    void setRow(int row);

    int getColumn() const;
    void setColumn(int column);
};


#endif //CONGA_AI_SPACE_H
