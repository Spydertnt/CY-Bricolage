#include "main.h"

Product increase_product(){
  //recherche du produit
  Product product=research_product();
  int verif;
  //si le produit est trouvé :
  if(product.found==1){
  do{
    printf("How much would you like to increase ? \n");
    verif = scanf("%d", &product.purchase);
    //on vide la mémoire tampon
    vide_buffer();
  }while(verif!=1);
  //on augmente la quantité du produit de la quantité souhaitée
  product.qty+=product.purchase;
  /*else{
    printf("Product does not exist or return\n");
  }*/
  return product;
}
}
