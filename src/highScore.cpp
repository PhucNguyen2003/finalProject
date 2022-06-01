#include "../header/highScore.h"

#include "../header/header.h"
#include "../header/gameStack.h"
#include "../header/render.h"

static bool quit = false;

//audio
enum SFX { SND_CLICK, SND_CONFIRM_CLICK, SND_MAX };
const int MAX_SND_CHANNELS = 8;
static Mix_Chunk* sound[SND_MAX];

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
        if(_event->keysym.sym == SDLK_SPACE ) 
        {
            gameStack.push(GAME);
            quit = true;
        }

        if(_event->keysym.sym == SDLK_ESCAPE ) 
        {
            quit = true;
        }
    }
}

static void doMouse(SDL_MouseButtonEvent* _event) 
{
    quit = true;
}

static void doInput() {
    while (SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT) 
        {
            gameStack.push(QUIT);
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

static void drawHighScoreBoard() 
{
    SDL_Texture* _texture;
    SDL_Color aColor = {255, 211, 0};

    //high score title
    std::string hsBoard = "- HIGH SCORE -";
    _texture = loadTextTexture(hsBoard, aColor, font);
    applyTexture(_texture, SCREEN_WIDTH / 3 + 40, SCREEN_HEIGHT / 6);
    SDL_DestroyTexture(_texture);

    //titles
    for(int i = 0; i < 8; i++)
    {
        hsBoard = std::to_string(i + 1) + ". ------------ " + std::to_string(highScoreList[i]);
        _texture = loadTextTexture(hsBoard, aColor, font);

        applyTexture(_texture, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4 + 50 * i);

        SDL_DestroyTexture(_texture);
    }

    hsBoard = "Hit SPACE to start a new game";
    _texture = loadTextTexture(hsBoard, aColor, font);
    applyTexture(_texture, SCREEN_WIDTH / 4 + 10 , SCREEN_HEIGHT - 100);

    SDL_DestroyTexture(_texture);
    _texture = NULL;
}

static void draw() 
{
    applyTexture(bkGround, 0, 0);

    drawHighScoreBoard();


}

void highScore() 
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