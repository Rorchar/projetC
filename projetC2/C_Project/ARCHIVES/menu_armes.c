void weapons_panel(SDL_Renderer *ren, int x, int y){

	SDL_Texture *texture = NULL;
	SDL_Surface *weapons = IMG_Load("IMG/weapons.png"); //faire un menu avec les cases: bouclier, canon et 4shots de 50*50 pixels
	texture = SDL_CreateTextureFromSurface(ren,weapons);
	SDL_FreeSurface(weapons);
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, texture, NULL, &dst);
}

void small_weapons (SDL_Renderer *ren, int x, int y, int dd){
	SDL_Texture *texture = NULL;
	SDL_Surface *d = NULL;
	switch(dd){
		case(1):d = IMG_Load("IMG/bouclier.png");break;
		case(2):d = IMG_Load("IMG/canon.png");break;
		case(3):d = IMG_Load("IMG/4shots.png");break;
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

//mettre les bonnes valeurs pour le nouveau menu

int choix_armes(int mx, int my){
	if ( mx< 929 && mx> 881 && my>181 && my<229){ 
		return  1;
	}
	if ( mx< 979 && mx> 931 && my>181 && my<229){ 
		return  2;
	}
	if ( mx< 1029 && mx> 981 && my>181 && my<229){ 
		return  3;
	}else{
		return  0;
	}
}