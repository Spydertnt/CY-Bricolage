#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define nbr_products 10


//enum taille {petit = 1, moyen = 2, grand = 4};


typedef struct{
    char nom[50];
    int ref;
    int qte;
    int prix;
    char taille[50];
}Produit;

typedef struct{
  char nom[50];
  char prenom[50];
  char histo1[50];
  char histo2[50];
  char histo3[50];
}Client;


void gestion() {
    Produit produit = {0};
    int count=0, i=0, k=5, l=0, m=0;
    Produit inventaire[10];
    FILE* produits = NULL;
    produits = fopen("produits.txt", "r+");
    char phrase[200];
    for(int line=0; line<nbr_products; line++){
        fgets(phrase, 199, produits);
        sscanf(phrase, "%s %d %d %d %s", produit.nom, &produit.ref, &produit.qte, &produit.prix, produit.taille);
        printf("%s %d %d %d %s\n", produit.nom, produit.ref, produit.qte, produit.prix, produit.taille);
        if(produit.qte==0){
            printf("%s est en rupture de stock \n", produit.nom);
            count++;
        }
        if(produit.qte!=0){
            inventaire[i].qte=produit.qte;
            i++;
        }
    }
    if(count==0){
        printf("Aucun produit est en rupture de stock \n");
    }
    if(i<5){
        k=i;
    }
    for(int j=0; j<k; j++){
        Produit minimum = inventaire[0];
        m=0;
    for(int l=0; l<i; l++){
        if(minimum.qte>inventaire[l].qte){
            minimum=inventaire[l];
            m=l;
        }
    }
    inventaire[m]=inventaire[i];
    printf("%s a un stock de %d unités \n", minimum.nom, minimum.qte);
    i--;
}



}


void achat() {
    FILE* clients = NULL;
    clients = fopen("clients.txt", "r+");



}


int main() {

    int mode;
 
    printf("Bienvenue chez Castorama \n ");
    do{
        printf("a quel mode souhaitez vous accéder ? (1:gestion ou 2:achat)\n");
        scanf("%d", &mode);
    }while(mode!=1 && mode!=2);

    if(mode=1){
    gestion();
    }

    return 0;
}