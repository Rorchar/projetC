#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdbool.h>
#include <unistd.h>
#include "case.h"

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
int choix_direction(int mx, int my){
    if ( mx< 779 && mx> 731 && my>181 && my<229){
        return  1;
    }
    if ( mx< 829 && mx> 781 && my>181 && my<229){
        return  2;
    }
    if ( mx< 879 && mx> 831 && my>181 && my<229){
        return  3;
    }
    if ( mx< 779 && mx> 731 && my>131 && my<179){
        return  4;
    }
    if ( mx< 879 && mx> 831 && my>131 && my<179){
        return  6;
    }
    if ( mx< 779 && mx> 731 && my> 81 && my<189){
        return  7;
    }
    if ( mx< 829 && mx> 781 && my> 81 && my<189){
        return  8;
    }
    if ( mx< 879 && mx> 831 && my> 81 && my<189){
        return  9;
    }else{
        return  5;
    }
}
int choix_arme(int mx,int my){
    if ( mx<779 && mx>731 && my<349 && my>301){
        return 1; //button quadri shot
    }
    if ( mx<829 && mx>781 && my<349 && my>301){
        return 2; //button tir simple
    }
    if ( mx<879 && mx>831 && my<349 && my>301){
        return 3; //button bouclier
    }else{
        return 0;
    }
}

void case_tir (SDL_Renderer *ren, int x, int y, int dd){
    SDL_Texture *texture = NULL;
    SDL_Surface *d = NULL;
    switch(dd){
        case(1):d = IMG_Load("IMG/t1.png");break;
        case(2):d = IMG_Load("IMG/missile2.png");break;
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