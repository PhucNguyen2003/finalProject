#ifndef PLAYER_H_
#define PLAYER_H_

#include "../header/header.h"
#include "../header/baseObject.h"

class Player : public BaseObject {
public:
    Player();
    virtual ~Player();

    //getter
    int GetReload() const 
    {
        return reload;
    }

    //setter
    int SetReload() 
    {
        reload = 2 * FPS;
    }
    
    void HandleMove();
    
    int reload;
};

#endif