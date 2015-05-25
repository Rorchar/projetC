#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <unistd.h>
#include "ennemie.h"

void tank_E(SDL_Surface *Tank_E, SDL_Renderer *ren, int x, int y ){
    SDL_Texture *texture_TE = NULL;
    texture_TE = SDL_CreateTextureFromSurface(ren, Tank_E);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture_TE, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture_TE, NULL, &dst);
    SDL_DestroyTexture(texture_TE);
}