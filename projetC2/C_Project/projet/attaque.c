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
bool attaque_mine(int x, int y,int xM, int yM){

    if(x==xM && y==yM){
        return true;
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
void tirerM(int x,int y,SDL_Renderer* ren){

    SDL_Surface *Explosion = NULL;
    SDL_Surface *e_1 = IMG_Load("IMG/case_explosion1.png");
    SDL_Surface *e_2 = IMG_Load("IMG/case_explosion2.png");
    SDL_Surface *e_3 = IMG_Load("IMG/case_explosion3.png");
    SDL_Surface *e_4 = IMG_Load("IMG/case_explosion4.png");
    SDL_Surface *e_5 = IMG_Load("IMG/case_explosion5.png");
    SDL_Surface *e_6 = IMG_Load("IMG/case_explosion6.png");
    SDL_Surface *e_7 = IMG_Load("IMG/case_explosion7.png");

    SDL_Surface* explosions[7]= {e_1,e_2,e_3,e_4,e_5,e_6,e_7};

    int k;
    for(k=0;k<7;k++){
        Explosion = explosions[6-k];
        fire(ren,Explosion,x,y);
        SDL_RenderPresent(ren);
        usleep(75000);
    }
}
void tirer(SDL_Renderer* ren,int set,int x,int y,int ne,int nm,int xEnnemie[],int yEnnemie[],int StatutE[],int xMine[],int yMine[],int StatutM[]){
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
        for(s=0;s<nm;s++){
            if(xmissile==xMine[s] && ymissile==yMine[s]){
                xmissile = 2000;
                ymissile = 2000;
                int k;
                for(k=0;k<7;k++){
                    Explosion = explosions[6-k];
                    fire(ren,Explosion,xMine[s],yMine[s]);
                    SDL_RenderPresent(ren);
                    usleep(75000);
                }
                StatutM[s]=1;
            }
        }
    }
}
/*void tirer4(SDL_Renderer* ren,int set,int x,int y,int ne,int nm,int xEnnemie[],int yEnnemie[],int StatutE[],int xMine[],int yMine[],int StatutM[]){

    int angles[] ={0,45,90,-45,0,135,-90,-135,180};

    //coordonnée de missile
    int xmissile1=0;
    int ymissile1=0;
    int xmissile2=0;
    int ymissile2=0;
    int xmissile3=0;
    int ymissile3=0;
    int xmissile4=0;
    int ymissile4=0;
    int set1=0;
    int set2=0;
    int set3=0;
    int set4=0;
    if(set%2==0){
        set1=2;
        set2=4;
        set3=6;
        set4=8;
    }else{
        set1=1;
        set2=3;
        set3=7;
        set4=9;
    }

    //tableau de direction
    int dx[9]={-5,0,5,-5,0,5,-5,0,5};
    int dy[9]={5,5,5,0,0,0,-5,-5,-5};

    //Missiles
    SDL_Surface *Missile1 = NULL;
    SDL_Surface *Missile2 = NULL;
    SDL_Surface *Missile3 = NULL;
    SDL_Surface *Missile4 = NULL;
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

    Missile1=rotozoomSurface(m_1,angles[set1-1], 1, 1);
    Missile2=rotozoomSurface(m_1,angles[set2-1], 1, 1);
    Missile3=rotozoomSurface(m_1,angles[set3-1], 1, 1);
    Missile4=rotozoomSurface(m_1,angles[set4-1], 1, 1);
    xmissile1=x+dx[set1-1];
    ymissile1=y+dy[set1-1];
    xmissile2=x+dx[set2-1];
    ymissile2=y+dy[set2-1];
    xmissile3=x+dx[set3-1];
    ymissile3=y+dy[set3-1];
    xmissile4=x+dx[set4-1];
    ymissile4=y+dy[set4-1];

    while((xmissile1<=635 && xmissile1>=25 && ymissile1<=635 && ymissile1>=25) || (xmissile2<=635 && xmissile2>=25 && ymissile2<=635 && ymissile2>=25) || (xmissile3<=635 && xmissile3>=25 && ymissile3<=635 && ymissile3>=25) || (xmissile4<=635 && xmissile4>=25 && ymissile4<=635 && ymissile4>=25)){
        fire(ren,Missile1,xmissile1,ymissile1);
        fire(ren,Missile2,xmissile2,ymissile2);
        fire(ren,Missile3,xmissile3,ymissile3);
        fire(ren,Missile4,xmissile4,ymissile4);
        usleep(50000);
        SDL_RenderPresent(ren);
        xmissile1=xmissile1+dx[set1-1];
        ymissile1=ymissile1+dy[set1-1];
        xmissile2=xmissile2+dx[set2-1];
        ymissile2=ymissile2+dy[set2-1];
        xmissile3=xmissile3+dx[set3-1];
        ymissile3=ymissile3+dy[set3-1];
        xmissile4=xmissile4+dx[set4-1];
        ymissile4=ymissile4+dy[set4-1];
        if(!(xmissile1<=635 && xmissile1>=25 && ymissile1<=635 && ymissile1>=25)){
            xmissile1=2000;
            ymissile1=2000;
        }
        if(!(xmissile2<=635 && xmissile2>=25 && ymissile2<=635 && ymissile2>=25)){
            xmissile2=2000;
            ymissile2=2000;
        }
        if(!(xmissile3<=635 && xmissile3>=25 && ymissile3<=635 && ymissile3>=25)){
            xmissile3=2000;
            ymissile3=2000;
        }
        if(!(xmissile4<=635 && xmissile4>=25 && ymissile4<=635 && ymissile4>=25)){
            xmissile4=2000;
            ymissile4=2000;
        }
        int s=0;
        for(s=0;s<ne;s++){
            if(xmissile1==xEnnemie[s] && ymissile1==yEnnemie[s]){
                xmissile1 = 2000;
                ymissile1 = 2000;
                int k;
                for(k=0;k<7;k++){
                    Explosion = explosions[6-k];
                    fire(ren,Explosion,xEnnemie[s],yEnnemie[s]);
                    usleep(75000);
                    SDL_RenderPresent(ren);
                }
                StatutE[s]=1;
            }
            if(xmissile2==xEnnemie[s] && ymissile2==yEnnemie[s]){
                xmissile2 = 2000;
                ymissile2 = 2000;
                int k;
                for(k=0;k<7;k++){
                    Explosion = explosions[6-k];
                    fire(ren,Explosion,xEnnemie[s],yEnnemie[s]);
                    usleep(75000);
                    SDL_RenderPresent(ren);
                }
                StatutE[s]=1;
            }
            if(xmissile3==xEnnemie[s] && ymissile3==yEnnemie[s]){
                xmissile3 = 2000;
                ymissile3 = 2000;
                int k;
                for(k=0;k<7;k++){
                    Explosion = explosions[6-k];
                    fire(ren,Explosion,xEnnemie[s],yEnnemie[s]);
                    usleep(75000);
                    SDL_RenderPresent(ren);
                }
                StatutE[s]=1;
            }
            if(xmissile4==xEnnemie[s] && ymissile4==yEnnemie[s]){
                xmissile4 = 2000;
                ymissile4 = 2000;
                int k;
                for(k=0;k<7;k++){
                    Explosion = explosions[6-k];
                    fire(ren,Explosion,xEnnemie[s],yEnnemie[s]);
                    usleep(75000);
                    SDL_RenderPresent(ren);
                }
                StatutE[s]=1;
            }
        }
        for(s=0;s<nm;s++){
            if(xmissile1==xMine[s] && ymissile1==yMine[s]){
                xmissile1 = 2000;
                ymissile1 = 2000;
                int k;
                for(k=0;k<7;k++){
                    Explosion = explosions[6-k];
                    fire(ren,Explosion,xMine[s],yMine[s]);
                    usleep(75000);
                    SDL_RenderPresent(ren);
                }
                StatutM[s]=1;
            }
            if(xmissile2==xMine[s] && ymissile2==yMine[s]){
                xmissile2 = 2000;
                ymissile2 = 2000;
                int k;
                for(k=0;k<7;k++){
                    Explosion = explosions[6-k];
                    fire(ren,Explosion,xMine[s],yMine[s]);
                    usleep(75000);
                    SDL_RenderPresent(ren);
                }
                StatutM[s]=1;
            }
            if(xmissile3==xMine[s] && ymissile3==yMine[s]){
                xmissile3 = 2000;
                ymissile3 = 2000;
                int k;
                for(k=0;k<7;k++){
                    Explosion = explosions[6-k];
                    fire(ren,Explosion,xMine[s],yMine[s]);
                    usleep(75000);
                    SDL_RenderPresent(ren);
                }
                StatutM[s]=1;
            }
            if(xmissile4==xMine[s] && ymissile4==yMine[s]){
                xmissile4 = 2000;
                ymissile4 = 2000;
                int k;
                for(k=0;k<7;k++){
                    Explosion = explosions[6-k];
                    fire(ren,Explosion,xMine[s],yMine[s]);
                    usleep(75000);
                    SDL_RenderPresent(ren);
                }
                StatutM[s]=1;
            }
        }
    }
}*/
