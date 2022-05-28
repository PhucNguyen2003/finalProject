#ifndef HEADER_H_
#define HEADER_H_

//sdl library
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <windows.h>

//standar library
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <math.h>
#include <string>
#include <stack>

//constant
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FPS = 60;
const int MAX_LINE_LENGTH = 1024;

const float PLAYER_SPEED = 4;
const float BULLET_SPEED = 16;
const float ENEMY_BULLET_SPEED = 8;

//sdl var
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* bkGround;
extern TTF_Font* font;
extern TTF_Font* titleFont;
extern TTF_Font* smallFont;
extern SDL_Event event;

//game fucntion for stack
enum GAME_FUNCTION {MENU = -1, GAME, HIGH_SCORE, CREDIT, QUIT, MAX_FUNCTION};

//high score list
extern int highScoreList[8];

#endif