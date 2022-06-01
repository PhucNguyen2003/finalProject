#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "header.h"

class BaseObject {
public:
    BaseObject();
    virtual ~BaseObject();  //base destructor, need virtual

    //getter
    float GetX() const 
    {
        return xPos;
    }
    float GetY() const 
    {
        return yPos;
    }
    int GetWidth() const 
    {
        return width;
    }
    int GetHeight() const
    {
        return height;
    }
    float GetXVal() const 
    {
        return xVal;
    }
    float GetYVal() const 
    {
        return yVal;
    }
    int GetHealth() const 
    {
        return health;
    }
    
    //setter
    void SetX(float _x) 
    {
        xPos = _x;
    } 
    void SetY(float _y) 
    {
        yPos = _y;
    }
    void SetWidthHeight(SDL_Texture* _texture) 
    {
        SDL_QueryTexture(_texture, NULL, NULL, &width, &height);
    }
    void SetHealth(int _health) 
    {
        health = _health;
    }
    void SetXVal(float _xVal) 
    {
        xVal = _xVal;
    }
    void SetYVal(float _yVal) 
    {
        yVal = _yVal;
    }
    
    void HandleMove();
    void ReduceHealth(int _x) 
    {
        health -= _x;
    }
protected:
    float xPos, yPos;   //position
    float xVal, yVal;   //movement
    int width, height;  //size

    //health to call for a destructor or quit game
    int health;
};

#endif