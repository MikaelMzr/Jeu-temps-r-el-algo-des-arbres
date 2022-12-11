/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 28-04-2021 */
/* Dernière modification : 30-04-2021 */
#include "Generation.h"

Generation* init_generation(void) {
	Generation* g;

	g = (Generation *) malloc(sizeof(Generation));

    g->intervalle = 1000;
    g->allure_proj = 300;
    
    return g;
}