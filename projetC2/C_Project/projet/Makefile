OBJECTS=lv01.o background.o tank.o disponibilite.o case.o map.o attaque.o menu.o
FLAGS=-Wall -Wextra
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf
NAME=jeu

$(NAME): $(OBJECTS)
		gcc $(FLAGS) $(OBJECTS) -o $(NAME) $(LDFLAGS)

%.o: %.c
		gcc $(FLAGS) -c $<

clean:
		rm -f $(NAME)
		rm -f *.o *~

cleano:
		rm -f *.o *~
