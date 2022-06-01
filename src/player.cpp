#include "player.h"

Player::Player()
{
    xVal = 0;
    yVal = 0;
    reload = 0;
    health = 5;
}

Player::~Player() 
{}

void Player::HandleMove() 
{
    xPos += xVal;
    if(xPos < 0 || xPos + width > SCREEN_WIDTH) 
    {
        xPos -= xVal;
    }

    yPos += yVal;
    if(yPos < 100 || yPos + height > SCREEN_HEIGHT) 
    {
        yPos -= yVal;
    }
}