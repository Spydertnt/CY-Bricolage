#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define nbr_products 10
#define nbr_line_stock 1

enum taille {petit = 1, moyen = 2, grand = 4};

typedef struct{
char nom[50];
int ref;
int qte;
int prix;
int taille;
}Produit;

typedef struct{
  char nom[50];
  char prenom[50];
  char histo1[50];
  char histo2[50];
  char histo3[50];
}Client;

typedef struct{
char nom[50];
int ref;
int qte;
int prix;
int taille;
int found;
}ProduitTemp;

typedef struct{
int stock_total;
int stock_restant;
}Stock;

ProduitTemp rechercher_produit(){
  char nom[20];
  int ref;
  ProduitTemp produit={0}, produit2={0};
  int rech;
  int caractereActuel;
  FILE* fichier;
  fichier = fopen("produits.txt", "r");
  caractereActuel = fgetc(fichier);
  if(fichier==NULL){
    printf("ouverture du fichier impossible \n");
    exit(1);
  }
  printf("\n       1- Recherche par ref:");
  printf("\n       2- Recherche par nom ");
  printf("\n       3- Retour:");
  printf("\n       choix: ");
  scanf("%d" , &rech);
  rewind(fichier);
    switch(rech){
      case 1:printf("       Entrez la ref du produit :");
      scanf("%d", &ref);
        do{
          fscanf(fichier, "%s %d %d %d %d", &produit.nom, &produit.ref, &produit.qte, &produit.prix, &produit.taille);
          if(ref==produit.ref){
            produit.found = 1;
            break;
          }
        }while(caractereActuel!=EOF);
        break;
      case 2: printf("      Entrez le nom :");
      scanf("%s", &nom);
        do{
          fscanf(fichier, "%s %d %d %d %d", &produit.nom, &produit.ref, &produit.qte, &produit.prix, &produit.taille);
          if(strcmp(produit.nom,nom)==0){
          produit.found = 1;
          break;
          }
        }while(caractereActuel!=EOF);
        break;
      case 3: 
        fclose(fichier); 
        return produit2;
    }

  fclose(fichier); 
  
  if(produit.found==1){
    printf("\nNom\tRef\tQuantite\tPrix\tTaille");
    printf("\n-----------------------------------");
    printf("\n%s\t%d\t%d\t%d\t%d\n", produit.nom, produit.ref, produit.qte, produit.prix, produit.taille);
    return produit;
  }
  else{
    printf("produit inexistant\n");
    return produit2;
  }

}

ProduitTemp acheter_produit(){
  int augmentation;
  ProduitTemp produit=rechercher_produit();
  if(produit.found==1){
    printf("De combien souhaitez vous augmenter ? \n");
    scanf("%d", &augmentation);
    produit.qte+=augmentation;
  }
  else{
    printf("produit inexistant\n");
  } 
  return produit;
}

void gestion() {
  Produit produit = {0};
  Stock stock_shop = {0};
  char nom_achat[20];
  int count=0, i=0, k=5, l=0, m=0;
  Produit inventaire[nbr_products]={0};
  ProduitTemp augmentation;
  int stock_actuel;
  FILE* fichier = NULL;
  fichier = fopen("produits.txt","r+");
  int choix1, choix2, choix3, choix4;
  char phrase[200];
  printf("Voici les articles disponibles \n");
  for(int line=0; line<nbr_products; line++){
    fgets(phrase, 199, fichier);
    sscanf(phrase, "%s %d %d %d %d", produit.nom, &produit.ref, &produit.qte, &produit.prix, &produit.taille);
    printf("%s\n", produit.nom);
    if(produit.qte==0){
      printf("%s est en rupture de stock \n", produit.nom);
      count++;
      }
    if(produit.qte!=0){
      inventaire[i]=produit;
      i++;
      }
  } 
  if(count==0){
    printf("Aucun produit n'est en rupture de stock \n");
    }
  if(i<5){
    k=i;
    }
  Produit minimum;
  for(int j=0; j<k; j++){
    minimum.qte=3000;
    m=0;
    for(int l=0; l<i; l++){
      if(minimum.qte>inventaire[l].qte){
        minimum=inventaire[l];
        m=l;
      }
    }
    inventaire[m]=inventaire[i-1];
    printf("%s a un stock de %d unites\n", minimum.nom, minimum.qte);
    i--;
  }
  FILE* stock = NULL;
  stock = fopen("stock.txt","r");
  fscanf(stock, "%d %d", &stock_shop.stock_total, &stock_shop.stock_restant);
  printf("La place restante en magasin est de %d\n", stock_shop.stock_restant);

  printf("souhaitez vous connaitre le stock d'un produit (oui: 1 ou non: 2) ? \n");
  scanf("%d", &choix1);

  if(choix1==1){
    rechercher_produit();
  }

  printf("Souhaitez vous augmenter la quantite d'un produit ? (1 ou 2) \n");
  scanf("%d", &choix2);

  if(choix2==1){
    augmentation = acheter_produit();
    stock_actuel = stock_shop.stock_total - stock_shop.stock_restant;
    /*if(stock_actuel+=(augmentation*augmentation.taille)>stock_shop.stock_total){
      printf("Le stock total n'est pas suffisant \n");
    }
    else{*/
      rewind(fichier);
      for(int i=1; i<augmentation.ref; i++){
        fscanf(fichier, "%s %d %d %d %d", produit.nom, &produit.ref, &produit.qte, &produit.prix, &produit.taille);
      }
      if(augmentation.ref!=1){
        fprintf(fichier, "\n");
      }
      fprintf(fichier, "%s %d %d %d %d", augmentation.nom, augmentation.ref, augmentation.qte, augmentation.prix, augmentation.taille);
      fprintf(fichier, "\n");
      //stock_shop.stock_restant -= augmentation; Voir pour une fonction dédié au calcul du stock
    //}
  }
}

void achat() {
    int a=-1;
    char nom_client[50], prenom_client[50];
    FILE* clients = NULL;
    printf("Avez-vous déjà un compte ? Si oui taper 1 sinon 0\n");
    do{
      scanf("%d", &a);
    }while(a!=1 || a!=0);
    if(a==0){
      clients = fopen("clients.txt", "a");
      printf("Quel est votre nom ? : ");
      scanf("%s", nom_client);
      printf("Quel est votre Prénom ? : ");
      scanf("%s", prenom_client);
      fprintf(clients, "\n%s %s", nom_client, prenom_client);
    }
  else if(a==1){
    clients = fopen("clients.txt", "r");
    // Fonction recherche pour trouver la bonne ligne et récupérer la valeur
    // printf les 3 derniers achats
    
  }

}

int main() {

  int mode;
  
  printf("-------Bienvenue chez Castorama------- \n ");
  do{
    printf("A quel mode souhaitez vous acceder ? \n");
    printf("\n  1- Mode gestion");
    printf("\n  2- Mode achat \n");
    scanf("%d", &mode);
  }while(mode!=1 && mode!=2);

  if(mode==1){
    gestion();
    }

return 0;

}
