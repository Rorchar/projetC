#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdbool.h>
#include <unistd.h>
#include "background.h"
#include "tank.h"
#include "disponibilite.h"
#include "case.h"
#include "map.h"

bool attaque_ennemi(int x, int y,int xE, int yE, int setE);

int main(){
    
    SDL_Window* window = NULL;
    SDL_Renderer* ren = NULL;

    SDL_Event event;
    
    //Entier controllant l'affichage de la fenetre
    int ON = 1;
    
    //Initialisation
    //Ajouter la gestion de l'erreur
    SDL_Init(SDL_INIT_VIDEO); 
    IMG_Init(IMG_INIT_PNG);
    TTF_Init(); 

    

    //Génération de la fenêtre  
    window = SDL_CreateWindow("TankRider : Level 00", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 720, SDL_WINDOW_SHOWN);
    ren =  SDL_CreateRenderer( window, 0, SDL_RENDERER_TARGETTEXTURE);
    
    //Initialisation de la position du curseur
    int MouseX = 0;
    int MouseY = 0;

    //Ces 3 tab enregistrentles coords et le bouton qui est down
    //36 est un nombre quelconque, à redefinir en fonction des courte
    int xcible[36];
    int ycible[36];
    int d_on_tab[36];
    
    //Nombre de fleche posée
    int nb=0;

    //Element de la boucle de dessin
    int nbj;

    //indice de la fleche selected
    int d_on=5;

    //Tableau des armes et defense
    int xtarget[36];
    int ytarget[36];
    int arm_on_tab[36];

    //nombre d'arme posée
    int na=0;

    //Element de la boucle arme
    int naj=0;

    //indice de l'arme
    int arm_on=0;

    int lvl=1;

    first_components_of_the_background(ren);
    niv(lvl,ren);

    int nb_fleche[12]={0,2,0,1,0,1,0,0,0,1,1,0};
    maj_panneau(ren,nb_fleche);
    
   
    int xE1 = PosE(lvl,0);
    int yE1 = PosE(lvl,1);
    int setE1= PosE(lvl,2);
    int StatutE1 =PosE(lvl,3);
    mvt_tank(ren, xE1,yE1, setE1, 0);
    int xE2 = PosE(lvl,4);
    int yE2 = PosE(lvl,5);
    int setE2= PosE(lvl,6);
    int StatutE2 =PosE(lvl,7);
    mvt_tank(ren, xE2,yE2, setE2, 0);

    int x=Pos(lvl,0);
    int y=Pos(lvl,1);
    int set = Pos(lvl,2);
    mvt_tank(ren,x,y,set,1);

    //tableau de direction
    int dx[9]={-5,0,5,-5,0,5,-5,0,5};
    int dy[9]={5,5,5,0,0,0,-5,-5,-5};

    //Missiles
    SDL_Surface *Missile = NULL;
    SDL_Surface *m_1 = IMG_Load("IMG/missile1.png");

    int angles[] ={0,45,90,-45,0,135,-90,-135,180};

    //explosions
    SDL_Surface *Explosion = NULL;
    SDL_Surface *e_1 = IMG_Load("IMG/case_explosion1.png");
    SDL_Surface *e_2 = IMG_Load("IMG/case_explosion2.png");
    SDL_Surface *e_3 = IMG_Load("IMG/case_explosion3.png");
    SDL_Surface *e_4 = IMG_Load("IMG/case_explosion4.png");
    SDL_Surface *e_5 = IMG_Load("IMG/case_explosion5.png");
    SDL_Surface *e_6 = IMG_Load("IMG/case_explosion6.png");
    SDL_Surface *e_7 = IMG_Load("IMG/case_explosion7.png");

    SDL_Surface* explosions[7]= {e_1,e_2,e_3,e_4,e_5,e_6,e_7};


    //coordonnée de missile
    int xmissile=0;
    int ymissile=0;

    SDL_RenderPresent(ren);

    int action = 0;

    int map01[13][13] = {
                    {0,0,0,6,15,2,2,2,2,2,4,0,0},
                    {9,0,0,6,2,1,1,1,1,2,11,9,0},
                    {3,0,0,6,2,5,5,1,1,15,2,4,0},
                    {0,0,0,6,2,5,5,5,1,15,2,4,0},
                    {0,0,0,6,2,2,5,5,1,2,2,4,0},
                    {0,0,0,6,14,14,1,1,2,2,7,3,0},
                    {9,0,0,6,2,2,1,1,2,2,4,0,0},
                    {4,0,0,6,2,2,2,15,2,7,3,0,0},
                    {3,0,0,13,8,8,8,12,8,3,0,0,0},
                    {0,0,0,0,0,0,0,12,0,0,0,0,0},
                    {0,0,0,16,10,10,10,12,9,0,0,0,0},
                    {0,0,0,6,2,14,2,2,11,10,9,0,0},
                    {0,0,0,6,2,5,1,1,5,2,4,0,0},
                };
    int Drapeau[2]={385,635}; 

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
                //detection de la fleche selected
                if(MouseX>731 && MouseX<879 && MouseY<229 && MouseY>81){
                    d_on = choix_direction(MouseX,MouseY);
                }
                if(MouseX>731 && MouseX<879 && MouseY<349 && MouseY>301){
                    arm_on= choix_arme(MouseX,MouseY);
                }
                if (event.button.button == SDL_BUTTON_LEFT){
                    if(MouseX>731 && MouseX<879 && MouseY>531 && MouseY<579){//BOUTON START
                        action = 1;
                    }
                    if(MouseX>731 && MouseX<879 && MouseY>601 && MouseY<649){//BOUTON RESET
                        niv(lvl,ren);
                        nb_fleche[0]= 0;
                        nb_fleche[1]= 2;
                        nb_fleche[2]= 0;
                        nb_fleche[3]= 1;
                        nb_fleche[4]= 0;
                        nb_fleche[5]= 1;
                        nb_fleche[6]= 0;
                        nb_fleche[7]= 0;
                        nb_fleche[8]= 0;
                        nb_fleche[9]= 1;
                        nb_fleche[10]= 1;
                        nb_fleche[11]= 0;
                        maj_panneau(ren,nb_fleche);
                        StatutE1 =PosE(lvl,3);
                        StatutE2 =PosE(lvl,7);
                        mvt_tank(ren, xE1,yE1, setE1, 0);
                        mvt_tank(ren, xE2,yE2, setE2, 0);
                        x = Pos(lvl,0);
                        y =Pos(lvl,1);;
                        set =Pos(lvl,2);
                        d_on=5;
                        arm_on=0;
                        nb=0;
                        na=0;
                        mvt_tank(ren,x,y,set,1);
                        SDL_RenderPresent(ren);
                    }
                }                
            break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT){
                    if(MouseX<685 && MouseX>38 && MouseY< 685 && MouseY>38 ){
                        if(d_on!=5 ){
                            if((nb_fleche[d_on-1])>0){
                                xcible[nb]= 35+50*(((MouseX+12)/50)-1);
                                ycible[nb]= 35+50*(((MouseY+12)/50)-1);
                                d_on_tab[nb]=d_on;
                                small_direction (ren,xcible[nb],ycible[nb],d_on_tab[nb]);
                                nb++;
                                nb_fleche[d_on-1]=(nb_fleche[d_on-1])-1;
                                maj_panneau(ren,nb_fleche);
                                d_on=5;
                            }    
                        }
                        if(arm_on!=0){
                            if((nb_fleche[arm_on+9-1])>0){
                                xtarget[na]= 35+50*(((MouseX+12)/50)-1);
                                ytarget[na]= 35+50*(((MouseY+12)/50)-1);
                                arm_on_tab[na]=arm_on;
                                case_tir (ren,xtarget[na],ytarget[na],arm_on_tab[na]);
                                na++;
                                nb_fleche[arm_on+9-1]=(nb_fleche[arm_on+9-1])-1;
                                maj_panneau(ren,nb_fleche);
                                arm_on=0;
                            }
                        } 
                        SDL_RenderPresent(ren);
                    }
                }
            break;
        }
        while (action==1 ){
            niv(lvl,ren);
            //int o=0;
            //for (o=0;o<nbE;o++){
                if(StatutE1==0){
                   mvt_tank(ren, xE1,yE1, setE1, 0);
                }
                if(StatutE2==0){
                   mvt_tank(ren, xE2,yE2, setE2, 0);
                }
            //}
            for(nbj = 0; nbj<nb;nbj++){
                if(nb!=0){
                    small_direction (ren,xcible[nbj],ycible[nbj],d_on_tab[nbj]);
                }
            }
            for(naj = 0; naj<na;naj++){
                if(na!=0){
                    case_tir(ren,xtarget[naj],ytarget[naj],arm_on_tab[naj]);
                }
            }

            for(naj=0;naj<na;naj++){
                if(x+15==xtarget[naj] && y+15==ytarget[naj]){
                    if(arm_on_tab[naj]==1){
                        //tirer4(Explosion,ren,set,x,y,nbE,StatutE,dx,dy,xTankE,yTankE);
                        usleep(50000);
                    }else if(arm_on_tab[naj]==2){
                        //tirer(Explosion,ren,set,x,y,nbE,StatutE,dx,dy,xTankE,yTankE);
                        usleep(50000);
                    }else{
                        //bouclier=1;
                    }
                }
            }

            x=x+dx[set-1];
            y=y+dy[set-1];
            action = evite_mer(window, x, y, map01);
            mvt_tank(ren, x ,y,set ,1); 
    
            SDL_RenderPresent(ren);

            if((x==630 || x==15 || y==630 || y==15)){ //borne a verifier
                action=0;
                SDL_ShowSimpleMessageBox(0, "out", "Vous etes hors champs ", window);
            }
            
            for(nbj=0;nbj<nb;nbj++){
                if((x+15)==xcible[nbj] && (y+15)==ycible[nbj]){
                    set= d_on_tab[nbj];    
                }
            }

            if((x+15)==Drapeau[0] && (y+15)==Drapeau[1]){
                action=0;
                lvl++;
                niv(lvl,ren);
                x=Pos(lvl,0);
                y=Pos(lvl,1);
                set = Pos(lvl,2);
                mvt_tank(ren,x,y,set,1);
                xE1 = PosE(lvl,0);
                yE1 = PosE(lvl,1);
                setE1= PosE(lvl,2);
                mvt_tank(ren, xE1,yE1, setE1, 0);
                xE2 = PosE(lvl,4);
                yE2 = PosE(lvl,5);
                setE2= PosE(lvl,6);
                mvt_tank(ren, xE2,yE2, setE2, 0);
                SDL_ShowSimpleMessageBox(0, "WIN", "niv1 terminer ", window);
            }

            if (attaque_ennemi(x, y, xE1, yE1, setE1) && StatutE1==0){
                Missile=rotozoomSurface(m_1,angles[setE1-1], 1, 1);
                xmissile=xE1;
                ymissile=yE1;
                while(!(xmissile==x && ymissile==y)){
                    fire(ren,Missile,xmissile,ymissile);
                    xmissile=xmissile+dx[setE1-1];
                    ymissile=ymissile+dy[setE1-1];
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
                SDL_ShowSimpleMessageBox(0, "HIT", "Vous etes mort", window);
                action=0;
            }
            if (attaque_ennemi(x, y, xE2, yE2, setE2) && StatutE2==0){
                Missile=rotozoomSurface(m_1,angles[setE2-1], 1, 1);
                xmissile=xE2;
                ymissile=yE2;
                while(!(xmissile==x && ymissile==y)){
                    fire(ren,Missile,xmissile,ymissile);
                    xmissile=xmissile+dx[setE2-1];
                    ymissile=ymissile+dy[setE2-1];
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
                SDL_ShowSimpleMessageBox(0, "HIT", "Vous etes mort", window);
                action=0;
            }
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}

bool attaque_ennemi(int x, int y,int xE, int yE, int setE){
    //tableau de direction
    int dx[9]={-5,0,5,-5,0,5,-5,0,5};
    int dy[9]={5,5,5,0,0,0,-5,-5,-5};

    int i;
    for(i=0;i<5;i++){
        if(x==xE+(10*i)*dx[setE-1] && y==yE+(10*i)*dy[setE-1]){
            return true;
        }
    }
        
    return false;  
}
