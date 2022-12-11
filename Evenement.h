/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 13-04-2021 */
/* Dernière modification : 13-04-2021 */
#ifndef __EVENEMENT__H__
#define __EVENEMENT__H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> /* Definis le type bool */
#include "Niveau.h"
#include "Temps.h"

#define BLOC_ALLOC 10

typedef struct {
  unsigned long moment; /* Moment auquel evenement doit avoir lieu en
                         * nombre de "tick" du processeur
                         * Voir Gestion du temps */
  Coordonnees coo_obj; /* Objet affecte */
} Evenement;


typedef struct {
  unsigned taille;    /* Nombre d'Evenements contenus dans le tas */
  unsigned capacite;  /* Nombre de cases allouees pour les 
                       * `valeurs` (i.e. taille maximale) */
  Evenement* valeurs; /* Tableau d'Evenements de taille `capacite` et
                       * dont les `taille` premieres cases sont 
                       * utilisees. */
} Tas;

Tas* malloc_Tas(unsigned capacite_initiale);

void free_Tas(Tas* tas);

int environ_maintenant(unsigned long moment);

/* Renvoie 'true' si un evenement
 * doit etre effectue. */
bool un_evenement_est_pret(Tas* tas);

/* Renvoie et retire de ` tas `
 * l ' Evenement dont le ` moment ` est
 * le plus petit. */
Evenement ote_minimum(Tas* tas);

/* Compare le moment
 * de 2 évènements. */
int compare_moment(const void * premier, const void * second);

/* Ajoute un Evenement
 * a un Tas */
void ajoute_evenement(Tas* tas, Evenement n);

/* Construit un Tas contenant les
 * Evenements initiaux d ' un
 * Niveau */
Tas* construit_Tas(Niveau* niveau);

/* Affiche le contenu d ' un tas , a des
 * fins de tests */
void affiche_Tas(Tas* tas);

/* Déplace le perso dans le niveau. */
void deplace_perso(Tas* tas, Niveau* niveau, int touche, int *depl_perso_autorise, int *est_mort, int *gagne);

/* Execute un Evenement , ce qui peut consister a deplacer un
 * objet dans le Niveau , verifier si la partie est terminee ,
 * ajouter de nouveaux evenements au Tas , etc. */
void execute_evenement(Evenement e, Tas* tas, Niveau* niveau, int *depl_perso_autorise, int *est_mort);

#endif