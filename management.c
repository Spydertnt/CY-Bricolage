#include "main.h"

void management() {
  //Déclaration et initialisation des variables
  Product product = {0}, minimum, increase;
  char purchase_name[20], phrase[200];;
  int count = 0, i = 0, k = 5, l = 0, m = 0, verif, choice1, choice2, choice3, choice4;;
  //Déclaration de 2 tableaux de produits, initialisé à 0
  Product inventory[nbr_products]={0}, inventory2[nbr_products]={0};
  FILE* file = NULL;
  file = fopen("products.txt","r+");
  
  printf("Here are the available products: \n");
  printf("\n");
  
  //Lecture du fichier products.txt
  for(int line=0; line<nbr_products; line++){
    fgets(phrase, 199, file);
    sscanf(phrase, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    //Si un produit a une quantité nulle, on affiche le produit en question et on incrémente le compteur
    if(product.qty==0){
      printf("%s is out of stock \n", product.name);
      count++;
    }
    //Sinon, on affiche la liste des articles du magasin, et on remplie le tableau de produits ayant une quantité non nulle
    if(product.qty!=0){
      printf("%s\n", product.name);
      inventory[i]=product;
      i++;
    }
  }
  
  printf("\n");

  //Si le compteur est à zéro, aucun produit en rupture de stock
  if(count==0){
    printf("No product is out of stock \n");
  }

  //On doit afficher les 5 produits avec les stocks les plus bas non nuls, on vérifie donc qu'il y a au moins 5 produits avec des stocks non nuls, sinon on affichera seulement les noms des produits ayant un stock non nul
  if(i<5){
    k=i;
  }
  
  printf("\n");

  //On trie les 5 produits avec les quantités les plus faibles
  for(int j=0; j<k; j++){
    minimum.qty=3000;
    m=0;
    for(int l=0; l<i; l++){
      if(minimum.qty>inventory[l].qty){
        minimum=inventory[l];
        m=l;
      }
    }
    //On récupère la dernière valeur du tableau qui remplace la valeur minimale (Pour supprimer la valeur minimale du tableau puisque elle est déjà sauvegardée)
    inventory[m]=inventory[i-1];
    //On affiche les 5 produits ayant la plus faible quantité, on décrémente i
    printf("%s has a stock of %d units\n", minimum.name, minimum.qty);
    i--;
  }
  
  printf("\n");

  //On affiche le stock restant du magasin
  printf("The remaining stock in the shop is %d\n", shop_stock-calculate_stock());

  //On demande si l'utilisateur souhaite connaître le stock d'un produit
  do{
    printf("Would you like to know a product's stock ? \n");
    printf("          1- YES \n");
    printf("          2- NO \n");
    verif = scanf("%d", &choice1);
    vide_buffer();
  }while(choice1!=1 && choice1!=2 || verif!=1);
  
  //On appelle la fonction research product si l'utilisateur souhaitre avoir les informations sur un produit et on les affichent
  if(choice1==1){
    research_product();
  }

  //On propose à l'utilisateur d'augmenter la quantité en stock d'un produit
  do{
    printf("Would you like to increase the quantity of a product ? \n");
    printf("          1- YES \n");
    printf("          2- NO \n");
    verif = scanf("%d", &choice2);
    vide_buffer();
  }while(choice2!=1 && choice2!=2 || verif!=1);

  //Si l'utilisateur souhaite augmenter les stocks d'un produit alors on suit la boucle ci-joint pour mettre à jour le fichier avec l'augmentation saisie par l'utilisateur et on propose d'augmenter la quantité en stock d'un autre produit
  while(choice2==1){
    //On appelle la fonction increase_product 
      increase = increase_product();
      //Si la quantité souhaitée du produit fait dépasser la capacité totale du magasin, on affiche un message d'erreur
      if(calculate_stock()+(increase.purchase*increase.size)>shop_stock && increase.found!=0){
        printf("The total stock is insufficient \n");
      }
      //Sinon on met à jour le fichier products.txt
      else if(increase.found!=0){
        rewrite(increase);
      }
      //On demande à l'utilisateur s'il souhaite augmenter autre chose, on répète tant qu'il n'entre pas 1 ou 2
      do{
        printf("Would you like to increase another product ? \n");
        printf("          1- YES \n");
        printf("          2- NO \n");
        verif = scanf("%d", &choice2);
        vide_buffer();
      }while(choice2!=1 && choice2!=2 || verif!=1);
  }
  
  //On vide le tampon associé à file
  fflush(file);
  //On ferme le fichier
  fclose(file);
  
}
