#include <sys/select.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

/* Fichier testé avec:
   - Ubuntu 20.04.2 LTS (Victor Marsault)
   - Ubuntu 20.10 (Christophe Morvan)
   - MacOS Catalina, version 10.15.7 (Marie van den Bogaard)
*/

static void millisleep(unsigned long i) {
  struct timeval tim;
  tim.tv_sec = 0;
  tim.tv_usec =  i * 1000;
  select(0, NULL, NULL, NULL, &tim);
}


int main() {
  unsigned i;

  /* Reparametrisation de STDIN */
  fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK); /* Rend l'appel à `read`
                                                        sur le descripteur 0 
                                                        (STDIN dans la plupart 
                                                        des cas) non-bloquant */
  setbuf(stdin, NULL); /* Supprime le buffer du flux stdin */

  /* Reparametrisation du terminal*/
  struct termios old_tio;
  struct termios new_tio;
  tcgetattr(0,&old_tio); /* Récupère les parametres actuels du terminal */
  new_tio=old_tio; /* Copie les anciens parametres dans les nouveaux*/
  new_tio.c_lflag &=(~ICANON & ~ECHO); /* Desactive les mode 'canonique' et 
                                          'echo' */
  new_tio.c_cc[VMIN] = 1; /* Taille du buffer avant transmission à STDIN */
  new_tio.c_cc[VTIME] = 0; /* Temps d'attente (en ds) avant de transmettre 
                              une input à STDIN. */
  tcsetattr(0, TCSANOW, &new_tio); /* Applique les paramètres */


  unsigned nb_sec = 10;
  unsigned une_touche_a_ete_pressee = 0;
  printf("Ce programme doit tourner pendant environ %d secondes.\n\n",10);
  printf("Chaque fois qu'une touche du clavier est pressée, ce programme "
         "doit afficher immediatement son code (ou ses codes) sur la sortie "
         "standart, precédé de \"Code reçu:\"\n\n");

  unsigned une_touche_a_ete_recu_sans_entree = 0;
  for (i=0; i<=nb_sec*100; i++) {
    unsigned une_touche_a_ete_recu_sans_entree_bis = 0;
    if (i%100 == 0) {
      printf("[Seconde %02d] Ce message doit s'afficher toutes les secondes "
             "quoi qu'il arrive.\n", i/100);
      printf("             Si ce n'est pas le cas, cette configuration ne "
             "fonctionne pas sur\n             votre machine.\n");
    }
    
    int c;
    while ( (c=getchar()) != EOF) {
      printf("\tCode reçu: %d\n", c);
      une_touche_a_ete_pressee++;
      une_touche_a_ete_recu_sans_entree_bis = (c!=10);
    }
    if (une_touche_a_ete_recu_sans_entree_bis)
       une_touche_a_ete_recu_sans_entree = 1;
    millisleep(10);
  }
  if (!une_touche_a_ete_pressee)
    printf("\n"
           "[ECHEC] Aucune touche n'a été reçue.\n"
           "        Cela peut aussi arriver si vous n'avez pressé aucune "
           "touche pendant le\n        test.\n");
  else if (!une_touche_a_ete_recu_sans_entree)
    printf("\n"
           "[ECHEC] Les entrées reçues ont l'air d'avoir été bufferisée.\n"
           "        Reessayez le test sans jamais presser la touche 'Entrée' "
           " (mais en\n        pressant d'autres touches).\n"
          );
  else
    printf("\n"
           "[REUSSITE] La configuration a l'air de fonctionner sur votre "
           "machine.\n");



  /* Rend au terminal ses paramètres d'origine */
  tcsetattr(0,TCSANOW,&old_tio);
  return (1);

}
