#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Menu(SDL_Renderer* ren){
    SDL_Texture *texture = NULL;
    SDL_Surface *menu = IMG_Load("IMG/m00.png");
    texture = SDL_CreateTextureFromSurface(ren,menu);
    SDL_FreeSurface(menu);
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(ren);
}

void levels(SDL_Renderer* ren){
    SDL_Texture *texture = NULL;
    SDL_Surface *menu = IMG_Load("IMG/m1.png");
    texture = SDL_CreateTextureFromSurface(ren,menu);
    SDL_FreeSurface(menu);
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(ren);
}


//if level==9 lancer
void credits(SDL_Renderer* ren){
    SDL_Texture *texture = NULL;
    SDL_Surface *menu = IMG_Load("IMG/m2.png");
    texture = SDL_CreateTextureFromSurface(ren,menu);
    SDL_FreeSurface(menu);
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(ren);
}

int lecture_niv(int mx, int my){
	if(mx>180 && mx<320){
			if(270 <my && my<320){
				return 1;
			}
			if(350 <my && my<400){
				return 2;
			}
			if(430 <my && my<480){
				return 3;
			}
			if(520 <my && my<570){
				return 4;
			}
	}else if(mx>495 && mx<645){
			if(270 <my && my<320){
				return 5;
			}
			if(350 <my && my<400){
				return 6;
			}
			if(430 <my && my<480){
				return 7;
			}
			if(520 <my && my<570){
				return 8;
			}
	}
	return 0;
}

void maj_titre(SDL_Window* window, int level){
	switch(level){
		case(0):SDL_SetWindowTitle(window,"TankRider: Menu");break;
		case(1):SDL_SetWindowTitle(window,"TankRider: Niveau 01");break;
		case(2):SDL_SetWindowTitle(window,"TankRider: Niveau 02");break;
		case(3):SDL_SetWindowTitle(window,"TankRider: Niveau 03");break;
		case(4):SDL_SetWindowTitle(window,"TankRider: Niveau 04");break;
		case(5):SDL_SetWindowTitle(window,"TankRider: Niveau 05");break;
		case(6):SDL_SetWindowTitle(window,"TankRider: Niveau 06");break;
		case(7):SDL_SetWindowTitle(window,"TankRider: Niveau 07");break;
		case(8):SDL_SetWindowTitle(window,"TankRider: Niveau 08");break;
		case(9):SDL_SetWindowTitle(window,"TankRider: Crédits");break;
		default: SDL_SetWindowTitle(window,"TankRider");
	}
}


int main(int argc, char const *argv[]){
	
    SDL_Init(SDL_INIT_VIDEO); 
    IMG_Init(IMG_INIT_PNG);

    
    SDL_Window* window = NULL;
    SDL_Renderer* ren = NULL;

    //Génération de la fenêtre  
    window = SDL_CreateWindow("TankRider", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 720, SDL_WINDOW_SHOWN);
    ren =  SDL_CreateRenderer( window, 0, SDL_RENDERER_TARGETTEXTURE);

    SDL_Event event;

    //int level =0;
    
    //Entier controllant l'affichage de la fenetre
    int ON = 1;

    int level=0;


    Menu(ren);

    //Initialisation de la position du curseur
    int MouseX = 0;
    int MouseY = 0;

    int affichage_niv=0;


    

    while( ON == 1 ) {
        SDL_WaitEvent(&event);
        switch( event.type){
            //Gestion de la fermeture
            case SDL_QUIT : 
            ON = 0;
            break;
           case SDL_MOUSEMOTION :
                MouseX=event.motion.x;
                MouseY=event.motion.y;
            break;
            case SDL_MOUSEBUTTONDOWN:
                if(MouseX>320 && MouseX<595 && MouseY<575 && MouseY>535){
                    level=1;
                   // printf("%d\n",level );
                }
                if(MouseX>370 && MouseX<560 && MouseY<630 && MouseY>595){//Bouton niv
                	affichage_niv = 1;
                	levels(ren);
                }
                if(affichage_niv==1){
                	level= lecture_niv(MouseX, MouseY);
                	if(level!=0){
                		affichage_niv = 0;
                	}
                   // printf("%d\n",level );

                }
            break;
        
        }       
    }           

   
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
	return 0;
}