#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdbool.h>
#include <unistd.h>
#include "background.h"

void first_components_of_the_background (SDL_Renderer* ren){

    //coloration de toutes la fenetes en blanc
    SDL_SetRenderDrawColor( ren, 255, 255, 255, 0 );
    SDL_Rect rect_BaseBackground;    rect_BaseBackground.x = 0;    rect_BaseBackground.y = 0;    rect_BaseBackground.w = 900;    rect_BaseBackground.h = 720;
    SDL_RenderFillRect( ren, &rect_BaseBackground );

    SDL_SetRenderDrawColor( ren,0, 0, 0, 0 );
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
    dst_start.y = 530;
    SDL_QueryTexture(texture_start, NULL, NULL, &dst_start.w, &dst_start.h);
    SDL_RenderCopy(ren, texture_start, NULL, &dst_start);
    SDL_DestroyTexture(texture_start);

    //Placement du bouton reset
    SDL_Texture *texture_reset = NULL;
    SDL_Surface *reset = IMG_Load("IMG/reset.png");
    texture_reset = SDL_CreateTextureFromSurface(ren, reset);
    SDL_FreeSurface(reset);
    SDL_Rect dst_reset;
    dst_reset.x = 730;
    dst_reset.y = 600;
    SDL_QueryTexture(texture_reset, NULL, NULL, &dst_reset.w, &dst_reset.h);
    SDL_RenderCopy(ren, texture_reset, NULL, &dst_reset);
    SDL_DestroyTexture(texture_reset);

    SDL_RenderPresent(ren);
}
void carte(SDL_Renderer* ren, int map[][13],int Drapeau[]){

    SDL_Surface *d = NULL;

    int i,j;
    for(i=0;i<13;i++){
        for(j=0;j<13;j++){
            switch(map[j][i]){
                case(0):d = IMG_Load("IMG/mersamere.png");break;
                case(1):d = IMG_Load("IMG/terresamer.png");break;
                case(2):d = IMG_Load("IMG/bonshitsamere.png");break;
                case(3):d = IMG_Load("IMG/hm).png");break;
                case(4):d = IMG_Load("IMG/l4.png");break;
                case(5):d = IMG_Load("IMG/graviasse.png");break;
                case(6):d = IMG_Load("IMG/l6.png");break;
                case(7):d = IMG_Load("IMG/diago(5)(1).png");break;
                case(8):d = IMG_Load("IMG/l8.png");break;
                case(9):d = IMG_Load("IMG/herbe-mer_1).png");break;
                case(10):d = IMG_Load("IMG/l2.png");break;
                case(11):d = IMG_Load("IMG/l1(.png");break;
                case(12):d = IMG_Load("IMG/base_pont.png");break;
                case(13):d = IMG_Load("IMG/coin_mer-terre1(.png");break;
                case(14):d = IMG_Load("IMG/fleurblanche.png");break;
                case(15):d = IMG_Load("IMG/fleurbleue.png");break;
                case(16):d = IMG_Load("IMG/herbe-mer_1(.png");break;
                case(17):d = IMG_Load("IMG/beton_terre.png");break;
                case(18):d = IMG_Load("IMG/betonI.png");break;
                case(19):d = IMG_Load("IMG/beton_angle_droit_herbe.png");break;
                case(20):d = IMG_Load("IMG/beton_angle_droit_terresaracelachienne.png");break;
                case(21):d = IMG_Load("IMG/beton_angle_droit_herbe2.png");break;
                case(22):d = IMG_Load("IMG/beton_angle_droit2_terresaracelachienne.png");break;
                case(23):d = IMG_Load("IMG/beton_terre2.png");break;
                case(24):d = IMG_Load("IMG/beton_angle_droit_herbe2.png");break;
                case(25):d = IMG_Load("IMG/beton_angle_droit_herbe3.png");break;
                case(26):d = IMG_Load("IMG/beton_angle_droit_herbe4.png");break;
                case(27):d = IMG_Load("IMG/beton_angle_droit_herbe5.png");break;
                case(28):d = IMG_Load("IMG/diago(5)(1)).png");break;
                case(29):d = IMG_Load("IMG/l3)).png");break;
                case(30):d = IMG_Load("IMG/base_pont2.png");break;
                case(31):d = IMG_Load("IMG/d2.png");break;
                case(32):d = IMG_Load("IMG/diago(1)(1).png");break;
                case(33):d = IMG_Load("IMG/d6.png");break;
                case(34):d = IMG_Load("IMG/d4.png");break;
                case(35):d = IMG_Load("IMG/l3))).png");break;
                case(36):d = IMG_Load("IMG/coin_mer-terre1(.png");break;
                case(37):d = IMG_Load("IMG/herbe-mer_7(.png");break;
                case(38):d = IMG_Load("IMG/herbe-mer_1((.png");break;
                case(39):d = IMG_Load("IMG/diago(5)(1).png");break;
            }
            SDL_Texture *texture  = SDL_CreateTextureFromSurface(ren,d);
            SDL_FreeSurface(d);
            SDL_Rect dst;
            dst.x = 35+(50*i);
            dst.y = 35+(50*j);
            dst.h = 50;
            dst.w = 50;
            SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
            SDL_RenderCopy(ren, texture, NULL, &dst);
            SDL_DestroyTexture(texture);
        }
    }
    //Placement drapeau
    SDL_Texture *texture_drapeau = NULL;
    SDL_Surface *drapeau = IMG_Load("IMG/case_drapeau.png");
    texture_drapeau = SDL_CreateTextureFromSurface(ren,drapeau);
    SDL_FreeSurface(drapeau);
    SDL_Rect dst_drapeau;
    dst_drapeau.x = Drapeau[0];
    dst_drapeau.y = Drapeau[1];
    SDL_QueryTexture(texture_drapeau, NULL, NULL, &dst_drapeau.w, &dst_drapeau.h);
    SDL_RenderCopy(ren, texture_drapeau, NULL, &dst_drapeau);
    SDL_DestroyTexture(texture_drapeau);
}