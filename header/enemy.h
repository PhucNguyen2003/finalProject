#ifndef ENEMY_H_
#define ENEMY_H_

#include "header.h"
#include "baseObject.h"

class Enemy : public BaseObject {
public:
    Enemy();
    virtual ~Enemy();

    //getter
    int GetReload() const 
    {
        return reload;
    }

    //setter
    void SetReload(int _reload) 
    {
        reload = _reload;
    }

    //enemy movement
    void HandleMove();

    int reload;
};

#endif