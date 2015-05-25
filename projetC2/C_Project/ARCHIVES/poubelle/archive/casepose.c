#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <unistd.h>
#include "casepose.h"

void small_direction (SDL_Renderer *ren, int x, int y, int dd){
    SDL_Texture *texture = NULL;
    SDL_Surface *d = NULL;
    switch(dd){
        case(1):d = IMG_Load("IMG/d1.png");break;
        case(2):d = IMG_Load("IMG/d2.png");break;
        case(3):d = IMG_Load("IMG/d3.png");break;
        case(4):d = IMG_Load("IMG/d4.png");break;
        case(6):d = IMG_Load("IMG/d6.png");break;
        case(7):d = IMG_Load("IMG/d7.png");break;
        case(8):d = IMG_Load("IMG/d8.png");break;
        case(9):d = IMG_Load("IMG/d9.png");break;
    }
    texture = SDL_CreateTextureFromSurface(ren,d);
    SDL_FreeSurface(d);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

void case_tir (SDL_Renderer *ren, int x, int y, int dd){
    SDL_Texture *texture = NULL;
    SDL_Surface *d = NULL;
    switch(dd){
        case(1):d = IMG_Load("IMG/t1.png");break;
        case(2):d = IMG_Load("IMG/t2.png");break;
        case(3):d = IMG_Load("IMG/t3.png");break;
    }
    texture = SDL_CreateTextureFromSurface(ren,d);
    SDL_FreeSurface(d);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}