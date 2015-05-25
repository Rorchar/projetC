#ifndef TANK
#define TANK

void mvt_tank(SDL_Renderer *ren, int x, int y, int orientation, int i,int bouclier);
int evite_mer(SDL_Window* win, int x, int y,int lvl);
int Pos(int i,int a);
int PosE(int i,int a);
int PosM(int i,int a);

#endif