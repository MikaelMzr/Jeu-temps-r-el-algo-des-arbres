/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 26-04-2021 */
/* Dernière modification : 26-04-2021 */
#include "Graphique.h"

void efface(Niveau *niveau) {
	unsigned i, j;

	for(i = 1; i < niveau->taille.y + 2; i++) {
		for(j = 1; j < niveau->taille.x + 2; j++) {
			mvaddch(i, j, ' ');
		}
	}
}

void affiche_niveau_graphique(Niveau *niveau) {
	unsigned i, j;
	Deplacement d;

	efface(niveau);
	for(i = 0; i < niveau->taille.x + 2; i++) {
		mvaddch(0, i, '#');
		mvaddch(niveau->taille.y + 1, i, '#');
	}

	for(i = 1; i < niveau->taille.y + 1; i++) {
		mvaddch(i, 0, '#');
		mvaddch(i, niveau->taille.x + 1, '#');
	}

	for(i = 0; i < niveau->taille.y; i++) {
		for(j = 0; j < niveau->taille.x; j++) {
			switch(niveau->objets[i][j].type) {
				case VIDE: mvaddch(i + 1, j + 1, ' '); break;
				case LANCEUR: mvaddch(i + 1, j + 1, 'O'); break;
				case MUR: mvaddch(i + 1, j + 1, '#'); break;
				case PROJECTILE: d = * (Deplacement *) niveau->objets[i][j].donnee_suppl;
								 if(d.direction == HAUT)
								 	mvaddch(i + 1, j + 1, '^');
								 else if(d.direction == GAUCHE)
								 	mvaddch(i + 1, j + 1, '<');
								 else if(d.direction == BAS)
								 	mvaddch(i + 1, j + 1, 'v');
								 else
								 	mvaddch(i + 1, j + 1, '>');
								 break;
				case PERSONNAGE: mvaddch(i + 1, j + 1, 'P'); break;
				case DESTINATION: mvaddch(i + 1, j + 1, 'D'); break;
			}
		}
	}
}

void fenetre_fin(int est_mort) {
    clear();
    if(est_mort)
    	mvprintw(LINES / 2, COLS / 2 - 8, "Vous avez Perdu.");
    else
    	mvprintw(LINES / 2, COLS / 2 - 8, "Vous avez Gagné.");
    refresh();
    millisleep(2000);
}