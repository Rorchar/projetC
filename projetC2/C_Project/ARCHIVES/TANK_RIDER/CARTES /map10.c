#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



void affiche(SDL_Renderer* ren){
    
    int table[13][13] = {
                        {2,  2,  2,  2,  2,  2,  14, 14, 2,  4,  0,  0,  0},
                        {2,  2,  15, 15, 2,  15, 2,  14, 2,  11, 10, 9,  0},
                        {5,  1,  1,  2,  15, 2,  2,  15, 2,  2,  2,  11, 10},
                        {5,  1,  1, 17, 17, 17, 17, 17, 17,  2,  2,  2,  15},
                        {5,  1,  1,  2,  2,  7,  8,  8, 35,  2,  31,  2,  2},
                        {2,  2,  2,  2,  7,  3,  0,  0,  6,  2,  2,  5,  5},
                        {2,  2,  2,  7,  3,  0,  16,10, 28,  2,  5,  1,  5},
                        {2,  15,  7,  3, 0,  16, 28, 2,  2,  2,  2,  1,  5},
                        {8,  8,  3,  0,  16, 28, 2,  2,  14, 2,  2,  24, 17},
                        {0,  0,  0,  16, 28, 2,  2,  2,  2,  2,  2,  23, 2},
                        {0,  0,  16, 28, 14, 2,  2,  2,  2,  2,  2,  23, 2},
                        {0,  16, 28, 2,  2,  2,  2,  21, 17, 27, 2,  23, 2},
                        {0,  6,  2,  2,  2,  2,  2,  23, 2,  23, 2,  23, 2},
                    };


    SDL_Surface *d = NULL;

    int i,j;
    for(i=0;i<13;i++){
        for(j=0;j<13;j++){
            switch(table[j][i]){
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

            }


            SDL_Texture *texture  = SDL_CreateTextureFromSurface(ren,d);
            
            SDL_Rect dst;
            dst.x = 35+(50*i);
            dst.y = 35+(50*j);
            dst.h = 50;
            dst.w = 50;
            SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
            SDL_RenderCopy(ren, texture, NULL, &dst);
        }
    }
}



int main(){

    SDL_Window* window = NULL;
    SDL_Renderer* ren = NULL;
   
    SDL_Event event;
    int ON = 1;

    //Initialisation
    //Ajouter la gestion de l'erreur
    SDL_Init(SDL_INIT_VIDEO);  
    IMG_Init(IMG_INIT_PNG);

    //Génération de la fenêtre  
    window = SDL_CreateWindow("TankRider : Level 00", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 720, SDL_WINDOW_SHOWN);
    ren =  SDL_CreateRenderer( window, 0, SDL_RENDERER_TARGETTEXTURE);
    



   affiche(ren);


   SDL_RenderPresent(ren);

    while( ON == 1 ) {
        SDL_WaitEvent(&event);
        switch( event.type){
            //Gestion de la fermeture
            case SDL_QUIT :
                ON = 0;
            break;
        }
    }


    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

