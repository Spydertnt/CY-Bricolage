#include "main.h"



void delete_client() {
    int position = 0, found = 0, i = 0, verif;
    char check[50]={0}, id[50]={0}, path[50]={0};
    List inventory[50]={0};
    Client client;
    FILE* clients = NULL;
    clients = fopen("clients.txt", "r");

    if (clients == NULL) {
        printf("Error while opening files.\n");
        exit(1);
    }
    do{
    printf("Enter the id of the client you would like to delete: \n");
    verif = scanf("%s", id);
    vide_buffer();
    }while(verif!=1);

    while(fscanf(clients, "%s", check)==1){
      if(strcmp(check,id)==0){
        found=1;
        break;
      }
      position = ftell(clients);
    }

    if(found==0){
      printf("Invalid id, no client found\n");
    }
    else{
      while(fscanf(clients, "%s", inventory[i])!=EOF){
        i++;
      }
      fseek(clients, position, 0);
      for(int j=0; j<i; j++){
        fprintf(clients, "%s", inventory[j]);
      }
    }

    fclose(clients);
    sprintf(path, "%s.txt", id);  
    remove(path);
    printf("Client deleted successfully !\n");
}

Product buy_product_client(){
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
        delete_client();
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
        Product product2 = buy_product_client();
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
