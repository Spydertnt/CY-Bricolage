#include "main.h"

void management() {
  Product product = {0};
  char purchase_name[20];
  int count=0, i=0, k=5, l=0, m=0, verif;
  //déclaration d'un tableau de produits, et d'un tableau de produits ayant une quantité nulle
  Product inventory[nbr_products]={0}, inventory2[nbr_products]={0};
  Product increase;
  FILE* file = NULL;
  file = fopen("products.txt","r+");
  int choice1, choice2, choice3, choice4;
  char phrase[200];
  printf("Here are the available products: \n");
  //lecture du fichier products.txt
  for(int line=0; line<nbr_products; line++){
    fgets(phrase, 199, file);
    sscanf(phrase, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    //si un produit a une quantité nulle, on affiche le produit en question et on incrémente le compteur
    if(product.qty==0){
      printf("%s is out of stock \n", product.name);
      count++;
    }
    //sinon, on affiche la liste des articles du magasin, et on remplie le tableau de produits ayant une quantité non nulle
    if(product.qty!=0){
      printf("%s\n", product.name);
      inventory[i]=product;
      i++;
    }
  }
  //si le compteur est à zéro, aucun produit en rupture de stock
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
    //on affiche les 5 produits ayant la plus faible quantité, on décrémente i
    printf("%s has a stock of %d units\n", minimum.name, minimum.qty);
    i--;
  }
  //on affiche le stock restant du magasin
  printf("The remaining stock in the shop is %d\n", shop_stock-calculate_stock());
  do{
  printf("Would you like to know a product's stock ? (yes: 1 or no: 2) ? \n");
  verif = scanf("%d", &choice1);
  vide_buffer();
  }while(choice1!=1 && choice1!=2 || verif!=1);
  //on appelle la fonction research product
  if(choice1==1){
    research_product();
  }
  do{
    printf("Would you like to increase the quantity of a product ? (yes: 1 or no: 2) \n");
    verif = scanf("%d", &choice2);
    vide_buffer();
  }while(choice2!=1 && choice2!=2 || verif!=1);
  
  do{
    //on appelle la fonction increase_product 
    if(choice2==1){ 
      increase = increase_product();
      //si la quantité souhaitée du produit fait dépasser la capacité totale du magasin, on affiche un message d'erreur
      if(calculate_stock()+(increase.purchase*increase.size)>shop_stock && increase.found!=0){
        printf("The total stock is insufficient \n");
      }
      //sinon on met à jour le fichier products.txt
      else if(increase.found!=0){
        rewrite(increase);
      }
      //on demande à l'utilisateur s'il souhaite augmenter autre chose, on répète tant qu'il n'entre pas 1 ou 2
      do{
        printf("Would you like to add another product ? (yes: 1 or no: 2) \n");
        verif = scanf("%d", &choice2);
        vide_buffer();
      }while(choice2!=1 && choice2!=2 || verif!=1);
    }
  }while(choice2==1);
  //on vide le tampon associé à file
  fflush(file);
  //on ferme le fichier
  fclose(file);
}
