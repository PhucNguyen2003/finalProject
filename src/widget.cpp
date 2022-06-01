#include "widget.h"

#include "header.h"
#include "render.h"
#include "gameStack.h"
#include "utility.h"

const int MAX_CHOICE = 4;

static bool quit = false;
SDL_Event event;
static bool buttonChosen[MAX_FUNCTION];
static int currentChoice = 0;
static bool doChoice = false;

enum CHANNEL { CH_ANY = -1 };
enum SFX { SND_MOVE_CHOICE, SND_CONFIRM_CHOICE, SND_MAX };
const int MAX_SND_CHANNELS = 8;
static Mix_Music* music;
static Mix_Chunk* sound[SND_MAX];

static void initAudio() 
{
    music = Mix_LoadMUS("res/sound/magic_space.mp3");
    if(music == NULL) 
    {
        quit = true;
    }

    //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( music, -1 );
        Mix_VolumeMusic(32);
    }

    sound[SND_MOVE_CHOICE] = Mix_LoadWAV("res/sound/move_choice.wav");
    Mix_VolumeChunk(sound[SND_MOVE_CHOICE], 16);
    if(sound[SND_MOVE_CHOICE] == NULL) 
    {
        quit = true;
    }

    sound[SND_CONFIRM_CHOICE] = Mix_LoadWAV("res/sound/confirm_choice.wav");
    Mix_VolumeChunk(sound[SND_CONFIRM_CHOICE], 16);
    if(sound[SND_CONFIRM_CHOICE] == NULL) 
    {
        quit = true;
    }
}

static void init() 
{
    initAudio();
}

static void clear() {
    for(int i = 0; i < SND_MAX; i++) 
    {
        Mix_FreeChunk(sound[i]);
        sound[i] = NULL;
    }

    Mix_FreeMusic(music);
    music = NULL;

    quit = false;
    currentChoice = 0;

    SDL_DestroyTexture(bkGround);
    bkGround = NULL;
}

static void doKeydown(SDL_KeyboardEvent* _event) 
{
    if(_event->repeat == 0) 
    {
        if(_event->keysym.sym == SDLK_UP ) 
        {
            currentChoice--;
            if(currentChoice < 0)currentChoice = MAX_FUNCTION - 1;

            Mix_PlayChannel(CH_ANY, sound[SND_MOVE_CHOICE], 0);
        }

        if(_event->keysym.sym == SDLK_DOWN ) 
        {
            currentChoice++;
            if(currentChoice >= MAX_FUNCTION) currentChoice = 0;

            Mix_PlayChannel(CH_ANY, sound[SND_MOVE_CHOICE], 0);
        }

        if(_event->keysym.sym == SDLK_ESCAPE ) 
        {
            gameStack.push(QUIT);
            quit = true;
        }

        if(_event->keysym.sym == SDLK_RETURN ) 
        {
            doChoice = true;
            quit = true;

            Mix_PlayChannel(CH_ANY, sound[SND_CONFIRM_CHOICE], 0);
        }
    }
}

static void doMouse(SDL_MouseButtonEvent* _event) 
{
    int _x, _y;
    SDL_GetMouseState(&_x, &_y);

    //game
    if(findPoint(640, 470, 971, 492, _x, _y)) {
        currentChoice = 0;
        doChoice = true;
        quit = true;
    }

    //high score
    if(findPoint(664, 520, 996, 542, _x, _y)) {
        currentChoice = 1;
        doChoice = true;
        quit = true;
    }

    //credit
    if(findPoint(640, 570, 877, 592, _x, _y)) {
        currentChoice = 2;
        doChoice = true;
        quit = true;
    }

    //quit
    if(findPoint(664, 620, 972, 642, _x, _y)) {
        currentChoice = 3;
        doChoice = true;
        quit = true;
    }
}

static void doInput() 
{
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

    for(int i = 0; i < MAX_CHOICE; i++) 
    {
        if(i == currentChoice)buttonChosen[i] = true;
        else buttonChosen[i] = false;
    }

    if(buttonChosen[GAME] && doChoice) 
    {
        gameStack.push(GAME);

        Mix_PlayChannel(CH_ANY, sound[SND_CONFIRM_CHOICE], 0);
    }

    if(buttonChosen[HIGH_SCORE] && doChoice) 
    {
        gameStack.push(HIGH_SCORE);

        Mix_PlayChannel(CH_ANY, sound[SND_CONFIRM_CHOICE], 0);
    }

    if(buttonChosen[CREDIT] && doChoice) 
    {
        gameStack.push(CREDIT);

        Mix_PlayChannel(CH_ANY, sound[SND_CONFIRM_CHOICE], 0);
    }

    if(buttonChosen[QUIT] && doChoice) 
    {
        gameStack.push(QUIT);

        Mix_PlayChannel(CH_ANY, sound[SND_CONFIRM_CHOICE], 0);
    }
    
    doChoice = false;
}

static void drawChoice(std::string _text, bool isChosen, int x, int y) 
{
    SDL_Color _color;

    if(isChosen) 
    {
        _color = {0, 255, 0};
    }
    else 
    {
        _color = {255, 255, 255};
    }

    SDL_Texture* _texture = loadTextTexture(_text, _color, font);
    applyTexture(_texture, x, y);

    SDL_DestroyTexture(_texture);
    _texture = NULL;
}

static void drawTitle() 
{
    SDL_Color _color = {0, 255, 255};

    std::string text = "HERO";
    SDL_Texture* _texture = loadTextTexture(text, _color, titleFont);
    applyTexture(_texture, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);

    SDL_DestroyTexture(_texture);

    text = "- A BATTLE IN SPACE - ";
    _texture = loadTextTexture(text, _color, titleFont);
    applyTexture(_texture, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 3);
    SDL_DestroyTexture(_texture);

    SDL_DestroyTexture(_texture);
    _texture = NULL;
}

static void draw()
{
    applyTexture(bkGround, 0, 0);

    drawTitle();

    drawChoice("> START GAME <", buttonChosen[GAME], SCREEN_WIDTH / 2, SCREEN_HEIGHT - 250);
    drawChoice(" > HIGH SCORE <", buttonChosen[HIGH_SCORE], SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200);
    drawChoice("> CREDIT <", buttonChosen[CREDIT], SCREEN_WIDTH / 2, SCREEN_HEIGHT - 150);
    drawChoice(" > QUIT GAME <", buttonChosen[QUIT], SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);
}

void menu() 
{
    init();

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