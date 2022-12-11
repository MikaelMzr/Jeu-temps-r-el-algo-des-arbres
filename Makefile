# Dos Santos Loïc
# Mikael Mezouar
# Création : 28-04-2021
# Dernière modification : 28-04-2021
CC = gcc
CFLAGS = -ansi -Wall -Wextra -lncurses
OBJ = Main.o Graphique.o config_stdin.o Evenement.o Temps.o Niveau.o Objet.o Generation.o Deplacement.o

tempsreel: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test_config_stdin: test_config_stdin.c config_stdin.h
	$(CC) $(CFLAGS) test_config_stdin.c -o test_config_stdin

Main.o: Main.c Graphique.h config_stdin.h

Graphique.o: Graphique.c Graphique.h Evenement.h

config_stdin.o: config_stdin.c config_stdin.h

Evenement.o: Evenement.c Evenement.h Temps.h Niveau.h

Temps.o: Temps.c Temps.h

Niveau.o: Niveau.c Niveau.h Objet.h

Objet.o: Objet.c Objet.h Generation.h Deplacement.h

Generation.o: Generation.c Generation.h

Deplacement.o: Deplacement.c Deplacement.h


%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o