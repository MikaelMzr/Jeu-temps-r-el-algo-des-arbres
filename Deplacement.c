/* Dos Santos Loïc */
/* Mikael Mezouar */
/* Création : 28-04-2021 */
/* Dernière modification : 30-04-2021 */
#include "Deplacement.h"

Deplacement* init_deplacement(Direction dir, unsigned long allure) {
	Deplacement* d;

	d = (Deplacement *) malloc(sizeof(Deplacement));

    d->direction = dir;
    d->allure = allure;

    return d;
}