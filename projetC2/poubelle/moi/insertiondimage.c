#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
	SDL_Window* window;
	SDL_Surface* screen=NULL,* image=NULL,*Zozor=NULL;
	SDL_Event event;
	int terminer=0;
	SDL_Rect positionZozor;
	

	SDL_Init(SDL_INIT_VIDEO);
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("erreur d'initialisation");
	}

	positionZozor.x = 500;
    positionZozor.y = 260; 
	window=SDL_CreateWindow("learn",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface( window );
	image = SDL_LoadBMP("lac_en_montagne.bmp");
	SDL_BlitSurface(image, NULL, screen, NULL ); 
    Zozor = SDL_LoadBMP("zozor.bmp");
    SDL_SetColorKey(Zozor, SDL_TRUE, SDL_MapRGB(Zozor->format, 0, 0, 255));
    SDL_BlitSurface(Zozor, NULL, screen, &positionZozor); 
    SDL_UpdateWindowSurface( window );

	while(terminer!=1){
		SDL_WaitEvent(&event);
		if(event.window.event==SDL_WINDOWEVENT_CLOSE)
			terminer=1;
		
	}
	SDL_FreeSurface(Zozor);
	SDL_FreeSurface( image );
	SDL_DestroyWindow(window);
	SDL_Quit(); 
    return 0;
}