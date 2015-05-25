#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <unistd.h>
#include "background.h"
#include "casepose.h"

void directions_panel(SDL_Renderer *ren, int x, int y);

int choix_direction(int mx, int my);

int choix_arme(int mx,int my);

void fire(SDL_Renderer *ren,SDL_Surface *Missile,int xmissile,int ymissile);

void tirer(SDL_Surface *Explosion,SDL_Renderer * ren,int set,int x,int y,int nbE,int *StatutE,int *dx,int *dy,int *xTankE,int *yTankE);

void tirer4(SDL_Surface *Explosion,SDL_Renderer * ren,int set,int x,int y,int nbE,int *StatutE,int *dx,int *dy,int *xTankE,int *yTankE);

int main(){

    SDL_Window* window = NULL;
    SDL_Renderer* ren = NULL;
    SDL_Surface* Tank = NULL;
    SDL_Surface* Tank_E = NULL;
    SDL_Surface* Explosion = NULL; 
    SDL_Surface* Missile = NULL;

    SDL_Event event;
    int ON = 1;
    
    //Initialisation
    //Ajouter la gestion de l'erreur
    SDL_Init(SDL_INIT_VIDEO);  
    IMG_Init(IMG_INIT_PNG);

    //Génération de la fenêtre  
    window = SDL_CreateWindow("TankRider : Level 00", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 720, SDL_WINDOW_SHOWN);
    ren =  SDL_CreateRenderer( window, 0, SDL_RENDERER_TARGETTEXTURE);

    //Trouver une façon plus elegante permettant de charger les surfaces
    SDL_Surface *t_1 = IMG_Load("IMG/tank1.png");
    SDL_Surface *t_2 = IMG_Load("IMG/tank2.png");
    SDL_Surface *t_3 = IMG_Load("IMG/tank3.png");
    SDL_Surface *t_4 = IMG_Load("IMG/tank4.png");
    SDL_Surface *t_5 = NULL;
    SDL_Surface *t_6 = IMG_Load("IMG/tank6.png");
    SDL_Surface *t_7 = IMG_Load("IMG/tank7.png");
    SDL_Surface *t_8 = IMG_Load("IMG/tank8.png");
    SDL_Surface *t_9 = IMG_Load("IMG/tank9.png");

    SDL_Surface* Tanks[9]= {t_1,t_2,t_3,t_4,t_5,t_6,t_7,t_8,t_9};

    SDL_Surface *b_1 = IMG_Load("IMG/bouclier1.png");
    SDL_Surface *b_2 = IMG_Load("IMG/bouclier2.png");
    SDL_Surface *b_3 = IMG_Load("IMG/bouclier3.png");
    SDL_Surface *b_4 = IMG_Load("IMG/bouclier4.png");
    SDL_Surface *b_5 = NULL;
    SDL_Surface *b_6 = IMG_Load("IMG/bouclier6.png");
    SDL_Surface *b_7 = IMG_Load("IMG/bouclier7.png");
    SDL_Surface *b_8 = IMG_Load("IMG/bouclier8.png");
    SDL_Surface *b_9 = IMG_Load("IMG/bouclier9.png");

    SDL_Surface* TanksBouclier[9]= {b_1,b_2,b_3,b_4,b_5,b_6,b_7,b_8,b_9};

    //Meme chose mais pour missile
    SDL_Surface *m_1 = IMG_Load("IMG/missile1.png");
    SDL_Surface *m_2 = IMG_Load("IMG/missile2.png");
    SDL_Surface *m_3 = IMG_Load("IMG/missile3.png");
    SDL_Surface *m_4 = IMG_Load("IMG/missile4.png");
    SDL_Surface *m_5 = NULL;
    SDL_Surface *m_6 = IMG_Load("IMG/missile6.png");
    SDL_Surface *m_7 = IMG_Load("IMG/missile7.png");
    SDL_Surface *m_8 = IMG_Load("IMG/missile8.png");
    SDL_Surface *m_9 = IMG_Load("IMG/missile9.png");

    SDL_Surface* Missiles[9]= {m_1,m_2,m_3,m_4,m_5,m_6,m_7,m_8,m_9};


    //explosions
    SDL_Surface *e_1 = IMG_Load("IMG/case_explosion1.png");
    SDL_Surface *e_2 = IMG_Load("IMG/case_explosion2.png");
    SDL_Surface *e_3 = IMG_Load("IMG/case_explosion3.png");
    SDL_Surface *e_4 = IMG_Load("IMG/case_explosion4.png");
    SDL_Surface *e_5 = IMG_Load("IMG/case_explosion5.png");
    SDL_Surface *e_6 = IMG_Load("IMG/case_explosion6.png");
    SDL_Surface *e_7 = IMG_Load("IMG/case_explosion7.png");

    SDL_Surface* explosions[7]= {e_1,e_2,e_3,e_4,e_5,e_6,e_7};

    //Tank ennemie
    SDL_Surface *E_1 = IMG_Load("IMG/ennemie1.png");
    SDL_Surface *E_2 = IMG_Load("IMG/ennemie2.png");
    SDL_Surface *E_3 = IMG_Load("IMG/ennemie3.png");
    SDL_Surface *E_4 = IMG_Load("IMG/ennemie4.png");
    SDL_Surface *E_5 = NULL;
    SDL_Surface *E_6 = IMG_Load("IMG/ennemie6.png");
    SDL_Surface *E_7 = IMG_Load("IMG/ennemie7.png");
    SDL_Surface *E_8 = IMG_Load("IMG/ennemie8.png");
    SDL_Surface *E_9 = IMG_Load("IMG/ennemie9.png");

    SDL_Surface* TankE[9]= {E_1,E_2,E_3,E_4,E_5,E_6,E_7,E_8,E_9};



    //Coord du premier Tank
    int x = 35;
    int y = 35;

    //statut bouclier
    int bouclier=0;

    //nb de case avec bouclier
    int nbb=0;

    //Initialisation de la position du curseur
    int MouseX = 0;
    int MouseY = 0;
    
    //Ces 3 tab enregistrentles coords et le bouton qui est down
    //36 est un nombre quelconque, à redefinir en fonction des courte
    int xcible[36];
    int ycible[36];
    int d_on_tab[36];

    //coordonnée drapeau
    int xdrapeau=535;
    int ydrapeau=535;
    
    //Tableau des armes et defense
    int xtarget[36];
    int ytarget[36];
    int arm_on_tab[36];
    //Nombre de fleche posée
    int nb=0;
    //nombre d'arme posée
    int na=0;
    //Element de la boucle de dessin
    int nbj;
    //Element de la boucle arme
    int naj=0;
    //indice de la fleche selected
    int d_on = 0;

    //indice de l'arme
    int arm_on=0;

    //Debut du jeu
    int action =0;

    //Position intial
    int set = 6;

    //tableau de direction
    int dx[9]={-5,0,5,-5,0,5,-5,0,5};
    int dy[9]={5,5,5,0,0,0,-5,-5,-5};

    //coordonnée de missile
    int xmissile=0;
    int ymissile=0;

    //nombre d'ennemie
    int nbE=2;

    //statut tank
    int StatutE[]={0,0};

    //tableau coordonnée tank ennemie
    int xTankE[]={435,235};
    int yTankE[]={535,485};
    int setE[]={4,8};

    first_components_of_the_background (ren);
    fond_carte(ren,Tank_E,Tank,xdrapeau,ydrapeau,nbE,nb,na,StatutE,TankE,Tanks,x,y,set,setE,xcible,ycible,xtarget,ytarget,xTankE,yTankE,d_on_tab,arm_on_tab,&nbb,bouclier,TanksBouclier);

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
            break;
            case SDL_APP_WILLENTERFOREGROUND:

                fond_carte(ren,Tank_E,Tank,xdrapeau,ydrapeau,nbE,nb,na,StatutE,TankE,Tanks,x,y,set,setE,xcible,ycible,xtarget,ytarget,xTankE,yTankE,d_on_tab,arm_on_tab,&nbb,bouclier,TanksBouclier);

            break;

            case SDL_MOUSEBUTTONUP:
            //#### AJOUTER LA RESTRICTION DE LA POSITION DE LA FLECHE  ########
                if (event.button.button == SDL_BUTTON_LEFT){
                    //Placement dans "la grille"
                    //Pas encore dessinée
                    if(MouseX<685 && MouseX>38 && MouseY< 685 && MouseY>38 ){
                        if(d_on!=0){
                            xcible[nb]= 35+50*(((MouseX+12)/50)-1);
                            ycible[nb]= 35+50*(((MouseY+12)/50)-1);
                            d_on_tab[nb]=d_on;
                            d_on=0;
                            small_direction (ren,xcible[nb],ycible[nb],d_on_tab[nb]);
                            nb++;
                        }
                        if(arm_on!=0){
                            xtarget[na]= 35+50*(((MouseX+12)/50)-1);
                            ytarget[na]= 35+50*(((MouseY+12)/50)-1);
                            arm_on_tab[na]=arm_on;
                            arm_on=0;
                            case_tir (ren,xtarget[na],ytarget[na],arm_on_tab[na]);
                            na++;
                        }   
                        SDL_RenderPresent(ren);
                    }
                }
                if (event.button.button == SDL_BUTTON_LEFT){
                    if(MouseX>731 && MouseX<879 && MouseY>601 && MouseY<649){
                        action = 1;
                    }
                }
            break;
        }

        while (action==1){    

            x=x+dx[set-1];
            y=y+dy[set-1];

            fond_carte(ren,Tank_E,Tank,xdrapeau,ydrapeau,nbE,nb,na,StatutE,TankE,Tanks,x,y,set,setE,xcible,ycible,xtarget,ytarget,xTankE,yTankE,d_on_tab,arm_on_tab,&nbb,bouclier,TanksBouclier);

            if((x==640 || x==25 || y==640 || y==25)){ //borne a verifier
                action=0;
                SDL_ShowSimpleMessageBox(0, "out", "vous etes hors champs ", window);
            }
        
            for(nbj=0;nbj<nb;nbj++){
                if(x==xcible[nbj] && y==ycible[nbj]){
                    set= d_on_tab[nbj];    
                }
            }
            for(naj=0;naj<na;naj++){
                if(x==xtarget[naj] && y==ytarget[naj]){
                    if(arm_on_tab[naj]==1){
                        tirer4(Explosion,ren,set,x,y,nbE,StatutE,dx,dy,xTankE,yTankE);
                        usleep(50000);
                    }else if(arm_on_tab[naj]==2){
                        tirer(Explosion,ren,set,x,y,nbE,StatutE,dx,dy,xTankE,yTankE);
                        usleep(50000);
                    }else{
                        bouclier=1;
                    }
                }
            }
            if(x==xdrapeau && y==ydrapeau){
                action=0;
                SDL_ShowSimpleMessageBox(0, "WIN", "niv1 terminer ", window);
            }
            
            int f=0;
            for (f=0;f<nbE;f++){
                if ((((x==xTankE[f] &&y==yTankE[f]) || (x==xTankE[f]+10*dx[setE[f]-1] && y==yTankE[f]+10*dy[setE[f]-1]) || (x==xTankE[f]+20*dx[setE[f]-1] && y==yTankE[f]+20*dy[setE[f]-1]) || (x==xTankE[f]+30*dx[setE[f]-1] && y==yTankE[f]+30*dy[setE[f]-1])) && StatutE[f]==0) && bouclier!=1){
                    Missile=Missiles[setE[f]-1];
                    xmissile=xTankE[f];
                    ymissile=yTankE[f];
                    while(!(xmissile==x && ymissile==y)){
                        fire(ren,Missile,xmissile,ymissile);
                        xmissile=xmissile+dx[setE[f]-1];
                        ymissile=ymissile+dy[setE[f]-1];
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
                    SDL_ShowSimpleMessageBox(0, "HIT", "vous etes mort", window);
                    action=0;
                }
            }
            usleep(500);          
        }
    }


    //SDL_FreeSurface(Tank);    //tableau de direction
    
    SDL_FreeSurface(t_1);
    SDL_FreeSurface(t_2);
    SDL_FreeSurface(t_3);
    SDL_FreeSurface(t_4);
    SDL_FreeSurface(t_5);
    SDL_FreeSurface(t_6);
    SDL_FreeSurface(t_7);
    SDL_FreeSurface(t_8);
    SDL_FreeSurface(t_9);

    SDL_FreeSurface(m_1);
    SDL_FreeSurface(m_2);
    SDL_FreeSurface(m_3);
    SDL_FreeSurface(m_4);
    SDL_FreeSurface(m_5);
    SDL_FreeSurface(m_6);
    SDL_FreeSurface(m_7);
    SDL_FreeSurface(m_8);
    SDL_FreeSurface(m_9);

    SDL_FreeSurface(e_1);
    SDL_FreeSurface(e_2);
    SDL_FreeSurface(e_3);
    SDL_FreeSurface(e_4);
    SDL_FreeSurface(e_5);
    SDL_FreeSurface(e_6);
    SDL_FreeSurface(e_7);

    SDL_FreeSurface(E_1);
    SDL_FreeSurface(E_2);
    SDL_FreeSurface(E_3);
    SDL_FreeSurface(E_4);
    SDL_FreeSurface(E_5);
    SDL_FreeSurface(E_6);
    SDL_FreeSurface(E_7);
    SDL_FreeSurface(E_8);
    SDL_FreeSurface(E_9);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

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

void directions_panel(SDL_Renderer *ren, int x, int y){

    SDL_Texture *texture = NULL;
    SDL_Surface *Directions = IMG_Load("IMG/Directions.png");
    texture = SDL_CreateTextureFromSurface(ren,Directions);
    SDL_FreeSurface(Directions);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

int choix_direction(int mx, int my){
    if ( mx< 779 && mx> 731 && my>181 && my<229){
        return  1;
    }
    if ( mx< 829 && mx> 781 && my>181 && my<229){
        return  2;
    }
    if ( mx< 879 && mx> 831 && my>181 && my<229){
        return  3;
    }
    if ( mx< 779 && mx> 731 && my>131 && my<179){
        return  4;
    }
    if ( mx< 879 && mx> 831 && my>131 && my<179){
        return  6;
    }
    if ( mx< 779 && mx> 731 && my> 81 && my<189){
        return  7;
    }
    if ( mx< 829 && mx> 781 && my> 81 && my<189){
        return  8;
    }
    if ( mx< 879 && mx> 831 && my> 81 && my<189){
        return  9;
    }else{
        return  0;
    }
}

int choix_arme(int mx,int my){
    if ( mx<779 && mx>731 && my<349 && my>301){
        return 1; //button quadri shot
    }
    if ( mx<829 && mx>781 && my<349 && my>301){
        return 2; //button tir simple
    }
    if ( mx<879 && mx>831 && my<349 && my>301){
        return 3; //button bouclier
    }else{
        return 0;
    }
}

void tirer(SDL_Surface *Explosion,SDL_Renderer * ren,int set,int x,int y,int nbE,int *StatutE,int *dx,int *dy,int *xTankE,int *yTankE){

    SDL_Surface *m_1 = IMG_Load("IMG/missile1.png");
    SDL_Surface *m_2 = IMG_Load("IMG/missile2.png");
    SDL_Surface *m_3 = IMG_Load("IMG/missile3.png");
    SDL_Surface *m_4 = IMG_Load("IMG/missile4.png");
    SDL_Surface *m_5 = NULL;
    SDL_Surface *m_6 = IMG_Load("IMG/missile6.png");
    SDL_Surface *m_7 = IMG_Load("IMG/missile7.png");
    SDL_Surface *m_8 = IMG_Load("IMG/missile8.png");
    SDL_Surface *m_9 = IMG_Load("IMG/missile9.png");
    SDL_Surface* Missiles[9]= {m_1,m_2,m_3,m_4,m_5,m_6,m_7,m_8,m_9};
    SDL_Surface *e_1 = IMG_Load("IMG/case_explosion1.png");
    SDL_Surface *e_2 = IMG_Load("IMG/case_explosion2.png");
    SDL_Surface *e_3 = IMG_Load("IMG/case_explosion3.png");
    SDL_Surface *e_4 = IMG_Load("IMG/case_explosion4.png");
    SDL_Surface *e_5 = IMG_Load("IMG/case_explosion5.png");
    SDL_Surface *e_6 = IMG_Load("IMG/case_explosion6.png");
    SDL_Surface *e_7 = IMG_Load("IMG/case_explosion7.png");
    SDL_Surface* explosions[7]= {e_1,e_2,e_3,e_4,e_5,e_6,e_7};

    SDL_Surface* Missile = NULL;
    int xmissile=0;
    int ymissile=0;
    usleep(50000);
        Missile=Missiles[set-1];
        xmissile=x+dx[set-1];
        ymissile=y+dy[set-1];
        while(xmissile<=635 && xmissile>=25 && ymissile<=635 && ymissile>=25){
            fire(ren,Missile,xmissile,ymissile);
            SDL_RenderPresent(ren);  
            xmissile=xmissile+dx[set-1];
            ymissile=ymissile+dy[set-1];
            int s=0;
            for(s=0;s<nbE;s++){
                if(xmissile==xTankE[s] && ymissile==yTankE[s]){
                    xmissile = 2000;
                    ymissile = 2000;
                    int k;
                    for(k=0;k<7;k++){
                        Explosion = explosions[6-k];
                        fire(ren,Explosion,xTankE[s],yTankE[s]);
                        SDL_RenderPresent(ren);
                        usleep(75000);
                    }
                    StatutE[s]=1;
                }
            }
        }
}

void tirer4(SDL_Surface *Explosion,SDL_Renderer * ren,int set,int x,int y,int nbE,int *StatutE,int *dx,int *dy,int *xTankE,int *yTankE){

    SDL_Surface *m_1 = IMG_Load("IMG/missile1.png");
    SDL_Surface *m_2 = IMG_Load("IMG/missile2.png");
    SDL_Surface *m_3 = IMG_Load("IMG/missile3.png");
    SDL_Surface *m_4 = IMG_Load("IMG/missile4.png");
    SDL_Surface *m_5 = NULL;
    SDL_Surface *m_6 = IMG_Load("IMG/missile6.png");
    SDL_Surface *m_7 = IMG_Load("IMG/missile7.png");
    SDL_Surface *m_8 = IMG_Load("IMG/missile8.png");
    SDL_Surface *m_9 = IMG_Load("IMG/missile9.png");
    SDL_Surface* Missiles[9]= {m_1,m_2,m_3,m_4,m_5,m_6,m_7,m_8,m_9};
    SDL_Surface *e_1 = IMG_Load("IMG/case_explosion1.png");
    SDL_Surface *e_2 = IMG_Load("IMG/case_explosion2.png");
    SDL_Surface *e_3 = IMG_Load("IMG/case_explosion3.png");
    SDL_Surface *e_4 = IMG_Load("IMG/case_explosion4.png");
    SDL_Surface *e_5 = IMG_Load("IMG/case_explosion5.png");
    SDL_Surface *e_6 = IMG_Load("IMG/case_explosion6.png");
    SDL_Surface *e_7 = IMG_Load("IMG/case_explosion7.png");
    SDL_Surface* explosions[7]= {e_1,e_2,e_3,e_4,e_5,e_6,e_7};

    SDL_Surface* Missile1 = NULL;
    SDL_Surface* Missile2 = NULL;
    SDL_Surface* Missile3 = NULL;
    SDL_Surface* Missile4 = NULL;
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
    usleep(50000);
        Missile1=Missiles[set1-1];
        xmissile1=x+dx[set1-1];
        ymissile1=y+dy[set1-1];
        Missile2=Missiles[set2-1];
        xmissile2=x+dx[set2-1];
        ymissile2=y+dy[set2-1];
        Missile3=Missiles[set3-1];
        xmissile3=x+dx[set3-1];
        ymissile3=y+dy[set3-1];
        Missile4=Missiles[set4-1];
        xmissile4=x+dx[set4-1];
        ymissile4=y+dy[set4-1];
        while((xmissile1<=635 && xmissile1>=25 && ymissile1<=635 && ymissile1>=25) || (xmissile2<=635 && xmissile2>=25 && ymissile2<=635 && ymissile2>=25) || (xmissile3<=635 && xmissile3>=25 && ymissile3<=635 && ymissile3>=25) || (xmissile4<=635 && xmissile4>=25 && ymissile4<=635 && ymissile4>=25)){
            fire(ren,Missile1,xmissile1,ymissile1);
            fire(ren,Missile2,xmissile2,ymissile2);
            fire(ren,Missile3,xmissile3,ymissile3); 
            fire(ren,Missile4,xmissile4,ymissile4);
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
            for(s=0;s<nbE;s++){
                if(xmissile1==xTankE[s] && ymissile1==yTankE[s]){
                    xmissile1 = 2000;
                    ymissile1 = 2000;
                    int k;
                    for(k=0;k<7;k++){
                        Explosion = explosions[6-k];
                        fire(ren,Explosion,xTankE[s],yTankE[s]);
                        usleep(75000);
                    }
                    StatutE[s]=1;
                }
                if(xmissile2==xTankE[s] && ymissile2==yTankE[s]){
                    xmissile2 = 2000;
                    ymissile2 = 2000;
                    int k;
                    for(k=0;k<7;k++){
                        Explosion = explosions[6-k];
                        fire(ren,Explosion,xTankE[s],yTankE[s]);
                        usleep(75000);
                    }
                    StatutE[s]=1;
                }
                if(xmissile3==xTankE[s] && ymissile3==yTankE[s]){
                    xmissile3 = 2000;
                    ymissile3 = 2000;
                    int k;
                    for(k=0;k<7;k++){
                        Explosion = explosions[6-k];
                        fire(ren,Explosion,xTankE[s],yTankE[s]);
                        usleep(75000);
                    }
                    StatutE[s]=1;
                }
                if(xmissile4==xTankE[s] && ymissile4==yTankE[s]){
                    xmissile4 = 2000;
                    ymissile4 = 2000;
                    int k;
                    for(k=0;k<7;k++){
                        Explosion = explosions[6-k];
                        fire(ren,Explosion,xTankE[s],yTankE[s]);
                        usleep(75000);
                    }
                    StatutE[s]=1;
                }
                SDL_RenderPresent(ren);
            }
        }
}
