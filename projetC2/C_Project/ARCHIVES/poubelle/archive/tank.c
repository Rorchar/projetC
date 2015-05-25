#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <unistd.h>
#include "tank.h"

void mvt_tank(SDL_Surface *Tank_i, SDL_Renderer *ren, int x, int y ){
    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(ren, Tank_i);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}