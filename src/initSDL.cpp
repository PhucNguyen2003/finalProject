#include "../header/initSDL.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* bkGround;
TTF_Font* font;
TTF_Font* titleFont;
TTF_Font* smallFont;

bool init() 
{   //success
    //inititalize flag
    bool success = true;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) 
    {  //SDL inititalize
        std::cout << "unable to initialize " << SDL_GetError() <<'\n';
        success = false;
    } 
    else 
    {
        //create window
        window = SDL_CreateWindow("Hero", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL) 
        {
            std::cout << "unable to create window " << SDL_GetError() << '\n';
            success = false;
        } 
        else 
        {

            //set game icon
            SDL_Surface* icon = IMG_Load("res/images/icon.png");
            SDL_SetWindowIcon(window, icon);

            //Set texture filtering to linear
            if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
            {
                std::cout << "Warning: Linear texture filtering not enabled!";
            }

            //create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL) 
            {
                std::cout << "unable to create renderer" << SDL_GetError() << '\n';
                success = false;
            } 
            else 
            {

                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) 
                {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n";
                    success = false;
                }
            }
        }
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
        std::cout << "can not initialize mixer\n";
		success = false;
	}

    if(TTF_Init() == -1)
    {
        std::cout << "TTF_Init: " << TTF_GetError() << '\n';
        success = false;
    }

    font = TTF_OpenFont("res/ttf/PressStart.ttf", 24);
    if(font == NULL) 
    {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << '\n';
        success = false;
    
    }
    smallFont = TTF_OpenFont("res/ttf/aFont.ttf", 18);
    if(smallFont == NULL) 
    {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << '\n';
        success = false;
    }

    titleFont = TTF_OpenFont("res/ttf/Titillium-BoldItalic.ttf", 60);
    if(titleFont == NULL) 
    {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << '\n';
        success = false;
    }



    //hide cursor
	SDL_ShowCursor(0);

    return success;
}

void close() {
    //destroy window
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    TTF_CloseFont(font);
    font = NULL;
    TTF_CloseFont(titleFont);
    titleFont = NULL;

    //quit sdl subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}