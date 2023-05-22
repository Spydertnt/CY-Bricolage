#include "main.h"

void purchase() {
    int a=-1, buy=0, choice = 0, purchase = 0, cart = 0, empty = 0, verif;
    Stock stock;
    char client_lastname[50]={0}, client_firstname[50]={0}, id[50]={0}, file_phrase[200]={0}, path[50]={0}, check[50]={0};
    Client client;
    FILE* clients=fopen("clients.txt", "r");
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
    int found=0;
    while(fscanf(clients, "%s", check)==1){
      if(strcmp(check,id)==0){
        found=1;
      break;
      }
    }
    fclose(clients);
    if(a==0 || found==0){
      account=fopen(path, "w");
      do{
      printf("New account\n");
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
      clients=fopen("clients.txt", "a");
      fprintf(clients, "%s ", id);
      fflush(account);
      fclose(clients);
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
        shopping = buy_product_client();
        cart += shopping.price * shopping.purchase;
        rewrite(shopping);
        fprintf(account, "%s %s %s %s %s", client.firstname, client.lastname, shopping.name, client.histo1, client.histo2);
        fscanf(account, "%s %s %s %s %s", client.lastname, client.firstname, client.histo1, client.histo2, client.histo3);
      }
  }while(buy==1 || verif!=1);
    
fclose(account);
printf("Your cart has a total of %d dollars, make that credit card snap!!", cart);
}
