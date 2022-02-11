#ifndef SDL_VARIABLES_GUARD__H
#define SDL_VARIABLES_GUARD__H

#include <stdio.h>

#define TILESIZE 32
#define GRIDSIZE 600
#define SCRWIDTH 720
#define SCRHEIGHT 720

int currentEvo = 0;
int isRendering = 1;

SDL_Renderer* renderer = NULL;

SDL_Surface*  white_surface = NULL;
SDL_Surface*  fullSurface = NULL;
SDL_Surface*  emptySurface = NULL;

SDL_Texture*  white_texture = NULL;
SDL_Texture*  fullTexture = NULL;
SDL_Texture*  emptyTexture = NULL;

void DrawTile(SDL_Texture *texture, int h, int w, int x, int y);

#endif
