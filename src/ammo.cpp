#include "../header/ammo.h"

Ammo::Ammo() 
{
    xVal = BULLET_SPEED;
    yVal = 0;

    health = 1;
}

Ammo::~Ammo() 
{}

void Ammo::HandleMove() 
{
    xPos += xVal;
    yPos += yVal;

    if(xPos + width < 0 || xPos > SCREEN_WIDTH) 
    {
        health = 0;
    }
    if(yPos + height < 0 || yPos > SCREEN_HEIGHT) 
    {
        health = 0;
    }
}