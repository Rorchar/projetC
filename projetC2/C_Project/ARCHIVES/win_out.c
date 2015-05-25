#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


/* Les differentes sources
http://openclassrooms.com/courses/developpez-vos-applications-3d-avec-opengl-3-3/creer-une-fenetre-avec-la-sdl-2-0
https://deptinfo-ensip.univ-poitiers.fr/ENS/doku/doku.php/stu:progc:sdl
http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world/
https://wiki.libsdl.org/
http://lazyfoo.net/tutorials/SDL
*/
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

void background(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor( renderer, 0, 127, 255, 255 );/*Background*/
    SDL_RenderClear( renderer );
    SDL_Rect rect_Int;    rect_Int.x = 20;    rect_Int.y = 20;    rect_Int.w = 600;    rect_Int.h = 440; /*Positon de rect_Int*/
    SDL_SetRenderDrawColor( renderer, 167, 103, 38, 255 );/*Foreground*/
    SDL_RenderFillRect( renderer, &rect_Int );
    SDL_RenderPresent(renderer);
}

void you_win(SDL_Event event){

    SDL_Window *window2 ;
    SDL_Surface *screen2;
   
    window2= SDL_CreateWindow("YOU WIN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, SDL_WINDOW_SHOWN);
    screen2= SDL_GetWindowSurface( window2 );
    SDL_BlitSurface( screen2, NULL, screen2, NULL ); /*à commenter*/
    SDL_UpdateWindowSurface( window2 ); /*à commenter*/

    SDL_Delay(2000);

    SDL_FreeSurface(screen2);
    SDL_DestroyWindow(window2);
}

void is_Out(SDL_Event event){

    SDL_Window *window3 ;
    SDL_Surface *screen3;
   
    window3= SDL_CreateWindow("YOU LOSE : YOU'RE OUT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, SDL_WINDOW_SHOWN);
    screen3= SDL_GetWindowSurface( window3 );
    SDL_BlitSurface( screen3, NULL, screen3, NULL ); /*à commenter*/
    SDL_UpdateWindowSurface( window3 ); /*à commenter*/

    SDL_Delay(2000);
    

    SDL_FreeSurface(screen3);
    SDL_DestroyWindow(window3);
}

/*void super_move(SDL_Renderer* renderer, SDL_Rect rect_T, int tx, int ty , int a, int b, int c){
  SDL_SetRenderDrawColor( renderer, a, b, c, 255 );
    SDL_Rect rect_T;    rect_T.x = tx;    rect_T.y = ty;    rect_T.w = 10;    rect_T.h = 10; 
    SDL_RenderFillRect( renderer, &rect_T );
    SDL_RenderPresent(renderer);
}
*/


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
            
            if (x==200 && y==200){
                you_win(event);
            }

            if (x<20 ){
                is_Out(event);
                /*A completer*/
            }
            if ( y<20 ){
                is_Out(event);
                /*A completer*/
            }
            if ( x>610 ){
                is_Out(event);
                /*A completer*/
            }
            if ( y> 450){
                is_Out(event);
                /*A completer*/
            }
            break ;
        }
    }
}

int main (int argc, char** argv){

	initialisation();

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

	window = SDL_CreateWindow("TankRider", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    renderer =  SDL_CreateRenderer( window, 0, SDL_RENDERER_ACCELERATED); /* 0 ou -1 ? */
    
    background(renderer);
    target(renderer,200,200);

    event_management (50,50,renderer); 
    SDL_RenderPresent(renderer);
    SDL_RenderPresent(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

/*
Separer les  event quit/keydown
Gerer les frontiere
Utiliser des variables globales pour les rect_T
Generer le quadrillage

FAIRE L'INTERFACE GRAPHIQUE DU JEU
*/
