/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 28-04-2021 */
/* Dernière modification : 30-04-2021 */
#ifndef __GENERATION__H__
#define __GENERATION__H__
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned long intervalle; /* Intervalle entre deux envois
                             * de projectiles */
  unsigned long allure_proj; /* Allure des projectiles envoyes */
} Generation;

/* Initialise une génération de lanceur
 * et renvoie cette Generation. */
Generation* init_generation(void);

#endif