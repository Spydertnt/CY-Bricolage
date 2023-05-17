#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define nbr_products 10
#define nbr_line_stock 1
#define stock_magasin 1000

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
  int achat;
}Produit;

typedef struct{
  int stock_total;
  int stock_restant;
}Stock;


void supprimer_client() {
    char prenom[50];
    char nom[50];
    Client client;
    FILE* clients = NULL;
    FILE* temp = NULL;
    clients = fopen("clients.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (clients == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        exit(1);
    }
    
    printf("Entrez le prénom du client à supprimer : \n");
    scanf("%s", prenom);
    printf("Entrez le nom du client à supprimer : \n");
    scanf("%s",nom);
    
    while (fscanf(clients, "%s %s %s %s %s\n", client.prenom, client.nom, client.histo1, client.histo2, client.histo3) == 5) {
        if (strcmp(prenom, client.prenom) != 0 && strcmp(nom, client.nom)!=0) {
        	
            		fprintf(temp, "%s %s %s %s %s\n", client.prenom, client.nom, client.histo1, client.histo2, client.histo3);
        }
   }
   	
    
    fclose(clients);
    fclose(temp);
    
    remove("clients.txt");
    rename("temp.txt", "clients.txt");
    
    printf("Client supprimé !\n");
}

Produit rechercher_produit(){
  char nom[20];
  int ref;
  Produit produit={0}, produit2={0};
  int rech;
  int caractereActuel;
  FILE* fichier;
  fichier = fopen("produits.txt", "r");
  if(fichier==NULL){
    printf("ouverture du fichier impossible \n");
    exit(1);
  }
  printf("\n       1- Recherche par ref:");
  printf("\n       2- Recherche par nom: ");
  printf("\n       Sinon retour: ");
  printf("\n       choix: ");
  scanf("%d" , &rech);
  rewind(fichier);
    switch(rech){
      case 1:printf("       Entrez la ref du produit :");
      scanf("%d", &ref);
          while(fscanf(fichier, "%s %d %d %d %d", produit.nom, &produit.ref, &produit.qte, &produit.prix, &produit.taille)==5){
            if(ref==produit.ref){
              produit.found = 1;
              break;
          }
        }
        break;
      case 2: printf("      Entrez le nom :");
      scanf("%s", nom);
          while(fscanf(fichier, "%s %d %d %d %d", produit.nom, &produit.ref, &produit.qte, &produit.prix, &produit.taille)==5){
            if(strcmp(produit.nom,nom)==0){
              produit.found = 1;
              break;
          }
        }
        break;
      default:
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
    produit.found=0;
    printf("produit inexistant\n");
    return produit2;
  }

}

Produit acheter_produit(){
  Produit produit=rechercher_produit();
  if(produit.found==1){
    printf("De combien souhaitez vous augmenter ? \n");
    scanf("%d", &produit.achat);
    produit.qte+=produit.achat;
  }
  else{
    printf("Produit inexistant ou retour\n");
  }
  return produit;
}


Produit acheter_produit_client(){
int choix;
int augmentation;
Client client;
FILE* clients = NULL;
clients = fopen("clients.txt", "r");
FILE* temp = NULL;
temp = fopen("temp.txt","a+");
Produit produit = rechercher_produit();
Produit produit2;
if(produit.found==1){
  return produit;
}
else if(produit.found==0){
  printf("Souhaitez-vous vous désinscrire ? (1 ou 2)\n");
  scanf("%d", &choix);
  if(choix==1){
    supprimer_client();
    printf("Nous espérons vous revoir prochainement chez Casto\n");
    exit(2);
  }
  else{
    printf("Souhaitez-vous acheter autre chose ? (1 OU 2)\n");
    scanf("%d", &choix);
    if(choix==1){
      produit2 = acheter_produit_client();
    }
    else{
      printf("A bientot chez Casto ! \n");
      exit(3);
    }
    return produit;
  }
}
return produit;
}



int calcul_stock(){
  int stock_utiliser = 0;
  Produit produit={0};
  FILE* fichier = NULL;
  FILE* fichier2 = NULL;
  fichier = fopen("produits.txt", "r");
  fichier2 = fopen("stock.txt", "r+");
  for(int i=0; i<nbr_products; i++){
    fscanf(fichier, "%s %d %d %d %d", produit.nom, &produit.ref, &produit.qte, &produit.prix, &produit.taille);
    stock_utiliser+=(produit.qte*produit.taille);
  }
    fprintf(fichier2, "%d %d", stock_magasin, stock_magasin-stock_utiliser);
    fclose(fichier);
    fclose(fichier2);
    return stock_utiliser;
}

void gestion() {
  Produit produit = {0};
  char nom_achat[20];
  int count=0, i=0, k=5, l=0, m=0;
  Produit inventaire[nbr_products]={0}, inventaire2[nbr_products]={0};
  Produit augmentation;
  FILE* fichier = NULL;
  fichier = fopen("produits.txt","r+");
  int choix1, choix2, choix3, choix4;
  char phrase[200];
  printf("Voici les articles disponibles\n");
  for(int line=0; line<nbr_products; line++){
    fgets(phrase, 199, fichier);
    sscanf(phrase, "%s %d %d %d %d", produit.nom, &produit.ref, &produit.qte, &produit.prix, &produit.taille);
    if(produit.qte==0){
      printf("%s est en rupture de stock \n", produit.nom);
      count++;
    }
    if(produit.qte!=0){
      printf("%s\n", produit.nom);
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
  printf("La place restante en magasin est de %d\n", stock_magasin-calcul_stock());

  do{
  printf("souhaitez vous connaitre le stock d'un produit (oui: 1 ou non: 2) ? \n");
  scanf("%d", &choix1);
  }while(choix1!=1 && choix1!=2);

  if(choix1==1){
    rechercher_produit();
  }

  do{
    printf("Souhaitez-vous augmenter la quantite d'un produit ? (oui: 1 ou non: 2) \n");
    scanf("%d", &choix2);
  }while(choix2!=1 && choix2!=2);

  do{
    int position;
    if(choix2==1){
      augmentation = acheter_produit();
      if(augmentation.found==0){
        printf("Objet non trouvé\n");
      }
      else if(calcul_stock()+(augmentation.achat*augmentation.taille)>stock_magasin){
        printf("Le stock total n'est pas suffisant \n");
      }
      else{
        rewind(fichier);
        for(int i=1; i<augmentation.ref; i++){
          fscanf(fichier, "%s %d %d %d %d", produit.nom, &produit.ref, &produit.qte, &produit.prix, &produit.taille);
        }
        if(augmentation.ref!=1){
          fprintf(fichier, "\n");
        }
        position=ftell(fichier);
        fgets(phrase, 199, fichier);
        for(int i=augmentation.ref; i<nbr_products; i++){
          fscanf(fichier, "%s %d %d %d %d", inventaire2[i-augmentation.ref].nom, &inventaire2[i-augmentation.ref].ref, &inventaire2[i-augmentation.ref].qte, &inventaire2[i-augmentation.ref].prix, &inventaire2[i-augmentation.ref].taille);
        }
        fseek(fichier, position, 0);
        for(int i=augmentation.ref; i<nbr_products; i++){
          fprintf(fichier, "%s %d %d %d %d\n", inventaire2[i-augmentation.ref].nom, inventaire2[i-augmentation.ref].ref-1, inventaire2[i-augmentation.ref].qte, inventaire2[i-augmentation.ref].prix, inventaire2[i-augmentation.ref].taille);
        }
        fprintf(fichier, "%s %d %d %d %d", augmentation.nom, nbr_products, augmentation.qte, augmentation.prix, augmentation.taille);
        fclose(fichier);
        fichier = fopen("produits.txt","r+");
        printf("Le stock restant est de %d\n", stock_magasin-calcul_stock());
      }
      do{
        printf("Souhaitez-vous acheter un autre produit ? (oui: 1 ou non: 2) \n");
        scanf("%d", &choix2);
      }while(choix2!=1 && choix2!=2);
    }
  }while(choix2==1);
  fclose(fichier);
}

void achat() {
    int a=-1;
    int stock_utiliser = 0;
    Stock stock;
    char nom_client[50], prenom_client[50];
    char phrase_fichier[200];
    FILE* clients = NULL;
    FILE* produits = NULL;
    clients = fopen("clients.txt", "a+");
    produits = fopen("produits.txt", "r+");
    Client client;
    Produit augmentation;
    Produit produit;
    int panier = 0;
    int choix, achat;
    printf("Avez-vous déjà un compte ? Si oui taper 1 sinon 0\n");
    do{
      scanf("%d", &a);
    }while(a!=1 && a!=0);
    if(a==0){
      printf("Quel est votre nom ? : ");
      scanf("%s", nom_client);
      printf("Quel est votre Prénom ? : ");
      scanf("%s", prenom_client);
      fprintf(clients, "\n%s %s ", prenom_client, nom_client);
      fflush(clients);
      rewind(clients);
    }
	  else if(a==1){
	    printf("Indiquez votre prenom.\n");
	    scanf("%s", prenom_client);
	    printf("indiquez votre nom\n");
	    scanf("%s", nom_client);
	    int found = 0;
	    while(fscanf(clients,"%s %s %s %s %s\n",client.prenom, client.nom, client.histo1, client.histo2, client.histo3)==5){
		if(strcmp(client.prenom,prenom_client)==0){
			if(strcmp(client.nom, nom_client)==0){
		  		found = 1;
		  		printf("historique des 3 derniers achats: %s %s %s\n", client.histo1, client.histo2, client.histo3);
		  		break;
			}
		else if(strcmp(client.prenom, prenom_client)!=0 || strcmp(client.nom, nom_client)!=0){
				printf("Vous n'etes pas dans la base de donnees des clients. \n");
				fprintf(clients, "\n%s %s ", prenom_client, nom_client);
		}
	      	}
	    }
      if(!found){
        printf("pas d'historique, ou moins de 3 achats.\n");
      }
    }
    int continuer;
    do{
      printf("Souhaitez vous acheter quelque chose ? \n");
      printf("            1- OUI \n");
      printf("            2- NON \n");
      scanf("%d", &continuer);
      if(continuer==1){
      augmentation = acheter_produit_client();
      printf("Combien voulez-vous en acheter ? \n");
      scanf("%d", &achat);
      panier += augmentation.prix * achat;
      rewind(produits);
      for(int i=1; i<augmentation.ref; i++){
        fscanf(produits, "%s %d %d %d %d\n", produit.nom, &produit.ref, &produit.qte, &produit.prix, &produit.taille);
      }
      if(augmentation.ref!=1){
        fprintf(produits, "\n");
      }
      fprintf(produits, "%s %d %d %d %d\n", augmentation.nom, augmentation.ref, augmentation.qte, augmentation.prix, augmentation.taille);
      if(a==0 || fscanf(clients, "%s %s %s %s %s", client.prenom, client.nom, client.histo1, client.histo2, client.histo3)!=5){
        fprintf(clients, " %s", augmentation.nom);
      }
      if(a==1){
          while(fscanf(clients,"%s %s %s %s %s\n",client.prenom, client.nom, client.histo1, client.histo2, client.histo3)==5){
            if(strcmp(client.prenom,prenom_client)==0){
              fprintf(clients, "%s %s %s %s %s\n", client.prenom, client.nom, augmentation.nom, client.histo2, client.histo3);
            }
          }
      
      }
      }

}while(continuer==1);

fclose(clients);
fclose(produits);

printf("Votre panier est de %d euros, faites claquer la CB\n", panier);

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
  else if(mode==2){
      achat();
  }
  printf("A bientot chez Casto !\n");

return 0;

}
