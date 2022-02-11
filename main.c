#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "graphics.h"

//calls the graphics module to initialise and then update every frame + check input
int  main (int argc, char* argv[])
{
	int delay = 200;
    init();   // setup the game data
    while(true) //loop
	{
        input();            // keyboard input
		update();
        SDL_Delay(delay); // time between frames (ms)
    }
    return 0;
}
