#include "main.h"

void purchase() {
    int a=-1, buy=0, choice = 0, purchase = 0, cart = 0, empty = 0;
    Stock stock;
    char client_lastname[50]={0}, client_firstname[50]={0}, id[50]={0}, file_phrase[200]={0}, path[50]={0}, check[50]={0};
    Client client;
    FILE* clients=fopen("clients.txt", "r");
    FILE* account = NULL;
    Product product, shopping;
    
    do{
    printf("Do you already have an account? If so type 1 otherwise type 0\n");
      scanf("%d", &a);
    }while(a!=1 && a!=0);
    
    printf("What's your ID or invent one if you don't have an account : ");
    scanf("%s", id);
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
      printf("New account\n");
      printf("What's your last name ? : ");
      scanf("%s", client_lastname);
      printf("What's your first name ? : ");
      scanf("%s", client_firstname);
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
      scanf("%d", &buy);
      if(buy==1){
        shopping = buy_product_client();
        cart += shopping.price * shopping.purchase;
        rewrite(shopping);
        fprintf(account, "%s %s %s %s %s", client.firstname, client.lastname, shopping.name, client.histo1, client.histo2);
        fscanf(account, "%s %s %s %s %s", client.lastname, client.firstname, client.histo1, client.histo2, client.histo3);
      }
  }while(buy==1);
    
fclose(account);
printf("Your cart has a total of %d dollars, make that credit card snap!!", cart);
}
