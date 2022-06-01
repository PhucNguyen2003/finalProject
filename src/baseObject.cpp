#include "baseObject.h"

BaseObject::BaseObject()
{
    health = 1;
}

BaseObject::~BaseObject()
{}

void BaseObject::HandleMove() 
{
    xPos += xVal;
    yPos += yVal;
}