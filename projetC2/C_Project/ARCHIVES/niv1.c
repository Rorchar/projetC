#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <unistd.h>

void first_components_of_the_background (SDL_Renderer* ren);

void mvt_tank(SDL_Surface *Tank_i, SDL_Renderer *ren, int x, int y );

void fond_terre(SDL_Renderer* ren,int xdrapeau,int ydrapeau); // updates

void directions_panel(SDL_Renderer *ren, int x, int y);

void small_direction (SDL_Renderer *ren, int x, int y, int dd);

void case_tir (SDL_Renderer *ren, int x, int y, int dd);

int choix_direction(int mx, int my);

int choix_arme(int mx,int my);

void fire(SDL_Renderer *ren,SDL_Surface *Missile,int set,int xmissile,int ymissile,int dx,int dy);

int main(){

    SDL_Window* window = NULL;
    SDL_Renderer* ren = NULL;
    SDL_Surface* Tank = NULL;
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
    int xdrapeau=535;
    int ydrapeau=535;
    first_components_of_the_background (ren);

    fond_terre(ren,xdrapeau,ydrapeau);


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

    //Coord du premier Tank
    int x = 35;
    int y = 35;
    //Orientation du premier Tank
    Tank = t_6;

    //Affichage du Premier tank
    mvt_tank(Tank,ren,x,y);

    SDL_RenderPresent(ren);
    

    //Initialisation de la position du curseur
    int MouseX = 0;
    int MouseY = 0;
    
    //Ces 3 tab enregistrentles coords et le bouton qui est down
    //36 est un nombre quelconque, à redefinir en fonction des courte
    int xcible[36];
    int ycible[36];
    int d_on_tab[36];
    
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
            case SDL_MOUSEBUTTONUP:
            //#### AJOUTER LA RESTRICTION DE LA POSITION DE LA FLECHE  ########
                if (event.button.button == SDL_BUTTON_LEFT){
                    //Placement dans "la grille"
                    //Pas encore dessinée
                    if(MouseX<635 && MouseX>25 && MouseY< 635 && MouseY>25 ){
                        if(d_on!=0){
                            xcible[nb]= 35+50*((MouseX/50)-1);
                            ycible[nb]= 35+50*((MouseY/50)-1);
                            d_on_tab[nb]=d_on;
                            d_on=0;
                            small_direction (ren,xcible[nb],ycible[nb],d_on_tab[nb]);
                            nb++;
                        }
                        if(arm_on!=0){
                            xtarget[na]= 35+50*((MouseX/50)-1);
                            ytarget[na]= 35+50*((MouseY/50)-1);
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


        //}
        while (action==1){    

            Tank = Tanks[set-1];

            fond_terre(ren,xdrapeau,ydrapeau);

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

            mvt_tank(Tank,ren, x ,y);

            SDL_RenderPresent(ren);

            if((x==635 || x==25 || y==635 || y==25)){ //borne a verifier
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
                    Missile=Missiles[set-1];
                    fire(ren,Missile,set,x,y,dx,dy);   
                }
            }
            if(x==xdrapeau && y==ydrapeau){
                action=0;
                SDL_ShowSimpleMessageBox(0, "WIN", "niv1 terminer ", window);
            } 

            usleep(15000);          
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

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void first_components_of_the_background (SDL_Renderer* ren){

    //coloration de toutes la fenetes en blanc
    SDL_SetRenderDrawColor( ren, 255, 255, 255, 0 );
    SDL_Rect rect_BaseBackground;    rect_BaseBackground.x = 0;    rect_BaseBackground.y = 0;    rect_BaseBackground.w = 900;    rect_BaseBackground.h = 720;
    SDL_RenderFillRect( ren, &rect_BaseBackground );
    

    SDL_SetRenderDrawColor( ren, 0, 0, 0, 0 );
    SDL_Rect rect_G;    rect_G.x = 10;    rect_G.y = 10;    rect_G.w = 700;    rect_G.h = 700;
    SDL_RenderFillRect( ren, &rect_G );
    

    SDL_SetRenderDrawColor( ren, 213, 196, 128, 0);
    SDL_Rect rect_D;    rect_D.x = 720;    rect_D.y = 10;    rect_D.w = 170;    rect_D.h = 700;
    SDL_RenderFillRect( ren, &rect_D );

    //Placement du bouton start
    SDL_Texture *texture_start = NULL;
    SDL_Surface *start = IMG_Load("IMG/start.png");
    texture_start = SDL_CreateTextureFromSurface(ren, start);
    SDL_FreeSurface(start);
    SDL_Rect dst_start;
    dst_start.x = 730;
    dst_start.y = 600;
    SDL_QueryTexture(texture_start, NULL, NULL, &dst_start.w, &dst_start.h);
    SDL_RenderCopy(ren, texture_start, NULL, &dst_start);
    SDL_DestroyTexture(texture_start);


    //Placement du direction_pannel
    //En changeant les coordonnées(730,80), il faut updater ##choix_direction
    SDL_Texture *texture_directions = NULL;
    SDL_Surface *Directions = IMG_Load("IMG/Directions.png");
    texture_directions = SDL_CreateTextureFromSurface(ren,Directions);
    SDL_FreeSurface(Directions);
    SDL_Rect dst_directions;
    dst_directions.x = 730;
    dst_directions.y = 80;
    SDL_QueryTexture(texture_directions, NULL, NULL, &dst_directions.w, &dst_directions.h);
    SDL_RenderCopy(ren, texture_directions, NULL, &dst_directions);
    SDL_DestroyTexture(texture_directions);

    //Placement des cases tirs
    SDL_Texture *texture_tir1 = NULL;
    SDL_Surface *Tir1 = IMG_Load("IMG/t1f.png");
    texture_tir1 = SDL_CreateTextureFromSurface(ren,Tir1);
    SDL_FreeSurface(Tir1);
    SDL_Rect shot1;
    shot1.x = 730;
    shot1.y = 300;
    SDL_QueryTexture(texture_tir1, NULL, NULL, &shot1.w, &shot1.h);
    SDL_RenderCopy(ren, texture_tir1, NULL, &shot1);
    SDL_DestroyTexture(texture_tir1);

    SDL_Texture *texture_tir2 = NULL;
    SDL_Surface *Tir2 = IMG_Load("IMG/t1f.png");
    texture_tir2 = SDL_CreateTextureFromSurface(ren,Tir2);
    SDL_FreeSurface(Tir2);
    SDL_Rect shot2;
    shot2.x = 780;
    shot2.y = 300;
    SDL_QueryTexture(texture_tir2, NULL, NULL, &shot2.w, &shot2.h);
    SDL_RenderCopy(ren, texture_tir2, NULL, &shot2);
    SDL_DestroyTexture(texture_tir2);

    SDL_Texture *texture_tir3 = NULL;
    SDL_Surface *Tir3 = IMG_Load("IMG/t3f.png");
    texture_tir3 = SDL_CreateTextureFromSurface(ren,Tir3);
    SDL_FreeSurface(Tir3);
    SDL_Rect shot3;
    shot3.x = 830;
    shot3.y = 300;
    SDL_QueryTexture(texture_tir3, NULL, NULL, &shot3.w, &shot3.h);
    SDL_RenderCopy(ren, texture_tir3, NULL, &shot3);
    SDL_DestroyTexture(texture_tir3);

    SDL_RenderPresent(ren);
}

void mvt_tank(SDL_Surface *Tank_i, SDL_Renderer *ren, int x, int y ){
    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(ren, Tank_i);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

void fire(SDL_Renderer *ren,SDL_Surface *Missile,int set,int xmissile,int ymissile,int dx,int dy){
    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(ren, Missile);
    SDL_Rect dst;
    dst.x = xmissile+dx[set-1];
    dst.y = ymissile+dy[set-1];
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(ren);
    if (!(x==635 || x==25 || y==635 || y==25)){
        Missile=Missiles[set-1];
        fire(ren,Missile,set,dst.x,dst.y,dx,dy);
    }


}
void fond_terre(SDL_Renderer* ren,int xdrapeau,int ydrapeau){
    //int jx, jy;
    //for(jx = 0; jx<13;jx++){
    //    for(jy = 0; jy<13;jy++){
    //       if(35+50*jx!=xdrapeau || 35+50*jy!=ydrapeau)
    //       carre_terre(ren, 35+50*jx, 35+50*jy);
    //    }
    //}

    SDL_Texture *texture_map1 = NULL;
    SDL_Surface *map1= IMG_Load("IMG/map1.png");
    texture_map1 = SDL_CreateTextureFromSurface(ren,map1);
    SDL_FreeSurface(map1);
    SDL_Rect lv1;
    lv1.x = 35;
    lv1.y = 35;
    SDL_QueryTexture(texture_map1, NULL, NULL, &lv1.w, &lv1.h);
    SDL_RenderCopy(ren, texture_map1, NULL, &lv1);
    SDL_DestroyTexture(texture_map1);

    //Placement drapeau
    SDL_Texture *texture_drapeau = NULL;
    SDL_Surface *Drapeau = IMG_Load("IMG/case_drapeau.png");
    texture_drapeau = SDL_CreateTextureFromSurface(ren,Drapeau);
    SDL_FreeSurface(Drapeau);
    SDL_Rect dst_drapeau;
    dst_drapeau.x = xdrapeau;
    dst_drapeau.y = ydrapeau;
    SDL_QueryTexture(texture_drapeau, NULL, NULL, &dst_drapeau.w, &dst_drapeau.h);
    SDL_RenderCopy(ren, texture_drapeau, NULL, &dst_drapeau);
    SDL_DestroyTexture(texture_drapeau);
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

void small_direction (SDL_Renderer *ren, int x, int y, int dd){
    SDL_Texture *texture = NULL;
    SDL_Surface *d = NULL;
    switch(dd){
        case(1):d = IMG_Load("IMG/d1.png");break;
        case(2):d = IMG_Load("IMG/d2.png");break;
        case(3):d = IMG_Load("IMG/d3.png");break;
        case(4):d = IMG_Load("IMG/d4.png");break;
        case(6):d = IMG_Load("IMG/d6.png");break;
        case(7):d = IMG_Load("IMG/d7.png");break;
        case(8):d = IMG_Load("IMG/d8.png");break;
        case(9):d = IMG_Load("IMG/d9.png");break;
    }
    texture = SDL_CreateTextureFromSurface(ren,d);
    SDL_FreeSurface(d);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}

void case_tir (SDL_Renderer *ren, int x, int y, int dd){
    SDL_Texture *texture = NULL;
    SDL_Surface *d = NULL;
    switch(dd){
        case(1):d = IMG_Load("IMG/t1.png");break;
        case(2):d = IMG_Load("IMG/t1.png");break;
        case(3):d = IMG_Load("IMG/t3.png");break;
    }
    texture = SDL_CreateTextureFromSurface(ren,d);
    SDL_FreeSurface(d);
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
