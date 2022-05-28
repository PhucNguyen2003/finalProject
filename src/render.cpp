#include "../header/render.h"

void prepareScene()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void presentScene()
{
	SDL_RenderPresent(renderer);
}

SDL_Texture* loadTexture(std::string path)
{
	SDL_Surface* loadSurface = IMG_Load(path.c_str());

	if(loadSurface == NULL) 
	{
		std::cout << "Unable to load image at " << path.c_str() << SDL_GetError() << '\n';
	}

	//colour key
	SDL_SetColorKey( loadSurface, SDL_TRUE, SDL_MapRGB( loadSurface->format, 255, 255, 255 ) );

	//load texture
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);

	//free loaded surface
	SDL_FreeSurface(loadSurface);
	loadSurface = NULL;

	return newTexture;
}

void applyTexture(SDL_Texture *texture, int x, int y)
{
	SDL_Rect des;

	des.x = x;
	des.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &des.w, &des.h);

	SDL_RenderCopy(renderer, texture, NULL, &des);
}

void renderRect(SDL_Texture *texture, SDL_Rect src, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = src.w;
	dest.h = src.h;

	SDL_RenderCopy(renderer, texture, &src, &dest);
}

SDL_Texture* loadTextTexture( std::string _textureText, SDL_Color _textColor, TTF_Font* _font)
{	
	SDL_Texture* _texture;

    SDL_Surface* _textSurface = TTF_RenderText_Solid(_font, _textureText.c_str(), _textColor);
    if(_textSurface == NULL)
    {
        std::cout << "can not create surface. Error: " << SDL_GetError() << "\n";
    }
    else
    {
        _texture = SDL_CreateTextureFromSurface( renderer, _textSurface );
        if( _texture == NULL )
        {
            std::cout << "Unable to create texture from rendered text! SDL Error: " <<  SDL_GetError() << "\n";
        }

        //Get rid of old surface
        SDL_FreeSurface( _textSurface );
    }

	return _texture;
}

void capFrameRate(long *_then, float *_remainder)
{
	long wait, frameTime;

	wait = 16 + *_remainder;

	*_remainder -= (int) *_remainder;

	frameTime = SDL_GetTicks() - *_then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*_remainder += 0.667;

	*_then = SDL_GetTicks();
}

