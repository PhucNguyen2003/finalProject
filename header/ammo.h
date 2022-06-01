#ifndef AMMO_H_
#define AMMO_H_

#include "header.h"
#include "baseObject.h"

class Ammo : public BaseObject 
{
public:
    enum AMMO_TYPE {NONE = 0, LAZER, SPHERE};
    Ammo();
    virtual ~Ammo();

    //getter
    int GetType() const 
    {
        return ammoType;
    }

    //setter
    int SetType(int _type) 
    {
        ammoType = _type;
    }

    void HandleMove();

protected:
    int ammoType;
};

#endif