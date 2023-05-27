#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define nbr_products 10
#define nbr_line_stock 1
#define shop_stock 1000
//Déclaration des bibliothèdes ainsi que des constantes liés aux nombres de produits, à la capacité du magasin etc ...

//Déclaration des structures utilisés dans le programme
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
  int line;
}Product;

typedef struct{
  int total_stock;
  int remaining_stock;
}Stock;

//Déclaration des fonctions du programme (prototypes des fonctions)
void vide_buffer();
void delete_client();
Product research_product();
Product increase_product();
Product buy_product_client();
int calculate_stock();
void rewrite(Product increase);
void management();
void purchase();
