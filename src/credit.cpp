#include "../header/credit.h"

#include "../header/header.h"
#include "../header/gameStack.h"
#include "../header/render.h"

static bool quit = false;

//audio
enum SFX { SND_CLICK, SND_CONFIRM_CLICK, SND_MAX };
const int MAX_SND_CHANNELS = 8;
static Mix_Chunk* sound[SND_MAX];

//text
const int MAX_LINE = 20;
std::string textBlock[MAX_LINE] =  
{
    "                                  - visual -                                   ",
    "     - spaceship -                                                             ",
    "Lunar Lander Asset by Matt Walkden                                             ",
    "https://mattwalkden.itch.io/lunar-battle-pack                                  ",
    "                                                                               ",
    "                                  - music -                                    ",
    "                                                                               ",
    "     - ingame soundtrack -                                                     ",
    "Deflector by Ghostrifter Official | https://soundcloud.com/ghostrifter-official",
    "Music promoted by https://www.chosic.com/free-music/all/                       ",
    "Creative Commons CC BY-SA 3.0                                                  ",
    "https://creativecommons.org/licenses/by-sa/3.0/                                ",
    "                                                                               ",
    "     - baby alien sound -                                                      ",
    "Sound from Zapsplat.com                                                        ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                           - Thank you for playing -                           "
};

static void clear() 
{
    SDL_DestroyTexture(bkGround);
    bkGround = NULL;

    quit = false;
}

static void doKeydown(SDL_KeyboardEvent* _event) 
{
    if(_event->repeat == 0) 
    {
        if(_event->keysym.sym == SDLK_ESCAPE || _event->keysym.sym == SDLK_RETURN) 
        {
            quit = true;
        }
    }
}

static void doMouse(SDL_MouseButtonEvent* _event) 
{
    if(_event->button == SDL_BUTTON_RIGHT) 
    {
        quit = true;
    }
}

static void doInput() 
{
    while (SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT) 
        {
            while(!gameStack.empty()) 
            {
                gameStack.pop();
            }
            quit = true;
        }

        if(event.type == SDL_KEYDOWN) 
        {
            doKeydown(&event.key);
        }

        if(event.type == SDL_MOUSEBUTTONDOWN) 
        {
            doMouse(&event.button);
        }
	}
}

static void logic()
{
    doInput();
}

static bool drawText() 
{
    SDL_Color aColor = {255, 211, 0};
    SDL_Texture* aTexture;
    for(int i = 0; i < MAX_LINE; i++) 
    {
        aTexture = loadTextTexture(textBlock[i], aColor, smallFont);
        applyTexture(aTexture, SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20 + i * 20);
    }

    SDL_DestroyTexture(aTexture);
    aTexture = NULL;
}

static void draw() 
{
    applyTexture(bkGround, 0, 0);
    
    //write text
    drawText();
}

void credit() 
{
    long then = SDL_GetTicks();
    float remainder = 0;

    bkGround = loadTexture("res/images/background.png");

    while(!quit) 
    {
		prepareScene();

        logic();
        draw();

		presentScene();
        capFrameRate(&then, &remainder);
    }
    
    clear();
}