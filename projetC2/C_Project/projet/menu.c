#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdbool.h>
#include <unistd.h>
#include "menu.h"

void Menu(SDL_Renderer* ren){
    SDL_Texture *texture = NULL;
    SDL_Surface *menu = IMG_Load("IMG/m00.png");
    texture = SDL_CreateTextureFromSurface(ren,menu);
    SDL_FreeSurface(menu);
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

void levels(SDL_Renderer* ren){
    SDL_Texture *texture = NULL;
    SDL_Surface *menu = IMG_Load("IMG/m1.png");
    texture = SDL_CreateTextureFromSurface(ren,menu);
    SDL_FreeSurface(menu);
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}


//if level==9 lancer
void credits(SDL_Renderer* ren){
    SDL_Texture *texture = NULL;
    SDL_Surface *menu = IMG_Load("IMG/m2.png");
    texture = SDL_CreateTextureFromSurface(ren,menu);
    SDL_FreeSurface(menu);
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

int lecture_niv(int mx, int my){
    if(mx>180 && mx<320){
            if(270 <my && my<320){
                return 1;
            }
            if(350 <my && my<400){
                return 2;
            }
            if(430 <my && my<480){
                return 3;
            }
            if(520 <my && my<570){
                return 4;
            }
    }else if(mx>495 && mx<645){
            if(270 <my && my<320){
                return 5;
            }
            if(350 <my && my<400){
                return 6;
            }
            if(430 <my && my<480){
                return 7;
            }
            if(520 <my && my<570){
                return 8;
            }
    }
    return 0;
}

void maj_titre(SDL_Window* window, int level){
    switch(level){
        case(0):SDL_SetWindowTitle(window,"TankRider: Menu");break;
        case(1):SDL_SetWindowTitle(window,"TankRider: Niveau 01");break;
        case(2):SDL_SetWindowTitle(window,"TankRider: Niveau 02");break;
        case(3):SDL_SetWindowTitle(window,"TankRider: Niveau 03");break;
        case(4):SDL_SetWindowTitle(window,"TankRider: Niveau 04");break;
        case(5):SDL_SetWindowTitle(window,"TankRider: Niveau 05");break;
        case(6):SDL_SetWindowTitle(window,"TankRider: Niveau 06");break;
        case(7):SDL_SetWindowTitle(window,"TankRider: Niveau 07");break;
        case(8):SDL_SetWindowTitle(window,"TankRider: Niveau 08");break;
        case(9):SDL_SetWindowTitle(window,"TankRider: Crédits");break;
        default: SDL_SetWindowTitle(window,"TankRider");
    }
}