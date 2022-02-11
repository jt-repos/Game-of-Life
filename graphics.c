#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "graphics.h"
#include "sdlVariables.h"
#include "logic.h"

// initialise the game data
void init(void)
{
    SetupLogic();
    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());

    atexit(SDL_Quit); // set for clean-up on exit

    SDL_CreateWindowAndRenderer(SCRWIDTH, SCRHEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "The Game of Life");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    fullSurface = SDL_LoadBMP("images/full.bmp");
    emptySurface = SDL_LoadBMP("images/empty.bmp");
    white_surface = SDL_LoadBMP("images/info.bmp");

    fullTexture = SDL_CreateTextureFromSurface(renderer, fullSurface);
    emptyTexture = SDL_CreateTextureFromSurface(renderer, emptySurface);
    white_texture = SDL_CreateTextureFromSurface(renderer, white_surface);
}

// read keyboard input
void input(void)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();
    if (state[SDL_SCANCODE_LEFT])
    {
        IncrementCurrentEvo(-1);
    }
    else if (state[SDL_SCANCODE_RIGHT])
    {
        IncrementCurrentEvo(1);
    }
    else if (state[SDL_SCANCODE_ESCAPE])
    {
        exit(0);
    }
    return;
}

//change evolution that is currently displayed
int IncrementCurrentEvo(int value)
{
    int numOfEvos = GetNumOfEvos();
	if(currentEvo + value < 0 || currentEvo + value > numOfEvos)
	{
		return 1;
	}
	currentEvo += value;
	return 0;
}

//update game state and render it
bool update(void)
{
    while(true)
    {
        render();           // render new state
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }
        }
        return true;
    }
    return false;
}

//set up position of each grid cell and render it 
void render(void)
{
    int iSize = GetISize();
    int jSize = GetJSize();
    //printf("{%d}{%d}", iSize, jSize);
    int numberOfTiles = iSize > jSize ? iSize : jSize;
    int tileRect = GRIDSIZE / numberOfTiles;
    int xOffset = (SCRWIDTH - (jSize*tileRect)) / 2;
    int yOffset = TILESIZE;
    DrawTile(white_texture, 32, 512, (SCRWIDTH - 512) / 2, SCRHEIGHT - yOffset);     // draw new location
    for(int i = 1; i <= iSize; i++)
    {
        int* ptrRow = GetGrid(currentEvo, i);
        for(int j = 1; j <= jSize; j++)
        {
            SDL_Texture *texture = ptrRow[j] == 0 ? emptyTexture : fullTexture;
            int x = xOffset + (j-1) * tileRect;
            int y = yOffset + (i-1) * tileRect;
            DrawTile(texture, tileRect, tileRect, x, y);     // draw new location
        }
    }
    SDL_RenderPresent(renderer);
    return;
}

// draw tiles
void DrawTile(SDL_Texture *texture, int h, int w, int x, int y)
{
    SDL_Rect rect;
    rect.h = h;
    rect.w = w;
    rect.x = x;
    rect.y = y;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    return;
}
