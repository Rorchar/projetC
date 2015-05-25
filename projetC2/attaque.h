#ifndef ATTAQUE
#define ATTAQUE

void fire(SDL_Renderer *ren,SDL_Surface *Missile,int xmissile,int ymissile);
bool attaque_ennemi(int x, int y,int xE, int yE, int setE);
bool attaque_mine(int x, int y,int xM, int yM);
void tirerE(int setE,int xE,int yE,int x,int y,SDL_Renderer* ren);
void tirerM(int x,int y,SDL_Renderer* ren);
void tirer(SDL_Renderer* ren,int set,int x,int y,int ne,int nm,int xEnnemie[],int yEnnemie[],int StatutE[],int xMine[],int yMine[],int StatueM[]);
void tirer4(SDL_Renderer* ren,int set,int x,int y,int ne,int nm,int xEnnemie[],int yEnnemie[],int StatutE[],int xMine[],int yMine[],int StatueM[]);

#endif