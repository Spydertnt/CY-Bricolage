#include "main.h"

Product buy_product_client(char path[]){
    int choice;
    int verif;
    Product product = research_product();

    if(product.found==1){
    	do{
        printf("How many items would you like to buy ? \n");
        verif = scanf("%d", &product.purchase);
        vide_buffer();
        }while(verif!=1);
        while(product.purchase>product.qty){
        	do{
        	printf("The quantity in stock for this product is too low. Please choose another quantity.\n");
        	verif = scanf("%d", &product.purchase);
        	vide_buffer();
        	}while(verif!=1);
        }
        product.qty-=product.purchase;
        return product;
    }
    else if(product.found==0){
    	do{
        printf("Would you like to unsubscribe :( ? (1 or 2)\n");
        verif = scanf("%d", &choice);
        vide_buffer();
        }while(choice!=2 && choice!=1 || verif!=1);
        if(choice==1){
        remove(path);
        printf("Client deleted successfully !\n");
        printf("We wish to see you soon at Casto !\n");
        exit(2);
      }
      else{
      	do{
        printf("Would you like to buy something else ? (1 or 2)\n");
        verif = scanf("%d", &choice);
        vide_buffer();
        }while(choice!=1 && choice!=2 || verif!=1);
        if(choice==1){
        Product product2 = buy_product_client(path);
      }
      else{
        printf("See you soon at Casto ! \n");
        exit(3);
      }
      return product;
  }
}

return product;

}
