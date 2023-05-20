#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define nbr_products 10
#define nbr_line_stock 1
#define shop_stock 1000

typedef struct{
  char lastname[50];
  char firstname[50];
  char histo1[50];
  char histo2[50];
  char histo3[50];
}Client;

typedef struct{
  char name[50];
  int ref;
  int qty;
  int price;
  int size;
  int found;
  int purchase;
}Product;

typedef struct{
  int total_stock;
  int remaining_stock;
}Stock;


void delete_client() {
    char firstname[50];
    char lastname[50];
    Client client;
    FILE* clients = NULL;
    FILE* temp = NULL;
    clients = fopen("clients.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (clients == NULL || temp == NULL) {
        printf("Error while opening files.\n");
        exit(1);
    }
    
    printf("Enter the first name of the client you would like to delete: \n");
    scanf("%s", firstname);
    printf("Enter the last name of the client you would like to delete : \n");
    scanf("%s",lastname);
    
    while (fscanf(clients, "%s %s %s %s %s\n", client.firstname, client.lastname, client.histo1, client.histo2, client.histo3) == 5) {
        if (strcmp(firstname, client.firstname) != 0 && strcmp(lastname, client.lastname)!=0) {
        
            fprintf(temp, "%s %s %s %s %s\n", client.firstname, client.lastname, client.histo1, client.histo2, client.histo3);
        }
   }
    
    
    fclose(clients);
    fclose(temp);
    
    remove("clients.txt");
    rename("temp.txt", "clients.txt");
    
    printf("Client deleted successfully !\n");
}

Product research_product(){
  char name[20];
  int ref;
  Product product={0}, product2={0};
  int rech;
  int currentCaract;
  FILE* file;
  file = fopen("products.txt", "r");
  if(file==NULL){
    printf("Cannot open file \n");
    exit(1);
  }
  printf("\n       1- Search by ref:");
  printf("\n       2- Search by name: ");
  printf("\n      Return to last page: ");
  printf("\n       choice: ");
  scanf("%d" , &rech);
  rewind(file);
    switch(rech){
      case 1:printf("       Enter product's ref:");
      scanf("%d", &ref);
          while(fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size)==5){
            if(ref==product.ref){
              product.found = 1;
              break;
          }
        }
        break;
      case 2: printf("      Enter product's name :");
      scanf("%s",name);
          while(fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size)==5){
            if(strcmp(product.name,name)==0){
              product.found = 1;
              break;
          }
        }
        break;
      default:
        fclose(file);
        return product2;
    }

  fclose(file);
 
  if(product.found==1){
    printf("\nName\tRef\tQuantity\tPrice\tSize");
    printf("\n-----------------------------------");
    printf("\n%s\t%d\t%d\t%d\t%d\n", product.name, product.ref, product.qty, product.price, product.size);
    return product;
  }
  else{
    product.found=0;
    printf("Product does not exist\n");
    return product2;
  }

}

Product buy_product(){
  Product product=research_product();
  if(product.found==1){
    printf("How much would you like to increase ? \n");
    scanf("%d", &product.purchase);
    product.qty+=product.purchase;
  }
  else{
    printf("Product does not exist or return\n");
  }
  return product;
}


Product buy_product_client(){
int choice;
int increase;
Client client;
FILE* clients = NULL;
clients = fopen("clients.txt", "r");
FILE* temp = NULL;
temp = fopen("temp.txt","a+");
Product product = research_product();
Product product2;
if(product.found==1){
  return product;
}
else if(product.found==0){
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
}
return product;
}



int calculate_stock(){
  int stock_used = 0;
  Product product={0};
  FILE* file = NULL;
  FILE* file2 = NULL;
  file = fopen("produits.txt", "r");
  file2 = fopen("stock.txt", "r+");
  for(int i=0; i<nbr_products; i++){
    fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    stock_used+=(product.qty*product.size);
  }
    fprintf(file2, "%d %d", shop_stock, 1000-stock_used);
    fclose(file);
    fclose(file2);
    return stock_used;
}

void management() {
  Product product = {0};
  char purchase_name[20];
  int count=0, i=0, k=5, l=0, m=0;
  Product inventory[nbr_products]={0}, inventory2[nbr_products]={0};
  Product increase;
  FILE* file = NULL;
  file = fopen("products.txt","r+");
  int choice1, choice2, choice3, choice4;
  char phrase[200];
  printf("Here are the available products: \n");
  for(int line=0; line<nbr_products; line++){
    fgets(phrase, 199, file);
    sscanf(phrase, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    if(product.qty==0){
      printf("%s is out of stock \n", product.name);
      count++;
    }
    if(product.qty!=0){
      printf("%s\n", product.name);
      inventory[i]=product;
      i++;
    }
  }
  if(count==0){
    printf("No product is out of stock \n");
    }
  if(i<5){
    k=i;
    }
  Product minimum;
  for(int j=0; j<k; j++){
    minimum.qty=3000;
    m=0;
    for(int l=0; l<i; l++){
      if(minimum.qty>inventory[l].qty){
        minimum=inventory[l];
        m=l;
      }
    }
    inventory[m]=inventory[i-1];
    printf("%s has a stock of %d units\n", minimum.name, minimum.qty);
    i--;
  }
  printf("The remaining space in the store is of : %d\n", shop_stock-calculate_stock());

  do{
  printf("Would you like to know a product's stock ? (yes: 1 or no: 2) ? \n");
  scanf("%d", &choice1);
  }while(choice1!=1 && choice1!=2);

  if(choice1==1){
    research_product();
  }

  do{
    printf("Would you like to increase the quantity of a product ? (yes: 1 or no: 2) \n");
    scanf("%d", &choice2);
  }while(choice2!=1 && choice2!=2);

  do{
    int position;
    if(choice2==1){
      increase = buy_product();
      if(increase.found==0){
        printf("Object not found\n");
      }
      else if(calculate_stock()+(increase.purchase*increase.size)>shop_stock){
        printf("The total stock is insufficient \n");
      }
      else{
        rewind(file);
        for(int i=1; i<increase.ref; i++){
          fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
        }
        if(increase.ref!=1){
          fprintf(file, "\n");
        }
        position=ftell(file);
        fgets(phrase, 199, file);
        for(int i=increase.ref; i<nbr_products; i++){
          fscanf(file, "%s %d %d %d %d", inventory2[i-increase.ref].name, &inventory2[i-increase.ref].ref, &inventory2[i-increase.ref].qty, &inventory[i-increase.ref].price, &inventory2[i-increase.ref].size);
        }
        fseek(file, position, 0);
        for(int i=increase.ref; i<nbr_products; i++){
          fprintf(file, "%s %d %d %d %d\n", inventory[i-increase.ref].name, inventory[i-increase.ref].ref-1, inventory[i-increase.ref].qty, inventory[i-increase.ref].price, inventory[i-increase.ref].size);
        }
        fprintf(file, "%s %d %d %d %d", increase.name, nbr_products, increase.qty, increase.price, increase.size);
        fclose(file);
        file = fopen("produits.txt","r+");
        printf("The remaining stock is : %d\n", shop_stock-calculate_stock());
      }
      do{
        printf("Would you like to add another product ? (yes: 1 or no: 2) \n");
        scanf("%d", &choice2);
      }while(choice2!=1 && choice2!=2);
    }
  }while(choice2==1);
  fclose(file);
}

void purchase() {
    int a=-1;
    int used_stock = 0;
    Stock stock;
    char client_lastname[50], client_firstname[50];
    char file_phrase[200];
    FILE* clients = NULL;
    FILE* products = NULL;
    clients = fopen("clients.txt", "a+");
    products = fopen("products.txt", "r+");
    Client client;
    Product increase;
    Product product;
    int cart = 0;
    int choice, purchase;
    printf("Do you already have an account? If so click 1 otherwise click 0\n");
    do{
      scanf("%d", &a);
    }while(a!=1 && a!=0);
    if(a==0){
      printf("What's your last name ? : ");
      scanf("%s", client_lastname);
      printf("What's your first name ? : ");
      scanf("%s", client_firstname);
      fprintf(clients, "\n%s %s ", client_firstname, client_lastname);
      fflush(clients);
      rewind(clients);
    }
 else if(a==1){
   printf("Please indicate your first name.\n");
   scanf("%s", client_firstname);
   int found = 0;
   while(fscanf(clients,"%s %s %s %s %s\n",client.firstname, client.lastname, client.histo1, client.histo2, client.histo3)==5){
if(strcmp(client.firstname,client_firstname)==0){
  found = 1;
  printf("History of the last 3 purchases: %s %s %s\n", client.histo1, client.histo2, client.histo3);
  break;
}
      
   }
      if(found!=0 && found!=1){
        printf("No history, or minus 3 purchases \n");
      }
    }
    int pursue;
    do{
      printf("Would you like to buy something else ? \n");
      printf("            1- YES \n");
      printf("            2- NO \n");
      scanf("%d", &pursue);
      if(pursue==1){
      increase = buy_product_client();
      printf("How many would you like to buy ? \n");
      scanf("%d", &purchase);
      cart += increase.price * purchase;
      rewind(products);
      for(int i=1; i<increase.ref; i++){
        fscanf(products, "%s %d %d %d %d\n", product.name, &product.ref, &product.qty, &product.price, &product.size);
      }
      if(increase.ref!=1){
        fprintf(products, "\n");
      }
      fprintf(products, "%s %d %d %d %d\n", increase.name, increase.ref, increase.qty, increase.price, increase.size);
      if(a==0 || fscanf(clients, "%s %s %s %s %s", client.firstname, client.lastname, client.histo1, client.histo2, client.histo3)!=5){
        fprintf(clients, " %s", increase.name);
      }
      if(a==1){
          while(fscanf(clients,"%s %s %s %s %s\n",client.firstname, client.lastname, client.histo1, client.histo2, client.histo3)==5){
            if(strcmp(client.firstname,client_firstname)==0){
              fprintf(clients, "%s %s %s %s %s\n", client.firstname, client.lastname, increase.name, client.histo2, client.histo3);
            }
          }
      
      }
      }

}while(pursue==1);

fclose(clients);
fclose(products);

printf("Your cart has a total of %d dollars, make that credit card snap!!", cart);

}

int main() {

  int mode;
 
  printf("-------Welcome to Castorama------- \n ");
  do{
    printf("Which mode would you like to access ? \n");
    printf("\n  1- Management mode");
    printf("\n  2- Purchase mode \n");
    scanf("%d", &mode);
  }while(mode!=1 && mode!=2);

  if(mode==1){
    management();
    }
  else if(mode==2){
      purchase();
  }
  printf("See you soon at Casto !\n");

return 0;

}
