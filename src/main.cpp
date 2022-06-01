#include "header.h"

#include "initSDL.h"      //init SDL2
#include "gameStack.h"    //run the whole game

int main(int argv, char* argc[])
{
    if(!init()) 
    {     //initialize everything
        std::cout << "can not initialize";
        
    } 
    else 
    {
        initStack();

        while(!gameStack.empty()) 
        {
            doStack();
        }
    }

    close();
    return 0;
}
















