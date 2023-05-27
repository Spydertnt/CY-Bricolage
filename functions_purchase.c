#include "main.h"

Product buy_product_client(char path[]){
  
  //Déclaration et initialisation des variables à 0
  int choice = 0;
  int verif = 0;
  
  //On recherche un produit
  Product product = research_product();
  
  //Si le produit est bien trouvé, on demande à l'utilisateur combien il en veut
  if(product.found==1 && product.qty!=0){
    do{
      printf("How many items would you like to buy ? \n");
      verif = scanf("%d", &product.purchase);
      vide_buffer();
    }while(verif!=1);
    
    //On répète cette boucle tant que l'utilisateur entre un nombre plus grand que la quantité actuelle en stock
    while(product.purchase>product.qty){
      do{
        printf("The quantity in stock for this product is too low. Please choose another quantity.\n");
        verif = scanf("%d", &product.purchase);
        vide_buffer();
      }while(verif!=1);
    }
    
    //On décrémente la quantité du produit souhaité de la quantité en stock du produit
    product.qty-=product.purchase;
    return product;
  }
  //Si le produit n'est plus disponible ou si il est introuvable, on demande à l'utilisateur s'il souhaite se désinscire
  else{
    do{
      printf("Would you like to unsubscribe :( ? \n");
      printf("          1- Yes.\n");
      printf("          2- No.\n");
      verif = scanf("%d", &choice);
      vide_buffer();
    }while(choice!=2 && choice!=1 || verif!=1);
    
    //S'il le souhaite, son fichier est supprimé
    if(choice==1){
      remove(path);
      printf("Client deleted successfully !\n");
      printf("We wish to see you soon at Casto !\n");
      exit(2);
    }
    //Sinon, on demande s'il souhaite acheter quelque chose d'autre
    else{
      do{
      printf("Would you like to buy something else ? \n");
      printf("          1- Yes.\n");
      printf("          2- No.\n");
      verif = scanf("%d", &choice);
      vide_buffer();
      }while(choice!=1 && choice!=2 || verif!=1);

      if(choice==1){
        //S'il le souhaite, on fait un appel récursif de la fonction buy_produit_client()
        Product product2 = buy_product_client(path);
      }  
      else{
        //Sinon on quitte le programme
        printf("See you soon at Casto ! \n");
        exit(3);
      }
      
      return product;
    }
  }
  
  return product;
  
}
