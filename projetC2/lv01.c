#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdbool.h>
#include <unistd.h>

void first_components_of_the_background (SDL_Renderer* ren);
void carte(SDL_Renderer* ren, int map[][13],int Drapeau[]);
void mvt_tank(SDL_Renderer *ren, int x, int y, int orientation, int i);
void affichage_nb(SDL_Renderer *ren, int x, int y, int i);
int evite_mer(SDL_Window* win, int x, int y,int map[][13]);
void small_direction (SDL_Renderer *ren, int x, int y, int dd);
int choix_direction(int mx, int my);
void maj_panneau(SDL_Renderer* ren, int nb_fleche[]);
void fire(SDL_Renderer *ren,SDL_Surface *Missile,int xmissile,int ymissile);
bool attaque_ennemi(int x, int y,int set, int xE, int yE, int setE);

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

    //Génération de la fenêtre  
    window = SDL_CreateWindow("TankRider : Level 00", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 720, SDL_WINDOW_SHOWN);
    ren =  SDL_CreateRenderer( window, 0, SDL_RENDERER_TARGETTEXTURE);
    
    //Initialisation de la position du curseur
    int MouseX = 0;
    int MouseY = 0;
    
    //Drapeau
    int Drapeau[2]={385,635};

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
    int d_on ;

    first_components_of_the_background(ren);
    carte(ren,map01,Drapeau);

    int nb_fleche[9]={0,2,0,1,0,1,0,0,0};
    maj_panneau(ren,nb_fleche);
    
   
    int xE = 220;
    int yE = 170 ;
    int setE=6;
    mvt_tank(ren, xE,yE, setE, 0);

    int x = 320;
    int y = 20;
    int set = 2;
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
                    if(nb_fleche[d_on-1]>=0){
                        nb_fleche[d_on-1]=(nb_fleche[d_on-1])-1;
                        maj_panneau(ren,nb_fleche);
                    }
                }
                if (event.button.button == SDL_BUTTON_LEFT){
                    if(MouseX>731 && MouseX<879 && MouseY>531 && MouseY<579){//BOUTON START
                        action = 1;
                    }
                    if(MouseX>731 && MouseX<879 && MouseY>601 && MouseY<649){//BOUTON RESET
                        carte(ren,map01,Drapeau);
                        nb_fleche[0]= 0;
                        nb_fleche[1]= 2;
                        nb_fleche[2]= 0;
                        nb_fleche[3]= 1;
                        nb_fleche[4]= 0;
                        nb_fleche[5]= 1;
                        nb_fleche[6]= 0;
                        nb_fleche[7]= 0;
                        nb_fleche[8]= 0;
                        maj_panneau(ren,nb_fleche);
                        mvt_tank(ren, xE,yE, setE, 0);
                        x = 320;
                        y = 20;
                        set = 2;
                        nb=0;
                        mvt_tank(ren,x,y,set,1);
                        SDL_RenderPresent(ren);
                    }
                }                
            break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT){
                    if(MouseX<685 && MouseX>38 && MouseY< 685 && MouseY>38 ){
                        if(d_on!=5 ){
                            if((nb_fleche[d_on-1])>(-1)){
                            xcible[nb]= 35+50*(((MouseX+12)/50)-1);
                            ycible[nb]= 35+50*(((MouseY+12)/50)-1);
                            d_on_tab[nb]=d_on;
                            d_on=5;
                                small_direction (ren,xcible[nb],ycible[nb],d_on_tab[nb]);
                                nb++;
                            }
                            
                        }
                        SDL_RenderPresent(ren);
                    }
                }
            break;
        }
        while (action==1 ){
        
            carte(ren,map01,Drapeau);
            mvt_tank(ren, 220,170, 6, 0);

            for(nbj = 0; nbj<nb;nbj++){
                if(nb!=0){
                    small_direction (ren,xcible[nbj],ycible[nbj],d_on_tab[nbj]);
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
                SDL_ShowSimpleMessageBox(0, "WIN", "niv1 terminer ", window);
            }

            if (attaque_ennemi(x, y, set, xE, yE, setE)){
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

void first_components_of_the_background (SDL_Renderer* ren){

    //coloration de toutes la fenetes en blanc
    SDL_SetRenderDrawColor( ren, 255, 255, 255, 0 );
    SDL_Rect rect_BaseBackground;    rect_BaseBackground.x = 0;    rect_BaseBackground.y = 0;    rect_BaseBackground.w = 900;    rect_BaseBackground.h = 720;
    SDL_RenderFillRect( ren, &rect_BaseBackground );

    SDL_SetRenderDrawColor( ren,0, 0, 0, 0 );
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
    dst_start.y = 530;
    SDL_QueryTexture(texture_start, NULL, NULL, &dst_start.w, &dst_start.h);
    SDL_RenderCopy(ren, texture_start, NULL, &dst_start);
    SDL_DestroyTexture(texture_start);

    //Placement du bouton reset
    SDL_Texture *texture_reset = NULL;
    SDL_Surface *reset = IMG_Load("IMG/reset.png");
    texture_reset = SDL_CreateTextureFromSurface(ren, reset);
    SDL_FreeSurface(reset);
    SDL_Rect dst_reset;
    dst_reset.x = 730;
    dst_reset.y = 600;
    SDL_QueryTexture(texture_reset, NULL, NULL, &dst_reset.w, &dst_reset.h);
    SDL_RenderCopy(ren, texture_reset, NULL, &dst_reset);
    SDL_DestroyTexture(texture_reset);

    SDL_RenderPresent(ren);
}
void carte(SDL_Renderer* ren, int map[][13],int Drapeau[]){

    SDL_Surface *d = NULL;

    int i,j;
    for(i=0;i<13;i++){
        for(j=0;j<13;j++){
            switch(map[j][i]){
                case(0):d = IMG_Load("IMG/Maps/mersamere.png");break;
                case(1):d = IMG_Load("IMG/Maps/terresamer.png");break;
                case(2):d = IMG_Load("IMG/Maps/bonshitsamere.png");break;
                case(3):d = IMG_Load("IMG/Maps/hm).png");break;
                case(4):d = IMG_Load("IMG/Maps/l4.png");break;
                case(5):d = IMG_Load("IMG/Maps/graviasse.png");break;
                case(6):d = IMG_Load("IMG/Maps/l6.png");break;
                case(7):d = IMG_Load("IMG/Maps/diago(5)(1).png");break;
                case(8):d = IMG_Load("IMG/Maps/l8.png");break;
                case(9):d = IMG_Load("IMG/Maps/herbe-mer_1).png");break;
                case(10):d = IMG_Load("IMG/Maps/l2.png");break;
                case(11):d = IMG_Load("IMG/Maps/l1(.png");break;
                case(12):d = IMG_Load("IMG/Maps/base_pont.png");break;
                case(13):d = IMG_Load("IMG/Maps/coin_mer-terre1(.png");break;
                case(14):d = IMG_Load("IMG/Maps/fleurblanche.png");break;
                case(15):d = IMG_Load("IMG/Maps/fleurbleue.png");break;
                case(16):d = IMG_Load("IMG/Maps/herbe-mer_1(.png");break;
            }
            SDL_Texture *texture  = SDL_CreateTextureFromSurface(ren,d);
            SDL_FreeSurface(d);
            SDL_Rect dst;
            dst.x = 35+(50*i);
            dst.y = 35+(50*j);
            dst.h = 50;
            dst.w = 50;
            SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
            SDL_RenderCopy(ren, texture, NULL, &dst);
            SDL_DestroyTexture(texture);
        }
    }
    //Placement drapeau
    SDL_Texture *texture_drapeau = NULL;
    SDL_Surface *drapeau = IMG_Load("IMG/case_drapeau.png");
    texture_drapeau = SDL_CreateTextureFromSurface(ren,drapeau);
    SDL_FreeSurface(drapeau);
    SDL_Rect dst_drapeau;
    dst_drapeau.x = Drapeau[0];
    dst_drapeau.y = Drapeau[1];
    SDL_QueryTexture(texture_drapeau, NULL, NULL, &dst_drapeau.w, &dst_drapeau.h);
    SDL_RenderCopy(ren, texture_drapeau, NULL, &dst_drapeau);
    SDL_DestroyTexture(texture_drapeau);
}
void mvt_tank(SDL_Renderer *ren, int x, int y, int orientation, int i){
    int angles[] ={0,45,90,-45,0,135,-90,-135,180};
    SDL_Texture *texture = NULL;
    SDL_Surface *t = NULL;
    if(i==1){
        t = IMG_Load("IMG/tank1.png");
    }else{
        t = IMG_Load("IMG/ennemie1.png");
    }
    SDL_Surface *Tank = rotozoomSurface(t,angles[orientation-1], 1, 1);
    texture = SDL_CreateTextureFromSurface(ren, Tank);
    SDL_FreeSurface(t);
    SDL_FreeSurface(Tank);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
}
void affichage_nb(SDL_Renderer *ren, int x, int y, int i){
    SDL_Color textColor = {0,0,0 ,0};
    TTF_Font *font = TTF_OpenFont( "TTF/Amelia_BT.ttf", 18 );
    char s[1]; // Nombre maximal de chiffres + 1
    sprintf(s, "%d", i);
    SDL_Surface *message = TTF_RenderText_Solid( font,s, textColor );
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, message);
    SDL_FreeSurface(message);
    SDL_Rect text;
    text.x = x;
    text.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &text.w, &text.h);
    SDL_RenderCopy(ren, texture, NULL, &text);
    SDL_DestroyTexture(texture);
}
int evite_mer(SDL_Window* win, int x, int y,int map[][13]){
    int mx = (x-20)/50; //Pour map ou matrice
    int my = (y-20)/50;
    if(map[my][mx]==0||map[my][mx]==8 || map[my][mx]==9||map[my][mx]==4 || map[my][mx]==3){
        SDL_ShowSimpleMessageBox(0, "Oooops", "Pas possible d'avancer d'avantage ", win);
        return 0;
    }else{
        return 1;
    }
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
        return  5;
    }
}
void maj_panneau(SDL_Renderer* ren, int nb_fleche[]){

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

    affichage_nb(ren,768,210,nb_fleche[0]);//d1
    affichage_nb(ren,818,210,nb_fleche[1]);//d2
    affichage_nb(ren,868,210,nb_fleche[2]);//d3
    affichage_nb(ren,768,160,nb_fleche[3]);//d4
    affichage_nb(ren,868,160,nb_fleche[5]);//d6
    affichage_nb(ren,768,110,nb_fleche[6]);//d7
    affichage_nb(ren,818,110,nb_fleche[7]);//d8
    affichage_nb(ren,868,110,nb_fleche[8]);//d9
    
    SDL_RenderPresent(ren);
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

bool attaque_ennemi(int x, int y,int set, int xE, int yE, int setE){
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
