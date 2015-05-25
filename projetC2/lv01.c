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
#include "attaque.h"


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
    window = SDL_CreateWindow("TankRider", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 720, SDL_WINDOW_SHOWN);
    ren =  SDL_CreateRenderer( window, 0, SDL_RENDERER_TARGETTEXTURE);
    
    //Initialisation de la position du curseur
    int MouseX = 0;
    int MouseY = 0;

    Menu(ren);

    int affichage_niv=0;

    //Ces 3 tab enregistrentles coords et le bouton qui est down
    //36 est un nombre quelconque, à redefinir en fonction des courte
    int xcible[10];
    int ycible[10];
    int d_on_tab[10];

    int o=0;
    int u=0;
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

    int lvl=0;

    //Nombre de fleche posée
    int nb=nbdispo(lvl);

    //bouclier
    int bouclier=0;
    int nbb=0;

    int nb_fleche[12];

    
    int ne=4;
    int nm=3;
    int jj=0;

    int xEnnemie[4];
    int yEnnemie[4];
    int setE[4];
    int StatutE[4]={0,0,0,0};

    int xMine[3];
    int yMine[3];
    int StatutM[3]={0,0,0};

    int x;
    int y;
    int set;
    

    //tableau de direction
    int dx[9]={-5,0,5,-5,0,5,-5,0,5};
    int dy[9]={5,5,5,0,0,0,-5,-5,-5};

    SDL_RenderPresent(ren);

    int action = 0; 

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
                if(lvl!=0 && lvl!=9){
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
                            for(u=0;u<12;u++){
                                nb_fleche[u]=dispo(lvl,u);
                            }
                            maj_panneau(ren,nb_fleche);
                            for(jj=0;jj<ne;jj++){
                                StatutE[jj]=0;
                                mvt_tank(ren, xEnnemie[jj],yEnnemie[jj],setE[jj], 0,bouclier);
                            }
                            for(jj=0;jj<nm;jj++){
                                StatutM[jj]=0;
                                mvt_tank(ren, xMine[jj],yMine[jj],2, 2,bouclier);
                            }
                            x = Pos(lvl,0);
                            y =Pos(lvl,1);;
                            set =Pos(lvl,2);
                            d_on=5;
                            arm_on=0;
                            nb=nbdispo(lvl);
                            na=0;
                            bouclier=0;
                            mvt_tank(ren,x,y,set,1,bouclier);
                            SDL_RenderPresent(ren);
                        }
                    }
                }else if(lvl==0){
                    if(affichage_niv==0 && MouseX>320 && MouseX<595 && MouseY<575 && MouseY>535){
                        lvl=1;
                        first_components_of_the_background(ren);
                        niv(lvl,ren);
                        x=Pos(lvl,0);
                        y=Pos(lvl,1);
                        set = Pos(lvl,2);
                        bouclier=0;
                        mvt_tank(ren,x,y,set,1,bouclier);
                        for(o=0;o<ne;o++){
                            xEnnemie[o] = PosE(lvl,3*o);
                            yEnnemie[o] = PosE(lvl,3*o+1);
                            setE[o]= PosE(lvl,3*o+2);
                            mvt_tank(ren, xEnnemie[o],yEnnemie[o], setE[o], 0,bouclier);
                            StatutE[o]=0;
                        }
                        for(o=0;o<nm;o++){
                            xMine[o] = PosM(lvl,2*o);
                            yMine[o] = PosM(lvl,2*o+1);
                            mvt_tank(ren, xMine[o],yMine[o], 2, 2,bouclier);
                            StatutM[o]=0;
                        }
                        for(u=0;u<12;u++){
                            nb_fleche[u]=dispo(lvl,u);
                        }
                        maj_panneau(ren,nb_fleche);
                        for(u=0;u<10;u++){
                            d_on_tab[u]=dispofleche(lvl,u,0);
                            xcible[u]=dispofleche(lvl,u,1);
                            ycible[u]=dispofleche(lvl,u,2);
                        }
                        nb=nbdispo(lvl);
                        na=0;
                    }
                    if(affichage_niv==1){
                        lvl= lecture_niv(MouseX, MouseY);
                        first_components_of_the_background(ren);
                        niv(lvl,ren);
                        x=Pos(lvl,0);
                        y=Pos(lvl,1);
                        set = Pos(lvl,2);
                        bouclier=0;
                        mvt_tank(ren,x,y,set,1,bouclier);
                        for(o=0;o<ne;o++){
                            xEnnemie[o] = PosE(lvl,3*o);
                            yEnnemie[o] = PosE(lvl,3*o+1);
                            setE[o]= PosE(lvl,3*o+2);
                            mvt_tank(ren, xEnnemie[o],yEnnemie[o], setE[o], 0,bouclier);
                            StatutE[o]=0;
                        }
                        for(o=0;o<nm;o++){
                            xMine[o] = PosM(lvl,2*o);
                            yMine[o] = PosM(lvl,2*o+1);
                            mvt_tank(ren, xMine[o],yMine[o], 2, 2,bouclier);
                            StatutM[o]=0;
                        }
                        for(u=0;u<12;u++){
                            nb_fleche[u]=dispo(lvl,u);
                        }
                        maj_panneau(ren,nb_fleche);
                        for(u=0;u<10;u++){
                            d_on_tab[u]=dispofleche(lvl,u,0);
                            xcible[u]=dispofleche(lvl,u,1);
                            ycible[u]=dispofleche(lvl,u,2);
                        }
                        nb=nbdispo(lvl);
                        na=0;
                    }
                    if(affichage_niv==0 && MouseX>370 && MouseX<560 && MouseY<630 && MouseY>595){//Bouton niv
                        affichage_niv = 1;
                        levels(ren);
                    }
                    
                }               
            break;
            case SDL_MOUSEBUTTONUP:
                if(lvl!=0 && lvl!=9){
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
                }
            break;
        }
        while (action==1 ){
            for(naj=0;naj<na;naj++){
                if(x+15==xtarget[naj] && y+15==ytarget[naj]){
                    if(arm_on_tab[naj]==1){
                        tirer4(ren,set,x,y,ne,nm,xEnnemie,yEnnemie,StatutE,xMine,yMine,StatutM);
                        usleep(50000);
                    }else if(arm_on_tab[naj]==2){
                        tirer(ren,set,x,y,ne,nm,xEnnemie,yEnnemie,StatutE,xMine,yMine,StatutM);
                        usleep(50000);
                    }else{
                        bouclier=1;
                    }
                }
            }
            niv(lvl,ren);
            for (o=0;o<ne;o++){
                if(StatutE[o]==0){
                   mvt_tank(ren, xEnnemie[o],yEnnemie[o], setE[o], 0,bouclier);
                } 
            }
            for (o=0;o<nm;o++){
                if(StatutM[o]==0){
                   mvt_tank(ren, xMine[o],yMine[o], 2, 2,bouclier);
                } 
            }
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

            x=x+dx[set-1];
            y=y+dy[set-1];
            //gestion du bouclier
            if(bouclier==1){
                nbb++;
                if(nbb==51){
                    bouclier=0;
                    nbb=0;
                }
            }
            action = evite_mer(window, x, y, lvl);
            mvt_tank(ren, x ,y,set ,1,bouclier); 
    
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

            if((x+15)==donne_drapeau(lvl,0) && (y+15)==donne_drapeau(lvl,1)){
                action=0;
                lvl++;
                if(lvl!=9){
                    niv(lvl,ren);
                    x=Pos(lvl,0);
                    y=Pos(lvl,1);
                    set = Pos(lvl,2);
                    bouclier=0;
                    mvt_tank(ren,x,y,set,1,bouclier);
                    for(o=0;o<ne;o++){
                        xEnnemie[o] = PosE(lvl,3*o);
                        yEnnemie[o] = PosE(lvl,3*o+1);
                        setE[o]= PosE(lvl,3*o+2);
                        mvt_tank(ren, xEnnemie[o],yEnnemie[o], setE[o], 0,bouclier);
                        StatutE[o]=0;
                    }
                    for(o=0;o<nm;o++){
                        xMine[o] = PosM(lvl,2*o);
                        yMine[o] = PosM(lvl,2*o+1);
                        mvt_tank(ren, xMine[o],yMine[o], 2, 2,bouclier);
                        StatutE[o]=0;
                    }
                    for(u=0;u<12;u++){
                        nb_fleche[u]=dispo(lvl,u);
                    }
                    maj_panneau(ren,nb_fleche);
                    for(u=0;u<10;u++){
                        d_on_tab[u]=dispofleche(lvl,u,0);
                        xcible[u]=dispofleche(lvl,u,1);
                        ycible[u]=dispofleche(lvl,u,2);
                    }
                    nb=nbdispo(lvl);
                    na=0;
                }else{
                    credits(ren);
                }
            }

            for(o=0;o<ne;o++){
                if (attaque_ennemi(x, y,xEnnemie[o],yEnnemie[o], setE[o]) && StatutE[o]==0 && bouclier==0){
                    tirerE(setE[o],xEnnemie[o],yEnnemie[o],x,y,ren);
                    SDL_ShowSimpleMessageBox(0, "HIT", "Vous etes mort", window);
                    action=0;
                }
            }
            for(o=0;o<nm;o++){
                if (attaque_mine(x, y,xMine[o],yMine[o]) && StatutM[o]==0 && bouclier==0){
                    tirerM(x,y,ren);
                    SDL_ShowSimpleMessageBox(0, "HIT", "Vous etes mort", window);
                    action=0;
                }
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
