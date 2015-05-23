#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdbool.h>
#include <unistd.h>
#include "attaque.h"

void fire(SDL_Renderer *ren,SDL_Surface *Missile,int xmissile,int ymissile){
    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(ren, Missile);
    SDL_Rect dst;
    dst.x = xmissile;
    dst.y = ymissile;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

bool attaque_ennemi(int x, int y,int xE, int yE, int setE){
    //tableau de direction
    int dx[9]={-5,0,5,-5,0,5,-5,0,5};
    int dy[9]={5,5,5,0,0,0,-5,-5,-5};

    int i;
    for(i=0;i<4;i++){
        if(x==xE+(10*i)*dx[setE-1] && y==yE+(10*i)*dy[setE-1]){
            return true;
        }
    }
        
    return false;  
}

void tirerE(int setE,int xE,int yE,int x,int y,SDL_Renderer* ren){
	int angles[] ={0,45,90,-45,0,135,-90,-135,180};

	//coordonnée de missile
    int xmissile=0;
    int ymissile=0;

    //tableau de direction
    int dx[9]={-5,0,5,-5,0,5,-5,0,5};
    int dy[9]={5,5,5,0,0,0,-5,-5,-5};

	//Missiles
    SDL_Surface *Missile = NULL;
    SDL_Surface *m_1 = IMG_Load("IMG/missile1.png");

    SDL_Surface *Explosion = NULL;
    SDL_Surface *e_1 = IMG_Load("IMG/case_explosion1.png");
    SDL_Surface *e_2 = IMG_Load("IMG/case_explosion2.png");
    SDL_Surface *e_3 = IMG_Load("IMG/case_explosion3.png");
    SDL_Surface *e_4 = IMG_Load("IMG/case_explosion4.png");
    SDL_Surface *e_5 = IMG_Load("IMG/case_explosion5.png");
    SDL_Surface *e_6 = IMG_Load("IMG/case_explosion6.png");
    SDL_Surface *e_7 = IMG_Load("IMG/case_explosion7.png");

    SDL_Surface* explosions[7]= {e_1,e_2,e_3,e_4,e_5,e_6,e_7};

	Missile=rotozoomSurface(m_1,angles[setE-1], 1, 1);
	xmissile=xE;
	ymissile=yE;
	while(!(xmissile==x && ymissile==y)){
		fire(ren,Missile,xmissile,ymissile);
		xmissile=xmissile+dx[setE-1];
		ymissile=ymissile+dy[setE-1];
		SDL_RenderPresent(ren);
	}
	xmissile = 2000;
	ymissile = 2000;
	int k;
	for(k=0;k<7;k++){
		Explosion = explosions[6-k];
		fire(ren,Explosion,x,y);
		SDL_RenderPresent(ren);
		usleep(75000);
	}
}
void tirer(SDL_Renderer* ren,int set,int x,int y,int ne,int xEnnemie[],int yEnnemie[],int StatutE[]){
	int angles[] ={0,45,90,-45,0,135,-90,-135,180};

	//coordonnée de missile
    int xmissile=0;
    int ymissile=0;

    //tableau de direction
    int dx[9]={-5,0,5,-5,0,5,-5,0,5};
    int dy[9]={5,5,5,0,0,0,-5,-5,-5};

	//Missiles
    SDL_Surface *Missile = NULL;
    SDL_Surface *m_1 = IMG_Load("IMG/missile1.png");

    SDL_Surface *Explosion = NULL;
    SDL_Surface *e_1 = IMG_Load("IMG/case_explosion1.png");
    SDL_Surface *e_2 = IMG_Load("IMG/case_explosion2.png");
    SDL_Surface *e_3 = IMG_Load("IMG/case_explosion3.png");
    SDL_Surface *e_4 = IMG_Load("IMG/case_explosion4.png");
    SDL_Surface *e_5 = IMG_Load("IMG/case_explosion5.png");
    SDL_Surface *e_6 = IMG_Load("IMG/case_explosion6.png");
    SDL_Surface *e_7 = IMG_Load("IMG/case_explosion7.png");

    SDL_Surface* explosions[7]= {e_1,e_2,e_3,e_4,e_5,e_6,e_7};

	Missile=rotozoomSurface(m_1,angles[set-1], 1, 1);
	xmissile=x;
	ymissile=y;
	xmissile=x+dx[set-1];
    ymissile=y+dy[set-1];
    while(xmissile<=635 && xmissile>=25 && ymissile<=635 && ymissile>=25){
    	fire(ren,Missile,xmissile,ymissile);
    	SDL_RenderPresent(ren);  
    	xmissile=xmissile+dx[set-1];
    	ymissile=ymissile+dy[set-1];
    	int s=0;
    	for(s=0;s<ne;s++){
    		if(xmissile==xEnnemie[s] && ymissile==yEnnemie[s]){
    			xmissile = 2000;
    			ymissile = 2000;
    			int k;
    			for(k=0;k<7;k++){
    				Explosion = explosions[6-k];
    				fire(ren,Explosion,xEnnemie[s],yEnnemie[s]);
    				SDL_RenderPresent(ren);
    				usleep(75000);
    			}
    			StatutE[s]=1;
    		}
    	}
    }
}