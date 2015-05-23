#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdbool.h>
#include <unistd.h>
#include "tank.h"

void mvt_tank(SDL_Renderer *ren, int x, int y, int orientation, int i,int bouclier){
    int angles[] ={0,45,90,-45,0,135,-90,-135,180};
    SDL_Texture *texture = NULL;
    SDL_Surface *t = NULL;
    if(i==1 && bouclier==0){
        t = IMG_Load("IMG/tank1.png");
    }else if(i==1 && bouclier==1){
        t = IMG_Load("IMG/ennemie1.png");
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
int evite_mer(SDL_Window* win, int x, int y,int lvl){
    int j=0;
    int k=0;
    int map01[13][13] = {
                    {0,0,0,6,15,2,2,2,2,2,4,0,0},
                    {9,0,0,6,2,1,1,1,1,2,11,9,0},
                    {3,0,0,6,2,5,5,1,1,15,2,4,0},
                    {0,0,0,6,2,5,5,5,1,15,2,4,0},
                    {0,0,0,6,2,2,5,5,1,2,2,4,0},
                    {0,0,0,6,14,14,1,1,2,2,7,3,0},
                    {9,0,0,6,2,2,1,1,2,2,4,0,0},
                    {4,0,0,6,2,2,2,15,2,7,3,0,0},
                    {3,0,0,13,8,8,8,12,8,3,0,0,0},
                    {0,0,0,0,0,0,0,12,0,0,0,0,0},
                    {0,0,0,16,10,10,10,12,9,0,0,0,0},
                    {0,0,0,6,2,14,2,2,11,10,9,0,0},
                    {0,0,0,6,2,5,1,1,5,2,4,0,0},
                };
    int map02[13][13] = {
                        {2,  2,  2,  2,  2,  2,  5,  4,  0,  6,  2,  2,  2},
                        {14, 14, 2,  2,  15, 15, 5,  4,  0,  6,  2,  15, 15},
                        {2,  14, 2,  15, 2,  2,  5,  30, 30, 30, 31, 2,  15},
                        {15, 2,  2,  2,  2,  2,  2,  4,  0,  6,  2,  2,  2},
                        {2,  15, 7,  8,  8,  12, 8,  3,  0,  6,  2,  2,  2},
                        {5,  5,  4,  0,  0,  12, 0,  0,  0,  6,  2,  2,  2},
                        {1,  7,  3,  0,  0,  12, 10, 10, 10, 28, 2,  24, 17},
                        {8,  3,  0,  0,  16, 12, 2,  15, 2,  2,  2,  23, 14},
                        {0,  0,  16, 10, 28, 2,  2,  24, 17, 27, 2,  23, 2},
                        {0,  16, 28, 2,  2,  2,  2,  23, 2,  23, 2,  23, 2},
                        {0,  6,  2,  2,  14, 14, 2,  23, 15, 23, 2,  23, 2},
                        {0,  6,  2,  2,  2,  14, 2,  23, 2,  23, 2,  23, 2},
                        {0,  6,  2,  15, 2,  2,  2,  23, 2,  19, 17, 26, 2},
                    };
    int map03[13][13]={
                        {0,  0,  0,  0,  6,  2,  14, 5,  5,  5,  5,  2, 2},
                        {0,  0,  0,  0,  6,  15, 2,  14, 1,  1,  1,  1, 15},
                        {0,  0,  0,  0,  6,  2,  2,  15, 2,  2,  2,  2, 15},
                        {0,  16, 10, 10, 28, 2,  2,  2,  2,  2,  2,  2, 2},
                        {0,  6,  2,  2,  2,  2,  33,  2,  2,  2,  2,  31, 2},
                        {10, 29, 2,  2,  2,  2,  2,  2,  2,  2,  2,  1, 5},
                        {2,  2,  2,  2,  2,  24,  17, 14, 17, 17,  17,  1, 5},
                        {1,  5,  1,  14, 2,  23,  2,  15, 2,  2,  2,  1, 5},
                        {1,  5,  1,  15, 2,  23,  2,  2,  14, 2,  2,  34, 2},
                        {2,  2,  2,  15, 2,  23,  2,  2,  2,  2,  2,  2, 2},
                        {8,  32, 2,  2,  14, 25, 17, 17, 17, 17, 17, 2, 2},
                        {0,  13, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 8},
                        {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0},
                    };
    int mx = (x-20)/50; //Pour map ou matrice
    int my = (y-20)/50;
    int map[13][13];
    switch (lvl){
        case (1):for(j=0;j<13;j++){
                    for(k=0;k<13;k++){
                        map[j][k]=map01[j][k];
                    }
                };break;
        case (2):for(j=0;j<13;j++){
                    for(k=0;k<13;k++){
                        map[j][k]=map02[j][k];
                    }
                };break;
        case (3):for(j=0;j<13;j++){
                    for(k=0;k<13;k++){
                        map[j][k]=map03[j][k];
                    }
                };break;
    }
    if(map[my][mx]==0||(map[my][mx]>=17 && map[my][mx]<=27)){
        SDL_ShowSimpleMessageBox(0, "Oooops", "Pas possible d'avancer d'avantage ", win);
        return 0;
    }else{
        return 1;
    }
}

int Pos(int i,int a){
    int b=0;
    int Pos1[3]={320,20,2};
    int Pos2[3]={170,570,6};
    int Pos3[3]={170,520,6};
    switch(i){
        case(1):b=Pos1[a];break;
        case(2):b=Pos2[a];break;
        case(3):b=Pos3[a];break;
    }
    return b;
}
int PosE(int i,int a){
    int b=0;
    int PosE1[6]={220,170,6,2000,2000,1};
    int PosE2[6]={420,470,6,620,370,4};
    int PosE3[6]={370,470,6,620,220,4};
    switch(i){
        case(1):b=PosE1[a];break;
        case(2):b=PosE2[a];break;
        case(3):b=PosE3[a];break;
    }
    return b;
}