#include "Evenement.h"

Tas* malloc_Tas(unsigned capacite_initiale) {
	Tas *tas;

	tas = (Tas *)malloc(sizeof(Tas));

	tas->taille = 0;
	tas->capacite = capacite_initiale;
	tas->valeurs = (Evenement *)malloc(sizeof(Evenement) * capacite_initiale);

	return tas;
}

void free_Tas(Tas* tas) {
	free(tas->valeurs);
	free(tas);
}

int environ_maintenant(unsigned long moment) {
	unsigned long mtn;

	mtn = maintenant() / une_milliseconde;
	if(moment < mtn + 6 && moment > mtn - 6) {
		return 1;
	}
	return 0;
}

bool un_evenement_est_pret(Tas* tas) {
	if(tas->taille != 0) {
		if(environ_maintenant(tas->valeurs[0].moment / une_milliseconde))
			return true;
	}
	return false;
}

Evenement ote_minimum(Tas* tas) {
	Evenement ev;
	unsigned i;

	ev = tas->valeurs[0];
	for(i = 0; i < tas->taille - 1; i++) {
		tas->valeurs[i] = tas->valeurs[i + 1];
	}
	tas->taille--;

	return ev;
}

int compare_moment(const void * premier, const void * second) {
	Evenement ev1, ev2;

	ev1 = * (Evenement *) premier;
	ev2 = * (Evenement *) second;

	return ev1.moment - ev2.moment;
}

void ajoute_evenement(Tas* tas, Evenement n) {
	if(tas->taille == tas->capacite) {
		tas->capacite += BLOC_ALLOC;
		tas->valeurs = (Evenement *)realloc(tas->valeurs, tas->capacite * sizeof(Evenement));
	}

	tas->valeurs[tas->taille] = n;
	tas->taille++;
	qsort(tas->valeurs, tas->taille, sizeof(Evenement), compare_moment);
}

Tas* construit_Tas(Niveau* niveau) {
	Tas* tas;
	unsigned i, j;
	Generation g;
	Evenement ev;

	tas = malloc_Tas(BLOC_ALLOC);

	for(i = 0; i < niveau->taille.y; i++) {
		for(j = 0; j < niveau->taille.x; j++) {
			if(niveau->objets[i][j].type == LANCEUR) {
				g = * (Generation *)niveau->objets[i][j].donnee_suppl;

				ev.moment = maintenant() + (g.intervalle * une_milliseconde);
				ev.coo_obj.x = j;
				ev.coo_obj.y = i;

				ajoute_evenement(tas, ev);
			}
		}
	}
	return tas;
}

void affiche_Tas(Tas* tas){
    unsigned i;
    for(i = 0; i < tas->taille; i++){
        printf("[%ld %d %d] ", tas->valeurs[i].moment / une_milliseconde, tas->valeurs[i].coo_obj.x, tas->valeurs[i].coo_obj.y);
    }
	printf("\n");
}

void deplace_perso(Tas* tas, Niveau* niveau, int touche, int *depl_perso_autorise, int *est_mort, int *gagne) {
	Evenement e;

	switch(touche) {
		case 'z': if(niveau->coo_perso.y != 0) {
					if(niveau->objets[niveau->coo_perso.y - 1][niveau->coo_perso.x].type == VIDE) {
					  	niveau->objets[niveau->coo_perso.y - 1][niveau->coo_perso.x] = niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x];
					  	niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x].type = VIDE;
					  	niveau->coo_perso.y = niveau->coo_perso.y - 1;
					  	e.moment = maintenant() + (niveau->allure_perso * une_milliseconde);
					  	e.coo_obj = niveau->coo_perso;
					  	*depl_perso_autorise = 0;
					  	ajoute_evenement(tas, e);
					}
					else if(niveau->objets[niveau->coo_perso.y - 1][niveau->coo_perso.x].type == PROJECTILE)
						*est_mort = 1;
					else if(niveau->objets[niveau->coo_perso.y - 1][niveau->coo_perso.x].type == DESTINATION)
						*gagne = 1;
				  }
				  break;
		case 'q': if(niveau->coo_perso.x != 0) {
					if(niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x - 1].type == VIDE) {
					  	niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x - 1] = niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x];
					  	niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x].type = VIDE;
					  	niveau->coo_perso.x = niveau->coo_perso.x - 1;
					  	e.moment = maintenant() + (niveau->allure_perso * une_milliseconde);
					  	e.coo_obj = niveau->coo_perso;
					  	*depl_perso_autorise = 0;
					  	ajoute_evenement(tas, e);
					}
					else if(niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x - 1].type == PROJECTILE)
						*est_mort = 1;
					else if(niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x - 1].type == DESTINATION)
						*gagne = 1;
				  }
				  break;
		case 's': if(niveau->coo_perso.y != niveau->taille.y - 1) {
					if(niveau->objets[niveau->coo_perso.y + 1][niveau->coo_perso.x].type == VIDE) {
					  	niveau->objets[niveau->coo_perso.y + 1][niveau->coo_perso.x] = niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x];
					  	niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x].type = VIDE;
					  	niveau->coo_perso.y = niveau->coo_perso.y + 1;
					  	e.moment = maintenant() + (niveau->allure_perso * une_milliseconde);
					  	e.coo_obj = niveau->coo_perso;
					  	*depl_perso_autorise = 0;
					  	ajoute_evenement(tas, e);
					}
					else if(niveau->objets[niveau->coo_perso.y + 1][niveau->coo_perso.x].type == PROJECTILE)
						*est_mort = 1;
					else if(niveau->objets[niveau->coo_perso.y + 1][niveau->coo_perso.x].type == DESTINATION)
						*gagne = 1;
				  }
				  break;
		case 'd': if(niveau->coo_perso.x != niveau->taille.x - 1) {
					if(niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x + 1].type == VIDE) {
					  	niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x + 1] = niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x];
					  	niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x].type = VIDE;
					  	niveau->coo_perso.x = niveau->coo_perso.x + 1;
					  	e.moment = maintenant() + (niveau->allure_perso * une_milliseconde);
					  	e.coo_obj = niveau->coo_perso;
					  	*depl_perso_autorise = 0;
					  	ajoute_evenement(tas, e);
					}
					else if(niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x + 1].type == PROJECTILE)
						*est_mort = 1;
					else if(niveau->objets[niveau->coo_perso.y][niveau->coo_perso.x + 1].type == DESTINATION)
						*gagne = 1;
				  }
				  break;
		default: break; 
	}
}

void execute_evenement(Evenement e, Tas* tas, Niveau* niveau, int *depl_perso_autorise, int *est_mort) {
	Generation *g;
	Deplacement *d;
	Evenement ev;
	unsigned coo_x, coo_y;

	coo_x = e.coo_obj.x;
	coo_y = e.coo_obj.y;
	if(niveau->objets[coo_y][coo_x].type == LANCEUR) {
		g = (Generation *) niveau->objets[coo_y][coo_x].donnee_suppl;

		if(coo_y != 0) {
			if(niveau->objets[coo_y - 1][coo_x].type == VIDE) {
				d = init_deplacement(HAUT, g->allure_proj);
				niveau->objets[coo_y - 1][coo_x].type = PROJECTILE;
				niveau->objets[coo_y - 1][coo_x].donnee_suppl = d;
				
				ev.moment = e.moment + (d->allure * une_milliseconde);
				ev.coo_obj.y = coo_y - 1;
				ev.coo_obj.x = coo_x;
				ajoute_evenement(tas, ev);
			}
			else if(niveau->objets[coo_y - 1][coo_x].type == PERSONNAGE)
				*est_mort = 1;
		}
		if(coo_x != 0) {
			if(niveau->objets[coo_y][coo_x - 1].type == VIDE) {
				d = init_deplacement(GAUCHE, g->allure_proj);
				niveau->objets[coo_y][coo_x - 1].type = PROJECTILE;
				niveau->objets[coo_y][coo_x - 1].donnee_suppl = d;

				ev.moment = e.moment + (d->allure * une_milliseconde);
				ev.coo_obj.y = coo_y;
				ev.coo_obj.x = coo_x - 1;
				ajoute_evenement(tas, ev);
			}
			else if(niveau->objets[coo_y][coo_x - 1].type == PERSONNAGE)
				*est_mort = 1;
		}
		if(coo_y != niveau->taille.y - 1) {
			if(niveau->objets[coo_y + 1][coo_x].type == VIDE) {
				d = init_deplacement(BAS, g->allure_proj);
				niveau->objets[coo_y + 1][coo_x].type = PROJECTILE;
				niveau->objets[coo_y + 1][coo_x].donnee_suppl = d;

				ev.moment = e.moment + (d->allure * une_milliseconde);
				ev.coo_obj.y = coo_y + 1;
				ev.coo_obj.x = coo_x;
				ajoute_evenement(tas, ev);
			}
			else if(niveau->objets[coo_y + 1][coo_x].type == PERSONNAGE)
				*est_mort = 1;
		}
		if(coo_x != niveau->taille.x - 1) {
			if(niveau->objets[coo_y][coo_x + 1].type == VIDE) {
				d = init_deplacement(DROITE, g->allure_proj);
				niveau->objets[coo_y][coo_x + 1].type = PROJECTILE;
				niveau->objets[coo_y][coo_x + 1].donnee_suppl = d;

				ev.moment = e.moment + (d->allure * une_milliseconde);
				ev.coo_obj.y = coo_y;
				ev.coo_obj.x = coo_x + 1;
				ajoute_evenement(tas, ev);
			}
			else if(niveau->objets[coo_y][coo_x + 1].type == PERSONNAGE)
				*est_mort = 1;
		}

		e.moment += (g->intervalle * une_milliseconde);
		ajoute_evenement(tas, e);
	}
	else if(niveau->objets[coo_y][coo_x].type == PROJECTILE) {
		d = (Deplacement *) niveau->objets[coo_y][coo_x].donnee_suppl;

		niveau->objets[coo_y][coo_x].type = VIDE;
		niveau->objets[coo_y][coo_x].donnee_suppl = NULL;

		e.moment += (d->allure * une_milliseconde);
		if(d->direction == HAUT) {
			if(coo_y != 0) {
				if(niveau->objets[coo_y - 1][coo_x].type == VIDE) {
					niveau->objets[coo_y - 1][coo_x].type = PROJECTILE;
					niveau->objets[coo_y - 1][coo_x].donnee_suppl = d;

					e.coo_obj.y--;
					ajoute_evenement(tas, e);
				}
				else if(niveau->objets[coo_y - 1][coo_x].type == PERSONNAGE)
					*est_mort = 1;
			}
		}
		else if(d->direction == GAUCHE) {
			if(coo_x != 0) {
				if(niveau->objets[coo_y][coo_x - 1].type == VIDE) {
					niveau->objets[coo_y][coo_x - 1].type = PROJECTILE;
					niveau->objets[coo_y][coo_x - 1].donnee_suppl = d;

					e.coo_obj.x--;
					ajoute_evenement(tas, e);
				}
				else if(niveau->objets[coo_y][coo_x - 1].type == PERSONNAGE)
					*est_mort = 1;
			}
		}			
		else if(d->direction == BAS) {
			if(coo_y != niveau->taille.y - 1) {
				if(niveau->objets[coo_y + 1][coo_x].type == VIDE) {
					niveau->objets[coo_y + 1][coo_x].type = PROJECTILE;
					niveau->objets[coo_y + 1][coo_x].donnee_suppl = d;

					e.coo_obj.y++;
					ajoute_evenement(tas, e);
				}
				else if(niveau->objets[coo_y + 1][coo_x].type == PERSONNAGE)
					*est_mort = 1;
			}
		}
		else {
			if(coo_x != niveau->taille.x - 1) {
				if(niveau->objets[coo_y][coo_x + 1].type == VIDE) {
					niveau->objets[coo_y][coo_x + 1].type = PROJECTILE;
					niveau->objets[coo_y][coo_x + 1].donnee_suppl = d;

					e.coo_obj.x++;
					ajoute_evenement(tas, e);
				}
				else if(niveau->objets[coo_y][coo_x + 1].type == PERSONNAGE)
					*est_mort = 1;
			}
		}
	}
	else if(niveau->objets[coo_y][coo_x].type == PERSONNAGE) {
		*depl_perso_autorise = 1;
	}
}