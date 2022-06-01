#include "gameStack.h"

#include "widget.h"
#include "game.h"
#include "highScore.h"
#include "credit.h"

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
        if(!gameStack.empty() && gameStack.top() != QUIT) 
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