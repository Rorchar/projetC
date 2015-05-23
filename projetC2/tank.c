#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdbool.h>
#include <unistd.h>
#include "tank.h"

void mvt_tank(SDL_Renderer *ren, int x, int y, int orientation, int i){
    int angles[] ={0,45,90,-45,0,135,-90,-135,180};
    SDL_Texture *texture = NULL;
    SDL_Surface *t = NULL;
    if(i==1){
        t = IMG_Load("IMG/tank1.png");
    }else{
        t = IMG_Load("IMG/ennemie1.png");
    }
    SDL_Surface *Tank = rotozoomSurface(t,angles[orientation-1], 1, 1);
    texture = SDL_CreateTextureFromSurface(ren, Tank);
    SDL_FreeSurface(t);
    SDL_FreeSurface(Tank);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}
int evite_mer(SDL_Window* win, int x, int y,int map[][13]){
    int mx = (x-20)/50; //Pour map ou matrice
    int my = (y-20)/50;
    if(map[my][mx]==0||map[my][mx]==8 || map[my][mx]==9||map[my][mx]==4 || map[my][mx]==3){
        SDL_ShowSimpleMessageBox(0, "Oooops", "Pas possible d'avancer d'avantage ", win);
        return 0;
    }else{
        return 1;
    }
}
void fire(SDL_Renderer *ren,SDL_Surface *Missile,int xmissile,int ymissile){
    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(ren, Missile);
    SDL_Rect dst;
    dst.x = xmissile;
    dst.y = ymissile;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}
int Pos(int i,int a){
    int b=0;
    int Pos1[3]={320,20,2};
    int Pos2[3]={170,570,6};
    switch(i){
        case(1):b=Pos1[a];break;
        case(2):b=Pos2[a];break;
    }
    return b;
}
int PosE(int i,int a){
    int b=0;
    int PosE1[8]={220,170,6,0,2000,2000,1,0};
    int PosE2[8]={420,470,6,0,620,370,4,0};
    switch(i){
        case(1):b=PosE1[a];break;
        case(2):b=PosE2[a];break;
    }
    return b;
}