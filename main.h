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
  char id[50];
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

void vide_buffer();
void delete_client();
Product research_product();
Product increase_product();
Product buy_product_client();
int calculate_stock();
void rewrite(Product increase);
void management();
void purchase();
