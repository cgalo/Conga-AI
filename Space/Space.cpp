//
// Created by Carlos Galo on 10/23/20.
//

#include "Space.h"

Space::Space(int row, int col, int val, int player)
{
    this->value = val;
    this->row = row;
    this->column = col;
    this->player = player;
}

int Space::getValue() const {
    return value;
}

void Space::setValue(int value) {
    Space::value = value;
}

int Space::getPlayer() const {
    return player;
}

void Space::setPlayer(int player) {
    Space::player = player;
}

int Space::getRow() const {
    return row;
}

void Space::setRow(int row) {
    Space::row = row;
}

int Space::getColumn() const {
    return column;
}

void Space::setColumn(int column) {
    Space::column = column;
}
