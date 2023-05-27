#include "main.h"


int main() {

  //Déclaration et initialisation des variables à 0
  int mode = 0;
  int verif = 0;

  //Affichage du message de bienvenue
  printf("╔═════════════════════════════════════╗\n");
  printf("║        Welcome to Castorama         ║\n");
  printf("╚═════════════════════════════════════╝\n");
  
  //Choix du mode souhaité et tant que l'utilisateur n'entre pas 1 ou 2, on répète cette boucle
  do{
    printf("Which mode would you like to access ? \n");
    printf("\n  1- Management mode");
    printf("\n  2- Purchase mode \n");
    verif = scanf("%d", &mode);
    vide_buffer();
  }while(mode!=1 && mode!=2 || verif!=1);

  //Lancement du mode choisie précédemment
  if(mode==1){
    management();
    }
  else if(mode==2){
    purchase();
  }

  //Affichage du message de départ
  printf("╔═════════════════════════════════════╗\n");
  printf("║        SEE YOU SOON AT CASTO        ║\n");
  printf("╚═════════════════════════════════════╝\n");

return 0;

}
