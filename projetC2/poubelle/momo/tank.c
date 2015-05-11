#include <stdio.h>


/*
The * and & operators are opposites.
The & operator takes a piece of data and tells where it's stored.
The * operator takes an adress and tells you what's stored there.
*/


void go_N (int *x, int  *y ){
	*x = *x;
	*y = *y + 1;
}
void go_NE(int *x, int  *y ){
	*x = *x+1;
	*y = *y+1;
}
void go_E (int *x, int  *y ){
	*x = *x+1;
	*y = *y;
}
void go_SE(int *x, int  *y ){
	*x = *x+1;
	*y = *y-1;
}
void go_S (int *x, int  *y ){
	*x = *x;
	*y = *y-1;
}
void go_SW(int *x, int  *y ){
	*x = *x-1;
	*y = *y-1;
}
void go_W (int *x, int  *y ){
	*x = *x-1;
	*y = *y;
}
void go_NW(int *x, int  *y ){
	*x = *x-1;
	*y = *y+1;
}


int main(){


	puts("\t\t\tWelcome");



	int pos_tX ;
	int pos_tY ;
	puts("Position Tank");
	scanf("%d", &pos_tX);
	scanf("%d", &pos_tY);
	printf("Le Tank se trouve en [%i , %i]\n", pos_tX , pos_tY);

	int pos_dX ;
	int pos_dY ;
	puts("Position Drapeau");
	scanf("%d", &pos_dX);
	scanf("%d", &pos_dY);
	printf("Le Drapeau se trouve [%i , %i]\n", pos_dX , pos_dY);

	puts("Commandant, quelles sont vos ordres");

	
	while (!((pos_dX==pos_tX) && (pos_dY==pos_tY))){
		int instrucution;
		scanf("%d" , &instrucution);
			switch(instrucution){
				case(8):go_N (&pos_tX, &pos_tY);break;
				case(9):go_NE(&pos_tX, &pos_tY);break;
				case(6):go_E (&pos_tX, &pos_tY);break;
				case(3):go_SE(&pos_tX, &pos_tY);break;
				case(2):go_S (&pos_tX, &pos_tY);break;
				case(1):go_SW(&pos_tX, &pos_tY);break;
				case(4):go_W (&pos_tX, &pos_tY);break;
				case(7):go_NW(&pos_tX, &pos_tY);break;
			}
		printf("Le Tank se trouve en [%i , %i]\n", pos_tX , pos_tY);
	}

	if((pos_dX==pos_tX) && (pos_dY==pos_tY)){
		puts("Mission réussie");
	}




	return 0;
}