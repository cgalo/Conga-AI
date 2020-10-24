//
// Created by Carlos Galo on 10/23/20.
//

#include "Player.h"

Player::Player(int val)
{
    this->value = val;
}

Player::Player(int value, Space* space)
{
    this->value = value;
    Spaces.push_back(space);
}

int Player::getValue() const {
    return value;
}

void Player::setValue(int value) {
    Player::value = value;
}

const std::vector<Space *> &Player::getSpaces() const {
    return Spaces;
}

void Player::updateSpaces(const std::vector<Space *> &spaces)
{
    Spaces = spaces;
}

