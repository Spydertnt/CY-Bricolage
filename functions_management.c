#include "main.h"

Product increase_product(){
  Product product=research_product();
  int verif;
  if(product.found==1){
  do{
    printf("How much would you like to increase ? \n");
    verif = scanf("%d", &product.purchase);
    vide_buffer();
  }while(verif!=1);
  product.qty+=product.purchase;
  /*else{
    printf("Product does not exist or return\n");
  }*/
  return product;
}
}
