#ifndef PLAYER_H_
#define PLAYER_H_

#include "header.h"
#include "baseObject.h"

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