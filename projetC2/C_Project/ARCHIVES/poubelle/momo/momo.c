#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Menu
void menu(SDL_Window *window ,SDL_Surface *screen, int ON1);
//Niveau 1
void show1(SDL_Window *window ,SDL_Renderer* renderer, int ON2 );
// composante du niveau 1
void background(SDL_Renderer* renderer);
void move_Tank(SDL_Renderer* renderer, int tx, int ty);
void destroy_Tank(SDL_Renderer* renderer, int tx, int ty);
void target(SDL_Renderer* renderer, int tx, int ty);
void event_management (int x, int y, SDL_Renderer* renderer );

int main (int argc, char** argv){

    SDL_Window *window = NULL ;
    SDL_Surface *screen = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);  
    IMG_Init(IMG_INIT_PNG);

    int ON1 = 1;

    menu(window ,screen,ON1);

    int ON2 = 1;

    show1(window , renderer, ON2 );
    
    IMG_Quit();
    SDL_FreeSurface(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}


void menu(SDL_Window *window ,SDL_Surface *screen, int ON1 ){

    SDL_Event event;

    window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface( window );

    SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,217,187,82));//Unique raison SDL_Surface *screen au niveau du
                                                                    //Couleur de l'ecran d'accueil
                                                                    //A paufiner
    SDL_UpdateWindowSurface( window ); //return an int 

    //Titre
    SDL_Surface  *titre = NULL;
    SDL_Rect pos_titre ;
    titre =  IMG_Load("IMG/Titre.png");
    pos_titre.x = 0;
    pos_titre.y = 30;
    SDL_BlitSurface ( titre, NULL, screen, &pos_titre);
    SDL_UpdateWindowSurface( window );    

    while( ON1 == 1 ) {
        SDL_Surface  *B1 = NULL;
        SDL_Rect pos_B1 ;
        pos_B1.x = 180;
        pos_B1.y = 340;
                
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                ON1 = 0;
            break;
            case SDL_MOUSEMOTION:
                if (event.motion.x >= 180 && event.motion.x <480 && event.motion.y >=340 && event.motion.y <400 ) {
                    B1 =  IMG_Load("IMG/CommencerRed.png");
                    SDL_BlitSurface ( B1, NULL, screen, &pos_B1);
                    SDL_UpdateWindowSurface( window ); 
                      case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT && event.motion.x >= 180 && event.motion.x <480 && event.motion.y >=340 && event.motion.y <400){ 
                        //Pourqui pas if (event.button.button == SDL_BUTTON_RIGHT seulement )//                            
                            IMG_Quit();
                            SDL_FreeSurface(screen);
                            SDL_DestroyWindow(window);
                            ON1 = 0;
                        }
                        break;
                }else{
                    B1 =  IMG_Load("IMG/CommencerBlue.png");
                    SDL_BlitSurface ( B1, NULL, screen, &pos_B1);
                    SDL_UpdateWindowSurface( window ); 
                }
            break;
        }
    }
}


void show1(SDL_Window *window , SDL_Renderer* renderer , int ON2 ){

    SDL_Event event;

    window = SDL_CreateWindow("TankRider", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    renderer =  SDL_CreateRenderer( window, 0, SDL_RENDERER_ACCELERATED); 
    background(renderer);

    target(renderer, 200 , 200);

    event_management (50, 50,  renderer); 
    SDL_RenderPresent(renderer);


    while( ON2 == 1 ) {
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                ON2 = 0;
            break;
        }
    }

}

void background(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor( renderer, 0, 127, 255, 255 );/*Background*/
    SDL_RenderClear( renderer );
    SDL_Rect rect_Int;    rect_Int.x = 20;    rect_Int.y = 20;    rect_Int.w = 600;    rect_Int.h = 440; /*Positon de rect_Int*/
    SDL_SetRenderDrawColor( renderer, 167, 103, 38, 255 );/*Foreground*/
    SDL_RenderFillRect( renderer, &rect_Int );
    SDL_RenderPresent(renderer);
}

void move_Tank(SDL_Renderer* renderer, int tx, int ty){
  SDL_SetRenderDrawColor( renderer, 27, 79, 8, 255 );
    SDL_Rect rect_T;    rect_T.x = tx;    rect_T.y = ty;    rect_T.w = 10;    rect_T.h = 10; /*Positon de rect_Int*/
    SDL_RenderFillRect( renderer, &rect_T );
    SDL_RenderPresent(renderer);
}

void destroy_Tank(SDL_Renderer* renderer, int tx, int ty){
  SDL_SetRenderDrawColor( renderer, 167, 103, 38, 255 );
    SDL_Rect rect_T;    rect_T.x = tx;    rect_T.y = ty;    rect_T.w = 10;    rect_T.h = 10; /*Positon de rect_Int*/
    SDL_RenderFillRect( renderer, &rect_T );
    SDL_RenderPresent(renderer);
}

void target(SDL_Renderer* renderer, int tx, int ty){
  SDL_SetRenderDrawColor( renderer, 255,0, 0,255 );
    SDL_Rect rect_T;    rect_T.x = tx;    rect_T.y = ty;    rect_T.w = 10;    rect_T.h = 10; /*Positon de rect_Int*/
    SDL_RenderFillRect( renderer, &rect_T );
    SDL_RenderPresent(renderer);
}

void initialisation(){
    SDL_Init(SDL_INIT_VIDEO);
    /*Ajouter la gestion de l'erreur */
}



void event_management (int x, int y, SDL_Renderer* renderer ){ /*Position initial */

    SDL_Event event;

    int kill = 0;
    while( kill == 0 ) {
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:kill= 1;break;
            case SDL_KEYDOWN :
                destroy_Tank(renderer, x,  y);
                if (event.key.keysym.scancode == SDL_SCANCODE_UP   ) {y = y - 10; move_Tank(renderer, x,  y);}
                if (event.key.keysym.scancode == SDL_SCANCODE_DOWN ) {y = y + 10; move_Tank(renderer, x,  y);}
                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {x = x + 10; move_Tank(renderer, x,  y);}
                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT ) {x = x - 10; move_Tank(renderer, x,  y);                }
            break ;
        }
    }

}

