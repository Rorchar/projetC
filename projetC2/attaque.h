#ifndef ATTAQUE
#define ATTAQUE

void fire(SDL_Renderer *ren,SDL_Surface *Missile,int xmissile,int ymissile);
bool attaque_ennemi(int x, int y,int xE, int yE, int setE);
void tirerE(int setE,int xE,int yE,int x,int y,SDL_Renderer* ren);
void tirer(SDL_Renderer* ren,int set,int x,int y,int ne,int xEnnemie[],int yEnnemie[],int StatutE[]);

#endif