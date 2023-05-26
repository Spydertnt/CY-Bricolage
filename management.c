#include "main.h"

void management() {
  Product product = {0};
  char purchase_name[20];
  int count=0, i=0, k=5, l=0, m=0, verif;
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
  printf("The remaining stock in the shop is %d\n", shop_stock-calculate_stock());
  do{
  printf("Would you like to know a product's stock ? (yes: 1 or no: 2) ? \n");
  verif = scanf("%d", &choice1);
  vide_buffer();
  }while(choice1!=1 && choice1!=2 || verif!=1);
  if(choice1==1){
    research_product();
  }
  do{
    printf("Would you like to increase the quantity of a product ? (yes: 1 or no: 2) \n");
    verif = scanf("%d", &choice2);
    vide_buffer();
  }while(choice2!=1 && choice2!=2 || verif!=1);
  
  do{
    if(choice2==1){
      increase = increase_product();
      /*if(increase.found==0){
        printf("Object not found\n");
      }
      else*/ if(calculate_stock()+(increase.purchase*increase.size)>shop_stock){
        printf("The total stock is insufficient \n");
      }
      else{
        rewrite(increase);
      }
      
      do{
        printf("Would you like to add another product ? (yes: 1 or no: 2) \n");
        verif = scanf("%d", &choice2);
        vide_buffer();
      }while(choice2!=1 && choice2!=2 || verif!=1);
      
    }
  }while(choice2==1);
  fflush(file);
  fclose(file);
}
