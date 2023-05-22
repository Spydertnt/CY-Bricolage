#include "main.h"

int main() {

  int mode;
 
  printf("-------Welcome to Castorama------- \n ");
  do{
    printf("Which mode would you like to access ? \n");
    printf("\n  1- Management mode");
    printf("\n  2- Purchase mode \n");
    scanf("%d", &mode);
  }while(mode!=1 && mode!=2);

  if(mode==1){
    management();
    }
  else if(mode==2){
    purchase();
  }
  printf("See you soon at Casto !\n");

return 0;

}
