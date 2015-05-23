#ifndef DISPO
#define DISPO

void affichage_nb(SDL_Renderer *ren, int x, int y, int i);
void maj_panneau(SDL_Renderer* ren, int nb_fleche[]);
int dispo(int lvl,int u);
int dispofleche(int lvl,int u,int i);
int nbdispo(int lvl);

#endif