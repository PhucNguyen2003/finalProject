#include "../header/game.h"

#include "../header/header.h"
#include "../header/render.h"
#include "../header/player.h"
#include "../header/enemy.h"
#include "../header/ammo.h"
#include "../header/utility.h"
#include "../header/spriteAnimate.h"
#include "../header/gameStack.h"
#include "../header/highScore.h"

//game var defintion
static bool quit = false;
int enemySpawnTimer = FPS;
int score = 0;
int highScoreList[8] = {0};

//background star and scrolling background
const int MAX_STAR = 500;
BaseObject star[MAX_STAR];
int backgroundX = 0;

//texture
static SDL_Texture* playerTexture;
static SDL_Texture* playerAmmoTexture;
static SDL_Texture* enemyTexture;
static SDL_Texture* enemyAmmoTexture;
static SDL_Texture* scoreTexture;
static SDL_Texture* lifepointTexture;
static SDL_Texture* explosionTexture;
static SDL_Texture* bannerTexture;

//game entity
Player* player;
std::vector<Ammo> playerAmmoList;
std::vector<Enemy> enemyList;
std::vector<Ammo> enemyAmmoList;
std::vector<AnimateObject> explosionList;

//audio
enum CHANNEL { CH_ANY = -1, CH_PLAYER, CH_ENEMY_FIRE, CH_ENEMY_DIE };
enum SFX { SND_PLAYER_FIRE, SND_ENEMY_FIRE, SND_PLAYER_DIE, SND_ENEMY_DIE, SND_MAX };
const int MAX_SND_CHANNELS = 8;
static Mix_Music* music;
static Mix_Chunk* sound[SND_MAX];

//start a game
static void initBackground() 
{
    bkGround = loadTexture("res/images/background.png");
    if(bkGround == NULL) 
    {
        quit = true;
    }

	for (int i = 0 ; i < MAX_STAR ; i++) 
    {
		star[i].SetX( rand() % SCREEN_WIDTH );
		star[i].SetY( rand() % SCREEN_HEIGHT );
		star[i].SetXVal( -( 1 + rand() % 8 ) );
        star[i].SetYVal( 0 );
	}
}

static void initGameAudio() 
{
    music = Mix_LoadMUS("res/sound/bgmusic.mp3");
    if(music == NULL) 
    {
        quit = true;
    }

    //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( music, -1 );
        Mix_VolumeMusic(16);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);

    sound[SND_PLAYER_FIRE] = Mix_LoadWAV("res/sound/playerAmmo.mp3");
    if(sound[SND_PLAYER_FIRE] == NULL) 
    {
        quit = true;
    }
    Mix_VolumeChunk(sound[SND_PLAYER_FIRE], 16);

    sound[SND_ENEMY_FIRE] = Mix_LoadWAV("res/sound/babyAlien.mp3");
    if(sound[SND_ENEMY_FIRE] == NULL) 
    {
        quit = true;
    }

    sound[SND_ENEMY_DIE] = Mix_LoadWAV("res/sound/babyAlienDie.mp3");
    if(sound[SND_ENEMY_DIE] == NULL) 
    {
        quit = true;
    }
}

static void initTexture() 
{
    playerTexture = loadTexture("res/images/aship.png");
    if(playerTexture == NULL) 
    {
        quit = true;
    }

    playerAmmoTexture = loadTexture("res/images/playerammo.png");
    if(playerAmmoTexture == NULL) 
    {
        quit = true;
    }

    enemyAmmoTexture = loadTexture("res/images/enemyBullet.png");
    if(enemyAmmoTexture == NULL) 
    {
        quit = true;
    }

    enemyTexture = loadTexture("res/images/Emissary.png");
    if(enemyTexture == NULL) 
    {
        quit = true;
    }

    lifepointTexture = loadTexture("res/images/aCrew.png");
    if(lifepointTexture == NULL) 
    {
        quit = true;
    }

    explosionTexture = loadTexture("res/images/explosion.png");
    if(explosionTexture == NULL) 
    {
        quit = true;
    }

    bannerTexture = loadTexture("res/images/Untitled.png");
    if(bannerTexture == NULL) 
    {
        quit = true;
    }
}

static void initPlayer() 
{
    player = new Player();

    player->SetX(100);
	player->SetY(100);
    player->SetWidthHeight(playerTexture);

    if(player == NULL)
    {
        quit = true;
    }
}

void initGame() 
{
    initGameAudio();

    initTexture();

    initBackground();

    initPlayer();
}

//generate a game
void spawnEnemy() 
{
    srand(time(0));

    if (--enemySpawnTimer <= 0)
	{
        Enemy anEnemy;

		anEnemy.SetX(SCREEN_WIDTH);
		anEnemy.SetY( 100 + rand() % (SCREEN_HEIGHT - 120) );
        anEnemy.SetWidthHeight(enemyTexture);

        enemyList.push_back( anEnemy );

		enemySpawnTimer = 30 + (rand() % ( FPS * 2 ) );
	}
}

//clean up after a game
static void clear() 
{
    //todo
    delete player;
    player = NULL;

    SDL_DestroyTexture(playerTexture);
    playerTexture = NULL;
    SDL_DestroyTexture(playerAmmoTexture);
    playerAmmoTexture = NULL;
    SDL_DestroyTexture(enemyTexture);
    enemyTexture = NULL;
    SDL_DestroyTexture(enemyAmmoTexture);
    enemyAmmoTexture = NULL;
    SDL_DestroyTexture(scoreTexture);
    scoreTexture = NULL;
    SDL_DestroyTexture(lifepointTexture);
    lifepointTexture = NULL;
    SDL_DestroyTexture(explosionTexture);
    explosionTexture = NULL;

    enemyList.clear();
    enemyAmmoList.clear();
    playerAmmoList.clear();
    explosionList.clear();

    score = 0;
    quit = false;

    for(int i = 0; i < SND_MAX; i++) 
    {
        Mix_FreeChunk(sound[i]);
        sound[i] = NULL;
    }

    Mix_FreeMusic(music);
    music = NULL;
}

//handle all action
void doBackground() {
    if(--backgroundX < -SCREEN_WIDTH) 
    {
		backgroundX = 0;
	}

    for(int i = 0 ; i < MAX_STAR ; i++) 
    {
        int starX = star[i].GetX();

		star[i].HandleMove();

		if (star[i].GetX() < 0)
		{
			star[i].SetX( SCREEN_WIDTH + starX );
		}
	}
}

static void doKeydown(SDL_KeyboardEvent* _event) 
{
    if(_event->repeat == 0) 
    {
        if(_event->keysym.sym == SDLK_UP || _event->keysym.sym == SDLK_w ) 
        {
            player->SetYVal( -PLAYER_SPEED );
        }

        if(_event->keysym.sym == SDLK_DOWN || _event->keysym.sym == SDLK_s ) 
        {
            player->SetYVal( PLAYER_SPEED );
        }

        if(_event->keysym.sym == SDLK_LEFT || _event->keysym.sym == SDLK_a ) 
        {
            player->SetXVal( -PLAYER_SPEED );
        }

        if(_event->keysym.sym == SDLK_RIGHT || _event->keysym.sym == SDLK_d ) 
        {
            player->SetXVal( PLAYER_SPEED );
        }

        if(_event->keysym.sym == SDLK_SPACE && --player->reload <= 0) 
        {
            Ammo anAmmo;

            anAmmo.SetWidthHeight( playerAmmoTexture );
            anAmmo.SetX( player->GetX() + player->GetWidth() - 10);
            anAmmo.SetY( player->GetY() + (player->GetHeight() / 2 - anAmmo.GetHeight() / 2) );

            playerAmmoList.push_back( anAmmo );

            Mix_PlayChannel(CH_PLAYER, sound[SND_PLAYER_FIRE], 0);

            player->reload = FPS / 10;
        }
    }
}

static void doKeyup(SDL_KeyboardEvent* _event) 
{
    if(_event->repeat == 0) 
    {
        if(_event->keysym.sym == SDLK_UP || _event->keysym.sym == SDLK_w ) 
        {
            player->SetYVal(0);
        }

        if(_event->keysym.sym == SDLK_DOWN || _event->keysym.sym == SDLK_s ) 
        {
            player->SetYVal(0);
        }

        if(_event->keysym.sym == SDLK_LEFT || _event->keysym.sym == SDLK_a ) 
        {
            player->SetXVal(0);
        }

        if(_event->keysym.sym == SDLK_RIGHT || _event->keysym.sym == SDLK_d ) 
        {
            player->SetXVal(0);
        }
    }
}

static void doMouse(SDL_MouseButtonEvent* _event) 
{
    if(_event->button == SDL_BUTTON_LEFT && --player->reload <= 0) 
    {
        Ammo anAmmo;

        anAmmo.SetX( player->GetX() + 30 );
        anAmmo.SetY( player->GetY() + 24 );
        anAmmo.SetWidthHeight( playerAmmoTexture );

        playerAmmoList.push_back( anAmmo );

        Mix_PlayChannel(CH_PLAYER, sound[SND_PLAYER_FIRE], 0);

        player->reload = FPS / 10;
    }
}

static void doInput() {
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

        if(event.type == SDL_KEYUP) 
        {
            doKeyup(&event.key);
        }

        if(event.type == SDL_MOUSEBUTTONDOWN) 
        {
            doMouse(&event.button);
        }
	}
}

void doPlayer() {
    
    if(player->reload > 0) 
    {
        player->reload--;
    }

    player->HandleMove();
}

void doEnemy() {
    for(int i = 0; i < enemyList.size(); i++) 
    {
        enemyList[i].HandleMove();
    }

    for(int i = 0; i < enemyList.size(); i++) 
    {
        if(checkCollision(enemyList[i].GetX(), enemyList[i].GetY(), enemyList[i].GetWidth(), enemyList[i].GetHeight(),
            player->GetX(), player->GetY(), player->GetWidth(), player->GetHeight() )) 
            {
                player->ReduceHealth(1);
                enemyList[i].ReduceHealth(1);
            }
    }

    for(int i = 0; i < enemyList.size(); i++) 
    {
        if(--enemyList[i].reload < 0) 
        {
            Ammo anAmmo;

            anAmmo.SetX( enemyList[i].GetX() + 14);
            anAmmo.SetY( enemyList[i].GetY() + 35);
            anAmmo.SetWidthHeight( enemyAmmoTexture );
            
            float _x, _y;
            calcSlope(player->GetX(), player->GetY(), enemyList[i].GetX(), enemyList[i].GetY(), &_x, &_y);
            anAmmo.SetXVal(_x * ENEMY_BULLET_SPEED);
            anAmmo.SetYVal(_y * ENEMY_BULLET_SPEED);

            enemyAmmoList.push_back( anAmmo );

            enemyList[i].reload = 30 + rand() % FPS;

            Mix_PlayChannel(CH_ENEMY_FIRE, sound[SND_ENEMY_FIRE], 0);
        } 
    }
}

void doAmmo() {
    for(int i = 0; i < playerAmmoList.size(); i++) 
    {
        playerAmmoList[i].HandleMove();
    }

    for(int i = 0; i < enemyAmmoList.size(); i++) 
    {
        enemyAmmoList[i].HandleMove();
    }

    for(int i = 0; i < playerAmmoList.size(); i++) 
    {
        for(int j = 0; j < enemyList.size(); j++) 
        {
            if( checkCollision(enemyList[j].GetX(), enemyList[j].GetY(), enemyList[j].GetWidth(), enemyList[j].GetHeight(),
                playerAmmoList[i].GetX(), playerAmmoList[i].GetY(), playerAmmoList[i].GetWidth(), playerAmmoList[i].GetHeight()) ) 
            {
                    //reduce health
                    playerAmmoList[i].ReduceHealth(1);
                    enemyList[j].ReduceHealth(1);
                    
                    //update score
                    score += 100;
            }
        }
    }

    for(int i = 0; i < enemyAmmoList.size(); i++) 
    {
        if(checkCollision(enemyAmmoList[i].GetX(), enemyAmmoList[i].GetY(), enemyAmmoList[i].GetWidth(), enemyAmmoList[i].GetHeight(),
            player->GetX(), player->GetY(), player->GetWidth(), player->GetHeight() ))
        {
            player->ReduceHealth(1);
            enemyAmmoList[i].ReduceHealth(1);
        }
    }
}

void doExplosion()
{
    //update frame
    for(int i = 0; i < explosionList.size(); i++) 
    {
        explosionList[i].HandleClip();
    }
}

//clean all entity whose health's zero
void updateEntity() {
    for(int i = 0; i < enemyList.size(); i++) 
    {
        if(enemyList[i].GetHealth() <= 0) 
        {
            //explosion here
            AnimateObject anExplosion;

            anExplosion.SetX( enemyList[i].GetX() );
            anExplosion.SetY( enemyList[i].GetY() );
            anExplosion.SetRect(explosionTexture);
            explosionList.push_back(anExplosion);

            enemyList.erase(enemyList.begin() + i);
            i--;
            
            Mix_PlayChannel(CH_ENEMY_DIE, sound[SND_ENEMY_DIE], 0);
        }
    }

    for(int i = 0; i < playerAmmoList.size(); i++) 
    {
        if(playerAmmoList[i].GetHealth() <= 0) 
        {
            playerAmmoList.erase(playerAmmoList.begin() + i);
            i--;
        }
    }

    for(int i = 0; i < enemyAmmoList.size(); i++) 
    {
        if(enemyAmmoList[i].GetHealth() <= 0) 
        {
            enemyAmmoList.erase(enemyAmmoList.begin() + i);
            i--;
        }
    }

    for(int i = 0; i < explosionList.size(); i++) 
    {
        if(explosionList[i].GetHealth() <= 0) 
        {
            explosionList.erase(explosionList.begin() + 1);
        }
    }
}

static void logic() 
{
    doBackground();

    doInput();

    doPlayer();
    
    doEnemy();

    doAmmo();

    doExplosion();

    updateEntity();
}

//render to screen
void drawBackground() 
{
    SDL_Rect dest;

	for (int x = backgroundX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH)
	{
		dest.x = x;
		dest.y = 0;
		dest.w = SCREEN_WIDTH;
		dest.h = SCREEN_HEIGHT;

		SDL_RenderCopy(renderer, bkGround, NULL, &dest);
	}

	for (int i = 0 ; i < MAX_STAR ; i++) 
    {
		int c = 32 * star[i].GetXVal();

		SDL_SetRenderDrawColor(renderer, c, c, c, 255);

		SDL_RenderDrawLine(renderer, star[i].GetX(), star[i].GetY(), star[i].GetX() + 3, star[i].GetY() );
	}

    applyTexture(bannerTexture, 0, 0);
}

void drawPlayer() {
    if(player != NULL) 
    {
        applyTexture( playerTexture, player->GetX(), player->GetY() );
    }
}

void drawEnemy() 
{
    for(int i = 0; i < enemyList.size(); i++) 
    {
        applyTexture( enemyTexture, enemyList[i].GetX(), enemyList[i].GetY() );
    }
}

void drawAmmo() 
{
    for(int i = 0; i < playerAmmoList.size(); i++) 
    {
        applyTexture( playerAmmoTexture, playerAmmoList[i].GetX(), playerAmmoList[i].GetY());
    }

    for(int i = 0; i < enemyAmmoList.size(); i++) 
    {
        applyTexture( enemyAmmoTexture, enemyAmmoList[i].GetX(), enemyAmmoList[i].GetY() );
    }
}

void drawExplosion() {
    for(int i =  0; i < explosionList.size(); i++) 
    {
        renderRect( explosionTexture, explosionList[i].GetRect(), explosionList[i].GetX(), explosionList[i].GetY() );
    }
}

static void draw() 
{
    drawBackground();

    drawPlayer();

    drawEnemy();

    drawAmmo();

    //score
    SDL_Color textColor = {255, 255, 255};
    std::string aText = "Score: " + std::to_string(score);
    scoreTexture = loadTextTexture(aText, textColor, font);
    applyTexture(scoreTexture, SCREEN_WIDTH / 20, SCREEN_HEIGHT / 20);


    //lifepoint
    for(int i = 0; i < player->GetHealth(); i++) 
    {
        SDL_Rect des;
        des.x = SCREEN_WIDTH / 3 + i * 40;
        des.y = SCREEN_HEIGHT / 20;

        SDL_QueryTexture(lifepointTexture, NULL, NULL, &des.w, &des.h);

        SDL_RenderCopy(renderer, lifepointTexture, NULL, &des);
    }

    //explosion
    drawExplosion();
}

static void pushHighScore() 
{
    for(int i = 0; i < 8; i++) 
    {
        if(highScoreList[i] < score) 
        {
            int temp = highScoreList[i];
            highScoreList[i] = score;
            score = temp;
        }
    }
}

//main game
void game() 
{

    initGame();

    long then = SDL_GetTicks();
    float remainder = 0;

    while (!quit)
	{
		prepareScene();

        spawnEnemy();

        logic();
        draw();

        if(player->GetHealth() <= 0) 
        {
            quit = true;
        }

		presentScene();
        capFrameRate(&then, &remainder);
	}

    pushHighScore();
    clear();
}
