#include "main.h"

Product buy_product(){

  Product product=research_product();

  if(product.found==1){

    printf("How much would you like to increase ? \n");

    scanf("%d", &product.purchase);

    product.qty+=product.purchase;

  }

  /*else{

    printf("Product does not exist or return\n");

  }*/

  return product;

}
