#include "../header/gameStack.h"

#include "../header/widget.h"
#include "../header/game.h"
#include "../header/highScore.h"
#include "../header/credit.h"

std::stack<int> gameStack;

void initStack() 
{
    gameStack.push(MENU);
}

void doStack() {
    if(gameStack.top() == MENU) 
    {
        menu();
    }

    if(gameStack.top() == GAME) 
    {
        gameStack.pop();
        game();
        if(!gameStack.empty()) 
        {
            highScore();
        }
    }

    if(gameStack.top() == CREDIT) 
    {
        gameStack.pop();
        credit();
    }

    if(gameStack.top() == HIGH_SCORE) 
    {
        gameStack.pop();
        highScore();
    }

    if(gameStack.top() == QUIT) 
    {
        while(!gameStack.empty()) 
        {
            gameStack.pop();
        }
    }
}