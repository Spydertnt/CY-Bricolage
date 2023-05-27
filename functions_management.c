#include "main.h"

Product increase_product(){
  
  //Recherche du produit
  Product product=research_product();
  
  int verif = 0;
  
  //Si le produit est trouvé :
  if(product.found==1){
    //On demande de combien on souhaite augmenter la quantité en stock du produit
    do{
      printf("How much would you like to increase ? \n");
      verif = scanf("%d", &product.purchase);
      //On vide la mémoire tampon
      vide_buffer();
    }while(verif!=1);
    
    //On augmente la quantité en stock du produit du montant saisie
    product.qty+=product.purchase;
    return product;
  }
  
}
