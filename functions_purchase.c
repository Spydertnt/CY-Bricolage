#include "main.h"

Product buy_product_client(char path[]){
  int choice;
  int verif;
//on recherche un produit
  Product product = research_product();
//si le produit est bien trouvé, on demande à l'utilisateur combien il en veut
  if(product.found==1){
    do{
      printf("How many items would you like to buy ? \n");
      verif = scanf("%d", &product.purchase);
      vide_buffer();
    }while(verif!=1);
//on répète cette boucle tant que l'utilisateur entre un nombre plus grand que la quantité actuelle du produit souhaité
    while(product.purchase>product.qty){
      do{
        printf("The quantity in stock for this product is too low. Please choose another quantity.\n");
        verif = scanf("%d", &product.purchase);
        vide_buffer();
      }while(verif!=1);
    }
    //on décrémente la quantité du produit souhaité de la quantité souhaitée du produit
    product.qty-=product.purchase;
    return product;
  }
  //si le produit n'est pas trouvé, on demande à l'utilisateur s'il souhaite se désinscire
  else if(product.found==0){
    do{
      printf("Would you like to unsubscribe :( ? (1 or 2)\n");
      verif = scanf("%d", &choice);
      vide_buffer();
    }while(choice!=2 && choice!=1 || verif!=1);
    //s'il le souhaite, son fichier est supprimé
    if(choice==1){
      remove(path);
      printf("Client deleted successfully !\n");
      printf("We wish to see you soon at Casto !\n");
      exit(2);
    }
    //sinon, on demande s'il souhaite acheter quelque chose d'autre
    else{
      do{
      printf("Would you like to buy something else ? (1 or 2)\n");
      verif = scanf("%d", &choice);
      vide_buffer();
      }while(choice!=1 && choice!=2 || verif!=1);
      if(choice==1){
      //s'il le souhaite, on fait un appel récursif de la fonction buy_produit_client()
      Product product2 = buy_product_client(path);
    }
    else{
     //sinon on quitte le programme
      printf("See you soon at Casto ! \n");
      exit(3);
    }
      return product;
    }
  }
return product;
}
