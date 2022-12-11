/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 28-04-2021 */
/* Dernière modification : 30-04-2021 */
#ifndef __DEPLACEMENT__H__
#define __DEPLACEMENT__H__
#include <stdio.h>
#include <stdlib.h>

typedef enum { 
  HAUT,              
  GAUCHE, 
  BAS,               
  DROITE
} Direction;

typedef struct {
  Direction direction; /* Direction du deplacement */
  unsigned long allure; /* Allure du deplacement */
} Deplacement;

/* Initialise un déplacement de projectile
 * et renvoie ce Deplacement. */
Deplacement* init_deplacement(Direction dir, unsigned long allure);

#endif