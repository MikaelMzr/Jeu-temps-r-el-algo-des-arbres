/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 28-04-2021 */
/* Dernière modification : 28-04-2021 */
#ifndef __OBJET__H__
#define __OBJET__H__
#include <stdio.h>
#include <stdlib.h>
#include "Generation.h"
#include "Deplacement.h"

typedef enum {
  VIDE = 0,          LANCEUR,           MUR,
  PROJECTILE,        PERSONNAGE,        DESTINATION
} TypeObjet;

typedef struct {
  TypeObjet type;     /* Type de l'objet */
  void* donnee_suppl; /* Donnee supplementaire: son type depend de 
                       * `type` ci-dessus:
                       * - Deplacement*  si  type == PROJECTILE
                       * - Generation* si type == LANCEUR
                       * - donnee_suppl vaut NULL pour les 
                       *   autres types. */
} Objet;


#endif