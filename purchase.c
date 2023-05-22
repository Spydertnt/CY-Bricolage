#include "main.h"

void purchase() {
    int a=-1, buy=0, choice = 0, purchase = 0, cart = 0, empty = 0, verif;
    Stock stock;
    char client_lastname[50]={0}, client_firstname[50]={0}, id[50]={0}, file_phrase[200]={0}, path[50]={0}, check[50]={0};
    Client client;
    FILE* account = NULL;
    Product product, shopping;
    
    do{
    printf("Do you already have an account? If so type 1 otherwise type 0\n");
    verif = scanf("%d", &a);
    vide_buffer();
    }while(a!=1 && a!=0 || verif!=1);
    
    do{
    printf("Type your ID or create one if you don't have an account : ");
    verif = scanf("%s", id);
    vide_buffer();
    }while(verif!=1);
    
    sprintf(path, "%s.txt", id);
    account = fopen(path, "r");
    
    if(account!=NULL){
      fclose(account);
      if(a==0){
        printf("You have an account why would you want to create a new one ?\n");
      }
    }
    else{
      if(a==1){
        printf("The id doesn't exist so why not creating an account ?\n");
      }
      account=fopen(path, "w");
      printf("New account\n");
      do{
      printf("What's your last name ? : ");
      verif = scanf("%s", client_lastname);
      vide_buffer();
      }while(verif!=1);
      do{
      printf("What's your first name ? : ");
      verif = scanf("%s", client_firstname);
      vide_buffer();
      }while(verif!=1);
      fprintf(account, "%s %s %d %d %d", client_firstname, client_lastname, empty, empty, empty);
      fflush(account);
      fclose(account);
    }
    
    account=fopen(path, "r+");
    fscanf(account, "%s %s %s %s %s", client.lastname, client.firstname, client.histo1, client.histo2, client.histo3);
    if(strcmp(client.histo1,"0") && strcmp(client.histo2,"0") && strcmp(client.histo3,"0")){
        printf("History of the last 3 purchases: %s %s %s\n", client.histo1, client.histo2, client.histo3);
    }
    else{
        printf("No history, or minus 3 purchases \n");
    }
    
    do{
      printf("Would you like to buy something  ? \n");
      printf("            1- YES \n");
      printf("            2- NO \n");
      verif = scanf("%d", &buy);
      vide_buffer();
      if(buy==1){
        shopping = buy_product_client(path);
        cart += shopping.price * shopping.purchase;
        rewrite(shopping);
        fprintf(account, "%s %s %s %s %s", client.firstname, client.lastname, shopping.name, client.histo1, client.histo2);
        fscanf(account, "%s %s %s %s %s", client.lastname, client.firstname, client.histo1, client.histo2, client.histo3);
      }
  }while(buy==1 || verif!=1);
    
fclose(account);
printf("Your cart has a total of %d dollars, make that credit card snap!!", cart);
}
