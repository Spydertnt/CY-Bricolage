#include "main.h"


int main() {

  int mode;
  int verif;
  printf("╔═════════════════════════════════════╗\n");
  printf("║        Welcome to Castorama         ║\n");
  printf("╚═════════════════════════════════════╝\n");
  
  //tant que l'utilisateur n'entre pas 1 ou 2, on répète cette boucle
  do{
    printf("Which mode would you like to access ? \n");
    printf("\n  1- Management mode");
    printf("\n  2- Purchase mode \n");
    verif = scanf("%d", &mode);
    vide_buffer();
  }while(mode!=1 && mode!=2 || verif!=1);

  if(mode==1){
    management();
    }
  else if(mode==2){
    purchase();
  }

  printf("╔═════════════════════════════════════╗\n");
  printf("║        SEE YOU SOON AT CASTO        ║\n");
  printf("╚═════════════════════════════════════╝\n");

return 0;

}
