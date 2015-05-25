#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <unistd.h>
#include "background.h"
#include "casepose.h"
#include "ennemie.h"
#include "tank.h"


void fond_carte(SDL_Renderer* ren,SDL_Surface* Tank_E,SDL_Surface *Tank,int xdrapeau,int ydrapeau,int nbE,int nb,int na,int *StatutE,SDL_Surface *TankE[],SDL_Surface *Tanks[],int x,int y,int set,int *setE,int *xcible,int *ycible,int *xtarget,int *ytarget,int *xTankE,int *yTankE,int *d_on_tab,int *arm_on_tab,int *nbb,int bouclier,SDL_Surface *TanksBouclier[]){
    SDL_Texture *texture_map1 = NULL;
    SDL_Surface *map1= IMG_Load("IMG/map1.png");
    texture_map1 = SDL_CreateTextureFromSurface(ren,map1);
    SDL_FreeSurface(map1);
    SDL_Rect lv1;
    lv1.x = 35;
    lv1.y = 35;
    SDL_QueryTexture(texture_map1, NULL, NULL, &lv1.w, &lv1.h);
    SDL_RenderCopy(ren, texture_map1, NULL, &lv1);
    SDL_DestroyTexture(texture_map1);

    //Placement drapeau
    SDL_Texture *texture_drapeau = NULL;
    SDL_Surface *Drapeau = IMG_Load("IMG/case_drapeau.png");
    texture_drapeau = SDL_CreateTextureFromSurface(ren,Drapeau);
    SDL_FreeSurface(Drapeau);
    SDL_Rect dst_drapeau;
    dst_drapeau.x = xdrapeau;
    dst_drapeau.y = ydrapeau;
    SDL_QueryTexture(texture_drapeau, NULL, NULL, &dst_drapeau.w, &dst_drapeau.h);
    SDL_RenderCopy(ren, texture_drapeau, NULL, &dst_drapeau);
    SDL_DestroyTexture(texture_drapeau);

    int nbj=0;
    for(nbj = 0; nbj<nb;nbj++){
        if(nb!=0){
            small_direction (ren,xcible[nbj],ycible[nbj],d_on_tab[nbj]);
        }
    }
    int naj=0;
    for(naj = 0; naj<na;naj++){
        if(na!=0){
            case_tir(ren,xtarget[naj],ytarget[naj],arm_on_tab[naj]);
        }
    }

    if(bouclier==0 || &nbb==50){
        Tank = Tanks[set-1];
        &nbb=0;
        bouclier=0;
    }else{
        Tank = TanksBouclier[set-1];
        &nbb=&nbb+1;
    }
    //Affichage du Premier tank
    mvt_tank(Tank,ren,x,y);

    int o=0;
    for (o=0;o<nbE;o++){
        if(StatutE[o]==0){
            Tank_E=TankE[setE[o]-1];
            tank_E(Tank_E,ren,xTankE[o],yTankE[o]);
        }
    }
    SDL_RenderPresent(ren);
}
void first_components_of_the_background (SDL_Renderer* ren){
    //coloration de toutes la fenetes en blanc
    SDL_SetRenderDrawColor( ren, 255, 255, 255, 0 );
    SDL_Rect rect_BaseBackground;    rect_BaseBackground.x = 0;    rect_BaseBackground.y = 0;    rect_BaseBackground.w = 900;    rect_BaseBackground.h = 720;
    SDL_RenderFillRect( ren, &rect_BaseBackground );
    

    SDL_SetRenderDrawColor( ren, 0, 0, 0, 0 );
    SDL_Rect rect_G;    rect_G.x = 10;    rect_G.y = 10;    rect_G.w = 700;    rect_G.h = 700;
    SDL_RenderFillRect( ren, &rect_G );
    

    SDL_SetRenderDrawColor( ren, 213, 196, 128, 0);
    SDL_Rect rect_D;    rect_D.x = 720;    rect_D.y = 10;    rect_D.w = 170;    rect_D.h = 700;
    SDL_RenderFillRect( ren, &rect_D );

    //Placement du bouton start
    SDL_Texture *texture_start = NULL;
    SDL_Surface *start = IMG_Load("IMG/start.png");
    texture_start = SDL_CreateTextureFromSurface(ren, start);
    SDL_FreeSurface(start);
    SDL_Rect dst_start;
    dst_start.x = 730;
    dst_start.y = 600;
    SDL_QueryTexture(texture_start, NULL, NULL, &dst_start.w, &dst_start.h);
    SDL_RenderCopy(ren, texture_start, NULL, &dst_start);
    SDL_DestroyTexture(texture_start);

    //Placement du direction_pannel
    //En changeant les coordonnées(730,80), il faut updater ##choix_direction
    SDL_Texture *texture_directions = NULL;
    SDL_Surface *Directions = IMG_Load("IMG/Directions.png");
    texture_directions = SDL_CreateTextureFromSurface(ren,Directions);
    SDL_FreeSurface(Directions);
    SDL_Rect dst_directions;
    dst_directions.x = 730;
    dst_directions.y = 80;
    SDL_QueryTexture(texture_directions, NULL, NULL, &dst_directions.w, &dst_directions.h);
    SDL_RenderCopy(ren, texture_directions, NULL, &dst_directions);
    SDL_DestroyTexture(texture_directions);

    //Placement des cases tirs
    SDL_Texture *texture_tir1 = NULL;
    SDL_Surface *Tir1 = IMG_Load("IMG/t1f.png");
    texture_tir1 = SDL_CreateTextureFromSurface(ren,Tir1);
    SDL_FreeSurface(Tir1);
    SDL_Rect shot1;
    shot1.x = 730;
    shot1.y = 300;
    SDL_QueryTexture(texture_tir1, NULL, NULL, &shot1.w, &shot1.h);
    SDL_RenderCopy(ren, texture_tir1, NULL, &shot1);
    SDL_DestroyTexture(texture_tir1);

    SDL_Texture *texture_tir2 = NULL;
    SDL_Surface *Tir2 = IMG_Load("IMG/t2f.png");
    texture_tir2 = SDL_CreateTextureFromSurface(ren,Tir2);
    SDL_FreeSurface(Tir2);
    SDL_Rect shot2;
    shot2.x = 780;
    shot2.y = 300;
    SDL_QueryTexture(texture_tir2, NULL, NULL, &shot2.w, &shot2.h);
    SDL_RenderCopy(ren, texture_tir2, NULL, &shot2);
    SDL_DestroyTexture(texture_tir2);

    SDL_Texture *texture_tir3 = NULL;
    SDL_Surface *Tir3 = IMG_Load("IMG/t3f.png");
    texture_tir3 = SDL_CreateTextureFromSurface(ren,Tir3);
    SDL_FreeSurface(Tir3);
    SDL_Rect shot3;
    shot3.x = 830;
    shot3.y = 300;
    SDL_QueryTexture(texture_tir3, NULL, NULL, &shot3.w, &shot3.h);
    SDL_RenderCopy(ren, texture_tir3, NULL, &shot3);
    SDL_DestroyTexture(texture_tir3);
    SDL_RenderPresent(ren);
}