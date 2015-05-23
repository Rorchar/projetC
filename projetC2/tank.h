#ifndef TANK
#define TANK

void mvt_tank(SDL_Renderer *ren, int x, int y, int orientation, int i);
int evite_mer(SDL_Window* win, int x, int y,int map[][13]);
void fire(SDL_Renderer *ren,SDL_Surface *Missile,int xmissile,int ymissile);
int Pos(int i,int a);
int PosE(int i,int a);
#endif