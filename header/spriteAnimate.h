#ifndef ANIMATE_OBJECT_H_
#define ANIMATE_OBJECT_H_

#include "../header/header.h"
#include "../header/baseObject.h"


class AnimateObject : public BaseObject 
{
public:
    AnimateObject();
    ~AnimateObject();

    //getter
    SDL_Rect GetRect() const 
    {
        return src;
    }
    
    //Setter
    void SetRect(SDL_Texture* _texture);

    void HandleClip();

    int frame;
    int loop;
    int timer = FPS / 6;
private:
    SDL_Rect src;
};

#endif