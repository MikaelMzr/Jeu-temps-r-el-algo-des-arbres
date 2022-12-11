/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 28-04-2021 */
/* Dernière modification : 28-04-2021 */
#ifndef __NIVEAU__H__
#define __NIVEAU__H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> /* Definis le type bool */
#include "Objet.h"

typedef struct {
  unsigned x;
  unsigned y;
} Coordonnees;

typedef struct {
  Coordonnees taille; /* Taille du niveau */
  Objet** objets; /* Tableau bi-directionnel de largeur taille.x, 
                   * de hauteur taille.y, et dont chaque case 
                   * contient un Objet */
  Coordonnees coo_perso; /* Position actuelle du personnage. */
  unsigned long allure_perso; /* Allure du personnage */
  int depl_perso_autorise; /* Vaut `true` si  le temps ecoule
                             * depuis le dernier deplacement du
                             * personnage est superieur a son
                             * allure. */
} Niveau;

/* Effectue les malloc's pour obtenir un
 * Niveau* de la taille donnee. */
Niveau* malloc_Niveau(Coordonnees taille);

/* Libere la memoire prise par un Niveau. */
void free_Niveau(Niveau* niveau);

Coordonnees lire_taille(char* nom_fichier);

/* Cree le niveau 0 (Figure 1). */
Niveau* niveau0();

/* Affiche dans le terminal le
 * Niveau donnee en argument. */
void affiche_Niveau(Niveau* niveau);

#endif