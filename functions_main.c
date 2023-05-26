#include "main.h"

void vide_buffer(){
	while(getchar()!='\n'){
	}
}

Product research_product(){
  char name[20];
  int ref, verif;
  Product product={0}, product2={0};
  int rech;
  int currentCaract;
  FILE* file;
  //on ouvre le fichier products en mode lecture
  file = fopen("products.txt", "r");
  if(file==NULL){
    printf("Cannot open file \n");
    exit(1);
  }
  do{
  printf("\n       1- Search by ref:");
  printf("\n       2- Search by name: ");
  printf("\n       Next: ");
  printf("\n       choice: ");
  verif  = scanf("%d" , &rech);
  vide_buffer();
  }while(verif!=1 || rech!=1 && rech!=2);
//on remet le curseur au début dans le fichier produit 
  rewind(file);
//switch case en fonction de la réponse de l'utilisateur
    switch(rech){
      case 1:do{
      printf("       Enter product's ref:");
      verif = scanf("%d", &ref);
      vide_buffer();
      }while(verif!=1);
	//lecture du fichier products, tant que le fichier récupère 5 valeurs correctes
          while(fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size)==5){
            product.line++;
	    //si la réf correspond à une ref du fichier products
            if(ref==product.ref){
              product.found = 1;
              break;
          }
        }
        break;
      case 2: do{
      printf("      Enter product's name :");
      verif = scanf("%s",name);
      vide_buffer();
      }while(verif!=1);
	  //lecture du fichier products, tant que le fichier récupère 5 valeurs correctes
          while(fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size)==5){
	    //on incrémente la ligne du produit
            product.line++;
	    //si le nom correspond à un nom de produits du fichier 
            if(strcmp(product.name,name)==0){
              product.found = 1;
              break;
          }
        }
        break;
      default:
        fclose(file);
        return product2;
    }

  fclose(file);
 //si le produit recherché est bien dans le fichier produits, on affiche la ligne du produit correspondant 
  if(product.found==1){
    printf("\nName\tRef\tQuantity\tPrice\tSize");
    printf("\n-----------------------------------");
    printf("\n%s\t%d\t%d\t%d\t%d\n", product.name, product.ref, product.qty, product.price, product.size);
    return product;
  }
//sinon on quitte la fonction
  else{
    product.found=0;
    printf("Product does not exist\n");
    return product2;
  }

}

int calculate_stock(){
  int stock_used = 0;
  Product product={0};
  FILE* file = NULL;
  FILE* file2 = NULL;
//ouverture du fichier produits en mode lecture
  file = fopen("products.txt", "r");
//ouverture du fichier stock en mode lecture écriture
  file2 = fopen("stock.txt", "r+");
//lecture du fichier produits
  for(int i=0; i<nbr_products; i++){
    fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
//on incrémente stock_used de la quantité du produit par sa taille
    stock_used+=(product.qty*product.size);
  }
//on réécrit dans le fichier stock la nouvelle valeur du stock restant, c'est à dire 1000-stock_used
    fprintf(file2, "%d %d", shop_stock, 1000-stock_used);
//fermeture des fichiers
    fclose(file);
    fclose(file2);
    return stock_used;
}

void rewrite(Product increase){
  int position=0;
  Product product, inventory[nbr_products];
//ouverture du fichier produits en mode lecture écriture
  FILE* file = NULL;
  file = fopen("products.txt","r+");
//ouverture d'un fichier temporaire en mode lecture écriture
  FILE* temp = NULL;
  temp = fopen("temp.txt","w+");
  char line[200];
//on lit le fichier produits, jusqu'à la ligne du produit qui est augmenté
  for(int i=1; i<increase.line; i++){
    fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
//on ecrit dans le fichier temporaire les lignes des produits qui ne sont pas modifés
    fprintf(temp, "%s %d %d %d %d\n", product.name, product.ref, product.qty, product.price, product.size);
    fflush(temp);
    
  }
//si la ligne du produit est différente de 1, on écrit un saut de ligne dans le fichier temporaire
  if(increase.line!=1){
    fprintf(file, "\n");
  }
//on recopie à la suite du fichier temp la ligne du produit qui est modifié
  fprintf(temp, "%s %d %d %d %d\n", increase.name, increase.ref, increase.qty, increase.price, increase.size);
  fgets(line, 199, file);
//après cette ligne modifiée, on recopie les autres lignes des produits d'après qui ne changent pas
  for(int i=increase.line; i<nbr_products; i++){
    fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    fprintf(temp, "%s %d %d %d %d\n", product.name, product.ref, product.qty, product.price, product.size);
    fflush(temp);
  }
//on supprime le fichier products.txt
  remove("products.txt");
//on renomme le fichier temporaire en "products.txt"
  rename("temp.txt", "products.txt");
//affichage du stock restant 
  printf("The remaining stock is : %d\n", shop_stock-calculate_stock());
}
