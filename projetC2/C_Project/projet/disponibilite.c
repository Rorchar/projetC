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
    SDL_Surface *tt2 = IMG_Load("IMG/missile.png");
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
}
int dispo(int lvl,int u){
    int nb_fleche01[12]={0,2,0,1,0,1,0,0,0,0,0,0};
    int nb_fleche02[12]={0,0,0,0,0,1,0,1,0,0,0,1};
    int nb_fleche03[12]={0,0,0,0,0,0,0,1,1,1,0,0};
    int nb_fleche04[12]={0,0,1,1,0,1,0,0,0,0,2,0};
    int nb_fleche05[12]={0,1,0,0,0,0,0,1,1,0,1,0};
    int nb_fleche06[12]={1,1,0,1,0,0,0,0,0,1,0,1};
    int nb_fleche07[12]={1,0,0,1,0,0,0,1,0,0,1,0};
    int nb_fleche08[12]={0,0,1,0,0,1,0,0,1,2,0,0};
    int b=0;
    switch(lvl){
        case (1):b=nb_fleche01[u];break;
        case (2):b=nb_fleche02[u];break;
        case (3):b=nb_fleche03[u];break;
        case (4):b=nb_fleche04[u];break;
        case (5):b=nb_fleche05[u];break;
        case (6):b=nb_fleche06[u];break;
        case (7):b=nb_fleche07[u];break;
        case (8):b=nb_fleche08[u];break;
    }
    return b;
}
int dispofleche(int lvl,int u,int i){
    int b=0;
    int d_on_tab01[10]={0,0,0,0,0,0,0,0,0,0};
    int xcible01[10]={0,0,0,0,0,0,0,0,0,0};
    int ycible01[10]={0,0,0,0,0,0,0,0,0,0};
    int d_on_tab02[10]={2,0,0,0,0,0,0,0,0,0};
    int xcible02[10]={535,0,0,0,0,0,0,0,0,0};
    int ycible02[10]={135,0,0,0,0,0,0,0,0,0};
    int d_on_tab03[10]={6,2,4,0,0,0,0,0,0,0};
    int xcible03[10]={335,585,585,0,0,0,0,0,0,0};
    int ycible03[10]={235,235,435,0,0,0,0,0,0,0};
    int d_on_tab04[10]={2,0,0,0,0,0,0,0,0,0};
    int xcible04[10]={535,0,0,0,0,0,0,0,0,0};
    int ycible04[10]={235,0,0,0,0,0,0,0,0,0};
    int d_on_tab05[10]={4,4,0,0,0,0,0,0,0,0};
    int xcible05[10]={635,535,0,0,0,0,0,0,0,0};
    int ycible05[10]={285,185,0,0,0,0,0,0,0,0};
    int d_on_tab06[10]={6,4,2,0,0,0,0,0,0,0};
    int xcible06[10]={135,435,485,0,0,0,0,0,0,0};
    int ycible06[10]={385,485,485,0,0,0,0,0,0,0};
    int d_on_tab07[10]={0,0,0,0,0,0,0,0,0,0};
    int xcible07[10]={0,0,0,0,0,0,0,0,0,0};
    int ycible07[10]={0,0,0,0,0,0,0,0,0,0};
    int d_on_tab08[10]={6,2,0,0,0,0,0,0,0,0};
    int xcible08[10]={85,585,0,0,0,0,0,0,0,0};
    int ycible08[10]={485,185,0,0,0,0,0,0,0,0};
    switch(lvl){
        case(1):if(i==0){
                    b=d_on_tab01[u];
                }else if(i==1){
                    b=xcible01[u];
                }else{
                    b=ycible01[u];
                }
            break;
        case(2):if(i==0){
                    b=d_on_tab02[u];
                }else if(i==1){
                    b=xcible02[u];
                }else{
                    b=ycible02[u];
                }
            break; 
        case(3):if(i==0){
                    b=d_on_tab03[u];
                }else if(i==1){
                    b=xcible03[u];
                }else{
                    b=ycible03[u];
                }
            break; 
        case(4):if(i==0){
                    b=d_on_tab04[u];
                }else if(i==1){
                    b=xcible04[u];
                }else{
                    b=ycible04[u];
                }
            break;
        case(5):if(i==0){
                    b=d_on_tab05[u];
                }else if(i==1){
                    b=xcible05[u];
                }else{
                    b=ycible05[u];
                }
            break;
        case(6):if(i==0){
                    b=d_on_tab06[u];
                }else if(i==1){
                    b=xcible06[u];
                }else{
                    b=ycible06[u];
                }
            break;
        case(7):if(i==0){
                    b=d_on_tab07[u];
                }else if(i==1){
                    b=xcible07[u];
                }else{
                    b=ycible07[u];
                }
            break;
        case(8):if(i==0){
                    b=d_on_tab08[u];
                }else if(i==1){
                    b=xcible08[u];
                }else{
                    b=ycible08[u];
                }
            break;    
    }
    return b;
}
int nbdispo(int lvl){
    int b=0;
    int nbbb[9]={0,0,1,3,1,2,3,0,2};
    b=nbbb[lvl];
    return b;
}
