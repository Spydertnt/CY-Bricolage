#include "main.h"

void purchase() {
    //Déclaration et initialisation des variables
    int a=-1, buy=0, choice = 0, purchase = 0, cart = 0, empty = 0, verif = 0;
    Stock stock;
    char client_lastname[50]={0}, client_firstname[50]={0}, id[50]={0}, file_phrase[200]={0}, path[50]={0}, check[50]={0};
    Client client;
    FILE* account = NULL;
    FILE* temp = NULL;
    Product product, shopping;

    //Boucle demandant si l'utilisateur possède un compte
    do{
      printf("Do you already have an account?\n");
      printf("          1- YES \n");
      printf("          2- NO \n");
      verif = scanf("%d", &a);
      vide_buffer();
    }while(a!=1 && a!=2 || verif!=1);

    //Boucle demandant l'id de l'utilisateur si il a un compte ou d'en créer un
    do{
    printf("Type your ID or create one if you don't have an account : ");
    verif = scanf("%s", id);
    vide_buffer();
    }while(verif!=1);
  
    //path devient une concaténation de id et de .txt
    sprintf(path, "%s.txt", id);
    account = fopen(path, "r");

    //Vérification de l'existence ou non du fichier client
    if(account!=NULL){
      fclose(account);
      if(a==2){
        //L'utilisateur à répondu qu'il n'avait pas de compte mais un compte du même identifiant existe
        printf("You have an account why would you want to create a new one ?\n");
      }
    }
    else{
      if(a==1){
        //L'utilisateur à répondu qu'il avait un compte mais aucun compte avec cette identifiant existe
        printf("The id doesn't exist so why not creating an account ?\n");
      }
      //Création du fichier account 
      account=fopen(path, "w");
      printf("New account\n");
      do{
      printf("What's your last name ? : ");
      verif = scanf("%s", client_lastname);
      vide_buffer();
      }while(verif!=1);
      do{
      printf("What's your first name ? : ");
      verif = scanf("%s", client_firstname);
      vide_buffer();
      }while(verif!=1);
      //écriture du nom et prénom du client, et de 3 0 correspondant à son historique (encore inexistant)
      fprintf(account, "%s %s %d %d %d", client_lastname, client_firstname, empty, empty, empty);
      fflush(account);
      fclose(account);
    }
  
    //ouverture du fichier account en mode lecture écriture
    account=fopen(path, "r+");
  
    //lecture du fichier account
    fscanf(account, "%s %s %s %s %s", client.lastname, client.firstname, client.histo1, client.histo2, client.histo3);
  
    //si on trouve 3 produits en historique, on les affiche
    if(strcmp(client.histo1,"0") && strcmp(client.histo2,"0") && strcmp(client.histo3,"0")){
        printf("History of the last 3 purchases: %s %s %s\n", client.histo1, client.histo2, client.histo3);
    }
    //sinon on affiche :
    else{
        printf("No history, or minus 3 purchases \n");
    }

    //Boucle permettant à l'utilisateur d'acheter un ou plusieurs objets d'une ou de plusieurs références
    do{
      printf("Would you like to buy something  ? \n");
      printf("            1- YES \n");
      printf("            2- NO \n");
      verif = scanf("%d", &buy);
      vide_buffer();
      if(buy==1){
        shopping = buy_product_client(path);
        //on incrémente le prix total du prix de l'article acheté multiplié par la quantité souhaitée 
        cart += shopping.price * shopping.purchase;
        //on écrit dans le fichier produit la modification liée au produit acheté
        rewrite(shopping);
        //On crée un fichier temporaire qui permettra de mettre à jour les données du client
        temp=fopen("temp.txt", "w");
        //on écrit dans le fichier temp l'historique mis à jour
        fprintf(temp, "%s %s %s %s %s", client.lastname, client.firstname, shopping.name, client.histo1, client.histo2);
        //On ferme le fichier temporaire pour enregistrer les modifications pour la console
        fclose(temp);
        //On réouvre en mode lecture pour récupérer les données
        temp=fopen("temp.txt", "r");
        //on lit le fichier temporaire
        fscanf(temp, "%s %s %s %s %s", client.lastname, client.firstname, client.histo1, client.histo2, client.histo3);
        printf("%s\n", client.histo1);
        //On ferme le fichier temporaire
        fclose(temp);
        //on supprime l'ancien fichier du client
        remove(path);
        //on renomme le fichier temporaire au nom du client
        rename("temp.txt", path);
      }
    //on répète cette boucle tant que le client souhaite acheter quelque chose, ou si le scanf ne retourne pas 1
    }while(buy==1 || verif!=1);
  
  //on ferme le fichier
  fclose(account);
  
  //affichage du prix total
  printf("Your cart has a total of %d dollars, make that credit card snap!!\n", cart);
  
}
