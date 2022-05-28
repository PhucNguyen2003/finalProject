#include "../header/spriteAnimate.h"

AnimateObject::AnimateObject() {
    src.x = 0;
    src.y = 0;
    frame = 8;
    
    health = 1;
}

AnimateObject::~AnimateObject()
{}

void AnimateObject::HandleClip() 
{
    int currentFrame = static_cast<int>( (SDL_GetTicks() / FPS) % frame );
    src.x = src.w * currentFrame;

    if( --timer < 0) 
    {
        health = 0;
    }
}

void AnimateObject::SetRect(SDL_Texture* _texture) 
{
    SDL_QueryTexture(_texture, NULL, NULL, &width, &height);

    src.w = width / frame;
    src.h = height;
}