#include "main.h"

void delete_client() {
    int position = 0, found = 0, i = 0;
    char check[50]={0}, id[50]={0}, path[50]={0};
    List inventory[50]={0};
    Client client;
    FILE* clients = NULL;
    clients = fopen("clients.txt", "r");

    if (clients == NULL) {
        printf("Error while opening files.\n");
        exit(1);
    }

    printf("Enter the id of the client you would like to delete: \n");
    scanf("%s", id);

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
    Product product = research_product();

    if(product.found==1){
        printf("How much would you like to increase ? \n");
        scanf("%d", &product.purchase);
        product.qty-=product.purchase;
        return product;
    }
    /*else if(product.found==0){
        printf("Would you like to unsubscribe :( ? (1 or 2)\n");
        scanf("%d", &choice);
        if(choice==1){
        delete_client();
        printf("We wish to see you soon at Casto !\n");
        exit(2);
      }
      else{
        printf("Would you like to buy something else ? (1 or 2)\n");
        scanf("%d", &choice);
        if(choice==1){
        product2 = buy_product_client();
      }
      else{
        printf("See you soon at Casto ! \n");
        exit(3);
      }
      return product;
  }

}*/

return product;

}
