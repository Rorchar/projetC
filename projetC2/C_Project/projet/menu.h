#ifndef MENU
#define MENU

void Menu(SDL_Renderer* ren);
void levels(SDL_Renderer* ren);
void credits(SDL_Renderer* ren);
int lecture_niv(int mx, int my);
void maj_titre(SDL_Window* window, int level);

#endif