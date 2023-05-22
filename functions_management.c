#include "main.h"

Product increase_product(){
  Product product=research_product();
  if(product.found==1){
    printf("How many would you like to buy? \n");
    scanf("%d", &product.purchase);
    product.qty+=product.purchase;
  }
  /*else{
    printf("Product does not exist or return\n");
  }*/
  return product;
}
