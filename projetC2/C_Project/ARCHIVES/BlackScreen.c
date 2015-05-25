#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>


/* Les differentes sources
http://openclassrooms.com/courses/developpez-vos-applications-3d-avec-opengl-3-3/creer-une-fenetre-avec-la-sdl-2-0
https://deptinfo-ensip.univ-poitiers.fr/ENS/doku/doku.php/stu:progc:sdl
http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world/
https://wiki.libsdl.org/
*/


int main (int argc, char** argv){

	SDL_Window *window ;
	SDL_Surface *screen;
	/*SDL_Renderer *renderer ;  Pour parler plus clairement, le renderer est en fait l'espace où nous allons pouvoir dessiner, écrire... */


	/*Elément dela boucle de controle*/
	SDL_Event event;
	int kill = 0;
	SDL_Init(SDL_INIT_VIDEO);  /*Initialisation*/

	window = SDL_CreateWindow("TankRider", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface( window );
	SDL_BlitSurface( screen, NULL, screen, NULL ); /*à commenter*/
    SDL_UpdateWindowSurface( window ); /*à commenter*/

	/*renderer = SDL_CreateRenderer (window, -1,SDL_RENDERER_ACCELERATED);*/

	while( kill == 0 ) {
		while( SDL_PollEvent( &event ) != 0 ) {
			if( event.type == SDL_QUIT ) {
				kill = 1;
			}
		}
	}

  SDL_DestroyWindow( window );
  SDL_Quit();
	return 0;
}