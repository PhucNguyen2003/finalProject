#include "../header/enemy.h"

Enemy::Enemy() 
{   
    xVal = -(2 + (rand() % 4));
    yVal = 0;
    
    health = 1;
    reload = FPS * (1 + (rand() % 3));
}

Enemy::~Enemy() 
{}

void Enemy::HandleMove() 
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
