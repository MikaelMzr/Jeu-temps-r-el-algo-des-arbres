/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 13-04-2021 */
/* Dernière modification : 13-04-2021 */
#ifndef __GRAPHIQUE__H__
#define __GRAPHIQUE__H__
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "Evenement.h"

void efface(Niveau *niveau);

void affiche_niveau_graphique(Niveau *niveau);

void fenetre_fin(int est_mort);

#endif