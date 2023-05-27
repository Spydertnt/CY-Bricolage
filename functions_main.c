#include "main.h"

//Sécurise les printf
void vide_buffer(){
	while(getchar()!='\n'){
	}
}

//Fonction de recherche de produit
Product research_product(){
  
  //Déclaration et initialisation des variables à 0
  char name[20] = {0};
  int ref = 0, verif = 0, rech = 0;
  Product product={0}, product2={0};
  FILE* file;
  
  //On ouvre le fichier products en mode lecture
  file = fopen("products.txt", "r");

  //On vérifie que le fichier existe bien sinon on renvoie une erreur
  if(file==NULL){
    printf("Cannot open file \n");
    exit(1);
  }

  //Quel est le critère de recherche
  do{
  printf("\n       1- Search by ref:");
  printf("\n       2- Search by name: ");
  printf("\n       3- Sign out ");
  printf("\n       choice: ");
  verif  = scanf("%d" , &rech);
  vide_buffer();
  }while(verif!=1 || rech!=1 && rech!=2 && rech!=3);

  //On remet le curseur au début dans le fichier produit 
  rewind(file);

  //Switch case en fonction de la réponse de l'utilisateur
  switch(rech){
    //Recherche avec la référence du produit
    case 1: do{
      printf("       Enter product's ref:");
      verif = scanf("%d", &ref);
      vide_buffer();
    }while(verif!=1);
      
    //Lecture du fichier products, tant que le fichier récupère 5 valeurs correctes
    while(fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size)==5){
      //On incrémente la ligne du produit
      product.line++;
	    //Si la réf saisie correspond à une réf du fichier products, le produit est indiqué comme trouvé
      if(ref==product.ref){
        product.found = 1;
        break;
      }
    }
      
    break;

    //Recherche par nom
    case 2: do{
      printf("      Enter product's name :");
      verif = scanf("%s",name);
      vide_buffer();
    }while(verif!=1);
      
	  //Lecture du fichier products, tant que le fichier récupère 5 valeurs correctes
    while(fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size)==5){
	    //On incrémente la ligne du produit
      product.line++;
	    //Si le nom saisie est identique au nom d'un des produits écrit dans le fichier, le produit est indiqué comme trouvé 
      if(strcmp(product.name,name)==0){
        product.found = 1;
        break;
      }
    }
      
    break;
    
    case 3:
      fclose(file);

    //Message d'au revoir
  	printf("╔═════════════════════════════════════╗\n");
  	printf("║        SEE YOU SOON AT CASTO        ║\n");
  	printf("╚═════════════════════════════════════╝\n");
        exit(4);
  }

  //Fermeture du fichier products.txt
  fclose(file);
  
  //Si le produit recherché est bien dans le fichier produits, on affiche la ligne du produit correspondant 
  if(product.found==1){
    printf("\nName\tRef\tQuantity\tPrice\tSize");
    printf("\n-----------------------------------");
    printf("\n%s\t%d\t%d\t%d\t%d\n", product.name, product.ref, product.qty, product.price, product.size);
    return product;
  }
  //Sinon on quitte la fonction
  else{
    product.found=0;
    printf("Product does not exist\n");
    return product2;
  }
  
}

int calculate_stock(){
  
  //Déclaration et initialisation des variables à 0
  int stock_used = 0;
  Product product={0};
  FILE* file = NULL;
  FILE* file2 = NULL;
  
  //Ouverture du fichier produits en mode lecture
  file = fopen("products.txt", "r");

  //On vérifie que le fichier existe bien sinon on renvoie une erreur
  if(file==NULL){
    printf("Cannot open file \n");
    exit(10);
  }
  
  //Ouverture du fichier stock en mode lecture écriture
  file2 = fopen("stock.txt", "r+");

  //On vérifie que le fichier existe bien sinon on renvoie une erreur
  if(file2==NULL){
    printf("Cannot open file \n");
    exit(11);
  }
  
  //Lecture du fichier produits
  for(int i=0; i<nbr_products; i++){
    fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    //On incrémente stock_used de la quantité du produit multiplié par sa taille
    stock_used+=(product.qty*product.size);
  }
  
  //On réécrit dans le fichier stock la nouvelle valeur du stock restant, c'est à dire 1000-stock_used
  fprintf(file2, "%d %d", shop_stock, 1000-stock_used);
  //Fermeture des fichiers
  fclose(file);
  fclose(file2);

  //On retourne le stock utilisé
  return stock_used;
  
}

void rewrite(Product increase){

  //Déclaration et initialisation des variables
  int position = 0;
  Product product, inventory[nbr_products];
  char line[200];
  
  //Ouverture du fichier produits en mode lecture écriture
  FILE* file = NULL;
  file = fopen("products.txt","r+");

  //On vérifie que le fichier existe bien sinon on renvoie une erreur
  if(file==NULL){
    printf("Cannot open file \n");
    exit(12);
  }
  
  //Ouverture d'un fichier temporaire en mode lecture écriture
  FILE* temp = NULL;
  temp = fopen("temp.txt","w+");
  
  //On lit le fichier produits, jusqu'à la ligne du produit qui est augmenté
  for(int i=1; i<increase.line; i++){
    fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    //On copie dans le fichier temporaire les lignes des produits qui ne sont pas modifés
    fprintf(temp, "%s %d %d %d %d\n", product.name, product.ref, product.qty, product.price, product.size);
    //Synchronisation du buffer en mémoire avec le fichier
    fflush(temp);
  }
  
  //Si la ligne du produit est différente de 1, on écrit un saut de ligne dans le fichier temporaire
  if(increase.line!=1){
    fprintf(file, "\n");
  }
  
  //On recopie à la suite du fichier temp la ligne du produit qui est modifié
  fprintf(temp, "%s %d %d %d %d\n", increase.name, increase.ref, increase.qty, increase.price, increase.size);

  //On copie dans un tableau la ligne originale du produit qui ne sert plus pour la passer 
  fgets(line, 199, file);
  
  //Après cette ligne modifiée, on recopie les autres lignes des produits d'après qui ne changent pas
  for(int i=increase.line; i<nbr_products; i++){
    fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    fprintf(temp, "%s %d %d %d %d\n", product.name, product.ref, product.qty, product.price, product.size);
    fflush(temp);
  }
  
  //On supprime l'ancien fichier products.txt
  remove("products.txt");
  
  //On renomme le fichier temporaire en "products.txt"
  rename("temp.txt", "products.txt");
  
  //Affichage du stock restant 
  printf("The remaining stock is : %d\n", shop_stock-calculate_stock());
  
}
