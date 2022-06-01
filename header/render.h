#ifndef RENDER_H_
#define RENDER_H_

#include "header.h"

//handle rendering and fps cap

void prepareScene();

void presentScene();

SDL_Texture* loadTexture(std::string path);

void applyTexture(SDL_Texture *texture, int x, int y);

void renderRect(SDL_Texture *texture, SDL_Rect src, int x, int y);

void capFrameRate(long *then, float *remainder);

SDL_Texture* loadTextTexture(std::string textureText, SDL_Color textColor, TTF_Font* _font);

#endif