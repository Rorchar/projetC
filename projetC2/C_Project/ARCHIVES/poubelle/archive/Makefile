OBJECTS=main.o tank.o ennemie.o casepose.o background.o
FLAGS=-Wall -Wextra
LDFLAGS=-lSDL2 -lSDL2_image
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
