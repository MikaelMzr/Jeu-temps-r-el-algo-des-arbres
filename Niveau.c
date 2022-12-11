/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 28-04-2021 */
/* Dernière modification : 28-04-2021 */
#include "Niveau.h"

Niveau* malloc_Niveau(Coordonnees taille) {
	Niveau* niveau;
	unsigned i;

	niveau = (Niveau*)malloc(sizeof(Niveau*));

	niveau->objets = (Objet**)malloc(sizeof(Objet*) * taille.y);
	for(i = 0; i < taille.y; i++)
		niveau->objets[i] = (Objet*)malloc(sizeof(Objet) * taille.x);
	niveau->allure_perso = (unsigned long)malloc(sizeof(unsigned long));

	return niveau;
}

void free_Niveau(Niveau* niveau) {
	unsigned i;

	if(niveau != NULL) {
		for(i = 0; i < niveau->taille.y; i++) {
			free(niveau->objets[i]);
			niveau->objets[i] = NULL;
		}
		/*free(niveau->objets);*/
		/*niveau->objets = NULL;*/
		free(niveau);
		niveau = NULL;
	}
}

Coordonnees lire_taille(char* nom_fichier) {
	Coordonnees taille;
	char caractere;
	FILE *f;

	f = fopen(nom_fichier, "r");

	taille.x = 0;
	taille.y = 1;
	while((caractere = fgetc(f)) != '\n') {
		taille.x++;
	}
	taille.x--;
	while((caractere = fgetc(f)) != EOF) {
		if(caractere == '\n')
			taille.y++;
	}

	fclose(f);
	return taille;
}

Niveau* niveau0() {
	FILE* f;
	char caractere;
	Niveau* niveau;
	Coordonnees taille;
	int x, y;

	taille = lire_taille("Niveau0.niv");

	f = fopen("Niveau0.niv", "r");

	niveau = malloc_Niveau(taille);
	niveau->taille = taille;

	x = 0;
	y = 0;
	while((caractere = fgetc(f)) != EOF) {
		if(caractere == '.') {
			niveau->objets[y][x].type = VIDE;
			niveau->objets[y][x].donnee_suppl = NULL;
		}
		else if(caractere == 'O') {
			niveau->objets[y][x].type = LANCEUR;
			niveau->objets[y][x].donnee_suppl = init_generation();
		}
		else if(caractere == '#') {
			niveau->objets[y][x].type = MUR;
			niveau->objets[y][x].donnee_suppl = NULL;
		}
		else if(caractere == 'P') {
			niveau->objets[y][x].type = PERSONNAGE;
			niveau->objets[y][x].donnee_suppl = NULL;
			niveau->coo_perso.x = x;
			niveau->coo_perso.y = y;
		}
		else if(caractere == 'D') {
			niveau->objets[y][x].type = DESTINATION;
			niveau->objets[y][x].donnee_suppl = NULL;
		}
		else if(caractere == '\n') {
			y++;
			x = 0;
		}
		if(caractere != '\n')
			x++;
	}

	niveau->allure_perso = 250;
	/*niveau->depl_perso_autorise = 1;*/

	fclose(f);
	return niveau;
}

void affiche_Niveau(Niveau* niveau) {
	unsigned i, j;
	Deplacement d;

	for(i = 0; i < niveau->taille.y; i++) {
		for(j = 0; j < niveau->taille.x; j++) {
			switch(niveau->objets[i][j].type) {
				case VIDE: printf("."); break;
				case LANCEUR: printf("O"); break;
				case MUR: printf("#"); break;
				case PROJECTILE: d = * (Deplacement *) niveau->objets[i][j].donnee_suppl;
								 if(d.direction == HAUT)
								 	printf("^");
								 else if(d.direction == GAUCHE)
								 	printf("<");
								 else if(d.direction == BAS)
								 	printf("v");
								 else
								 	printf(">");
								 break;
				case PERSONNAGE: printf("P"); break;
				case DESTINATION: printf("D"); break;
			}
		}
		printf("\n");
	}
}