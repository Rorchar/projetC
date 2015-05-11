#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

void first_components_of_the_background (SDL_Renderer* renderer);

void carre_terre(SDL_Renderer *ren, int x, int y);

void mvt_tank(SDL_Surface *Tank_i, SDL_Renderer *ren, int x, int y );

void fond_terre(SDL_Renderer* renderer,int xdrapeau,int ydrapeau); // updates

void directions_panel(SDL_Renderer *ren, int x, int y);

void small_direction (SDL_Renderer *ren, int x, int y, int dd);

int choix_direction(int mx, int my);

int main(int argc, char *argv[]){

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
       SDL_Surface* Tank = NULL;
   
    SDL_Event event;
    int ON = 1;
    
    //Initialisation
    //Ajouter la gestion de l'erreur
    SDL_Init(SDL_INIT_VIDEO);  
    IMG_Init(IMG_INIT_PNG);

    //Génération de la fenêtre  
    window = SDL_CreateWindow("TankRider : Level 00", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 720, SDL_WINDOW_SHOWN);
    renderer =  SDL_CreateRenderer( window, 0, SDL_RENDERER_TARGETTEXTURE);
    int xdrapeau=535;
    int ydrapeau=535;
    first_components_of_the_background (renderer);

    fond_terre(renderer,xdrapeau,ydrapeau);


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

    //Coord du premier Tank
    int x = 35;
    int y = 35;
    //Orientation du premier Tank
    Tank = t_6;

    //Affichage du Premier tank
    mvt_tank(Tank,renderer,x,y);
    

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
    int d_on = 0;

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
                d_on = choix_direction(MouseX,MouseY);
            break;
            case SDL_MOUSEBUTTONUP:
            //#### AJOUTER LA RESTRICTION DE LA POSITION DE LA FLECHE  ########
                if (event.button.button == SDL_BUTTON_LEFT){
                    //Placement dans "la grille"
                    //Pas encore dessinée
                    if(MouseX<735 && MouseX>35 && MouseY< 735 && MouseY>35 ){
                    xcible[nb]= 35+50*((MouseX/50)-1);
                    ycible[nb]= 35+50*((MouseY/50)-1);
                    d_on_tab[nb]=d_on;
                    small_direction (renderer,xcible[nb],ycible[nb],d_on_tab[nb]);
                    nb++;
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

            fond_terre(renderer,xdrapeau,ydrapeau);

            Tank = Tanks[set-1];

            fond_terre(renderer,xdrapeau,ydrapeau);

            for(nbj = 0; nbj<nb;nbj++){
                if(nb!=0){
                    small_direction (renderer,xcible[nbj],ycible[nbj],d_on_tab[nbj]);
                }
            }

            x=x+dx[set-1];
            y=y+dy[set-1];

            mvt_tank(Tank,renderer, x ,y);

            if((x==635 || x==25 || y==635 || y==25)){ //borne a verifier
                action=0;
                SDL_ShowSimpleMessageBox(0, "out", "vous etes hors champs ", window);
            }
        
            for(nbj=0;nbj<nb;nbj++){
                if(x==xcible[nbj] && y==ycible[nbj]){
                    set= d_on_tab[nbj];    
                }
            }

            if(x==xdrapeau && y==ydrapeau){
                action=0;
                SDL_ShowSimpleMessageBox(0, "WIN", "vous avez terminez le niveau 0 ", window);
            }              
        }
    }


    SDL_FreeSurface(Tank);    //tableau de direction

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void first_components_of_the_background (SDL_Renderer* renderer){

    //coloration de toutes la fenetes en blanc
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 0 );
    SDL_Rect rect_BaseBackground;    rect_BaseBackground.x = 0;    rect_BaseBackground.y = 0;    rect_BaseBackground.w = 900;    rect_BaseBackground.h = 720;
    SDL_RenderFillRect( renderer, &rect_BaseBackground );
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor( renderer, 120, 165, 255, 0 );
    SDL_Rect rect_G;    rect_G.x = 10;    rect_G.y = 10;    rect_G.w = 700;    rect_G.h = 700;
    SDL_RenderFillRect( renderer, &rect_G );
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor( renderer, 213, 196, 128, 0);
    SDL_Rect rect_D;    rect_D.x = 720;    rect_D.y = 10;    rect_D.w = 170;    rect_D.h = 700;
    SDL_RenderFillRect( renderer, &rect_D );
    SDL_RenderPresent(renderer);

    //Placement du bouton start
    SDL_Texture *texture_start = NULL;
    SDL_Surface *start = IMG_Load("IMG/start.png");
    texture_start = SDL_CreateTextureFromSurface(renderer, start);
    SDL_FreeSurface(start);
    SDL_Rect dst_start;
    dst_start.x = 730;
    dst_start.y = 600;
    SDL_QueryTexture(texture_start, NULL, NULL, &dst_start.w, &dst_start.h);
    SDL_RenderCopy(renderer, texture_start, NULL, &dst_start);
    SDL_RenderPresent(renderer);

    //Placement du direction_pannel
    //En changeant les coordonnées(730,80), il faut updater ##choix_direction
    SDL_Texture *texture_directions = NULL;
    SDL_Surface *Directions = IMG_Load("IMG/Directions.png");
    texture_directions = SDL_CreateTextureFromSurface(renderer,Directions);
    SDL_FreeSurface(Directions);
    SDL_Rect dst_directions;
    dst_directions.x = 730;
    dst_directions.y = 80;
    SDL_QueryTexture(texture_directions, NULL, NULL, &dst_directions.w, &dst_directions.h);
    SDL_RenderCopy(renderer, texture_directions, NULL, &dst_directions);
    SDL_RenderPresent(renderer);
}

void carre_terre(SDL_Renderer *ren, int x, int y){
    SDL_Texture *texture = NULL;
    SDL_Surface *terre5050 = IMG_Load("IMG/Base_terre.png");
    texture = SDL_CreateTextureFromSurface(ren, terre5050);
    SDL_FreeSurface(terre5050);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
}

void mvt_tank(SDL_Surface *Tank_i, SDL_Renderer *ren, int x, int y ){
    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(ren, Tank_i);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_RenderPresent(ren);
}

void fond_terre(SDL_Renderer* ren,int xdrapeau,int ydrapeau){
    int jx, jy;
    for(jx = 0; jx<13;jx++){
        for(jy = 0; jy<13;jy++){
            carre_terre(ren, 35+50*jx, 35+50*jy);
        }
    }
    //Placement drapeau

    SDL_Texture *texture_drapeau = NULL;
    SDL_Surface *Drapeau = NULL;
    Drapeau = IMG_Load("IMG/case_drapeau.png");
    texture_drapeau = SDL_CreateTextureFromSurface(ren,Drapeau);
    SDL_FreeSurface(Drapeau);
    SDL_Rect dst_drapeau;
    dst_drapeau.x = xdrapeau;
    dst_drapeau.y = ydrapeau;
    SDL_QueryTexture(texture_drapeau, NULL, NULL, &dst_drapeau.w, &dst_drapeau.h);
    SDL_RenderCopy(ren, texture_drapeau, NULL, &dst_drapeau);
    SDL_RenderPresent(ren);
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
    SDL_RenderPresent(ren);
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
