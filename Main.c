/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 28-04-2021 */
/* Dernière modification : 17-05-2021 */
#include "Graphique.h"
#include "config_stdin.h"
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

int main () {
	Niveau* niveau;
	Tas* tas;
	Evenement e;
	int touche, depl_perso_autorise, est_mort, gagne;
	char version;

	niveau = niveau0();
	tas = construit_Tas(niveau);
	depl_perso_autorise = 1;
	est_mort = 0;
	gagne = 0;

	do {
		printf("Version Terminal ou Version Graphique(T ou G): ");
		scanf("%c", &version);
	} while(version != 'T' && version != 'G');

	/* Version Terminal. */
	if(version == 'T') {
		init_stdin();
		/* Tant que le personnage n'est pas mort ou qu'il n'a pas gagner. */
		while(!(est_mort || gagne)) {
			touche = getchar();

			if(depl_perso_autorise) {
				deplace_perso(tas, niveau, touche, &depl_perso_autorise, &est_mort, &gagne);	
			}
			if(un_evenement_est_pret(tas)) {
				e = ote_minimum(tas);
				execute_evenement(e, tas, niveau, &depl_perso_autorise, &est_mort);
				/*affiche_Tas(tas);*/
				affiche_Niveau(niveau);
			}
			/* Toujours attendre quelques millisecondes
			quand on ne fait pas grand chose (ici un
			seul test) dans la boucle. */
			else
				millisleep(10);
		}
		restaure_stdin();
		if(est_mort)
			printf("Vous avez Perdu.\n");
		else
			printf("Vous avez Gagné.\n");
	}
	/* Version Graphique. */
	else {
		initscr();
		noecho();
	    nodelay(stdscr, TRUE);
	    keypad(stdscr, TRUE);	
		/* Tant que le personnage n'est pas mort ou qu'il n'a pas gagner. */
		while(!(est_mort || gagne)) {
			touche = getch();

			if(depl_perso_autorise) {
				deplace_perso(tas, niveau, touche, &depl_perso_autorise, &est_mort, &gagne);	
			}
			if(un_evenement_est_pret(tas)) {
				e = ote_minimum(tas);
				execute_evenement(e, tas, niveau, &depl_perso_autorise, &est_mort);
				affiche_niveau_graphique(niveau);
				refresh();
			}
			/* Toujours attendre quelques millisecondes
			quand on ne fait pas grand chose (ici un
			seul test) dans la boucle. */
			else
				millisleep(10);
		}
		fenetre_fin(est_mort);
		endwin();
	}

	free_Niveau(niveau);
	free_Tas(tas);
	return 0;
}