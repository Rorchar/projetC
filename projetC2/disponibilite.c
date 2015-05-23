#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdbool.h>
#include <unistd.h>
#include "disponibilite.h"

void affichage_nb(SDL_Renderer *ren, int x, int y, int i){
    SDL_Color textColor = {0,0,0,0};
    TTF_Font *font = TTF_OpenFont( "TTF/Amelia_BT.ttf", 18 );
    char s[3]; // Nombre maximal de chiffres + 1
    sprintf(s,"%d", i);
    SDL_Surface *message = TTF_RenderText_Solid( font,s, textColor );
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, message);
    SDL_FreeSurface(message);
    SDL_Rect text;
    text.x = x;
    text.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &text.w, &text.h);
    SDL_RenderCopy(ren, texture, NULL, &text);
    SDL_DestroyTexture(texture);
}
void maj_panneau(SDL_Renderer* ren, int nb_fleche[]){

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

    SDL_Texture *texture_t1f = NULL;
    SDL_Surface *tt1 = IMG_Load("IMG/t1f.png");
    texture_t1f = SDL_CreateTextureFromSurface(ren, tt1);
    SDL_FreeSurface(tt1);
    SDL_Rect dst_t1f;
    dst_t1f.x = 730;
    dst_t1f.y = 280;
    SDL_QueryTexture(texture_t1f, NULL, NULL, &dst_t1f.w, &dst_t1f.h);
    SDL_RenderCopy(ren, texture_t1f, NULL, &dst_t1f);
    SDL_DestroyTexture(texture_t1f);

    SDL_Texture *texture_t2f = NULL;
    SDL_Surface *tt2 = IMG_Load("IMG/t2f.png");
    texture_t2f = SDL_CreateTextureFromSurface(ren, tt2);
    SDL_FreeSurface(tt2);
    SDL_Rect dst_t2f;
    dst_t2f.x = 780;
    dst_t2f.y = 280;
    SDL_QueryTexture(texture_t2f, NULL, NULL, &dst_t2f.w, &dst_t2f.h);
    SDL_RenderCopy(ren, texture_t2f, NULL, &dst_t2f);
    SDL_DestroyTexture(texture_t2f);

    SDL_Texture *texture_t3f = NULL;
    SDL_Surface *tt3 = IMG_Load("IMG/t3f.png");
    texture_t3f = SDL_CreateTextureFromSurface(ren, tt3);
    SDL_FreeSurface(tt3);
    SDL_Rect dst_t3f;
    dst_t3f.x = 830;
    dst_t3f.y = 280;
    SDL_QueryTexture(texture_t3f, NULL, NULL, &dst_t3f.w, &dst_t3f.h);
    SDL_RenderCopy(ren, texture_t3f, NULL, &dst_t3f);
    SDL_DestroyTexture(texture_t3f);

    affichage_nb(ren,768,210,nb_fleche[0]);//d1
    affichage_nb(ren,818,210,nb_fleche[1]);//d2
    affichage_nb(ren,868,210,nb_fleche[2]);//d3
    affichage_nb(ren,768,160,nb_fleche[3]);//d4
    affichage_nb(ren,868,160,nb_fleche[5]);//d6
    affichage_nb(ren,768,110,nb_fleche[6]);//d7
    affichage_nb(ren,818,110,nb_fleche[7]);//d8
    affichage_nb(ren,868,110,nb_fleche[8]);//d9

    affichage_nb(ren,768,310,nb_fleche[9]);//d1
    affichage_nb(ren,818,310,nb_fleche[10]);//d2
    affichage_nb(ren,868,310,nb_fleche[11]);//d3
    
    SDL_RenderPresent(ren);
}
