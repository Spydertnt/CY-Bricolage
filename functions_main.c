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
  file = fopen("products.txt", "r");
  if(file==NULL){
    printf("Cannot open file \n");
    exit(1);
  }
  do{
  printf("\n       1- Search by ref:");
  printf("\n       2- Search by name: ");
  printf("\n       Return to last page: ");
  printf("\n       choice: ");
  verif  = scanf("%d" , &rech);
  vide_buffer();
  }while(verif!=1 || rech!=1 && rech!=2);
  rewind(file);
    switch(rech){
      case 1:do{
      printf("       Enter product's ref:");
      verif = scanf("%d", &ref);
      vide_buffer();
      }while(verif!=1);
          while(fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size)==5){
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
          while(fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size)==5){
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
 
  if(product.found==1){
    printf("\nName\tRef\tQuantity\tPrice\tSize");
    printf("\n-----------------------------------");
    printf("\n%s\t%d\t%d\t%d\t%d\n", product.name, product.ref, product.qty, product.price, product.size);
    return product;
  }
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
  file = fopen("products.txt", "r");
  file2 = fopen("stock.txt", "r+");
  for(int i=0; i<nbr_products; i++){
    fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    stock_used+=(product.qty*product.size);
  }
    fprintf(file2, "%d %d", shop_stock, 1000-stock_used);
    fclose(file);
    fclose(file2);
    return stock_used;
}

void rewrite(Product increase){
  int position=0;
  Product product, inventory[nbr_products];
  FILE* file = NULL;
  file = fopen("products.txt","r+");
  FILE* temp = NULL;
  temp = fopen("temp.txt","w+");
  char line[200];
  for(int i=1; i<increase.line; i++){
    fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    fprintf(temp, "%s %d %d %d %d\n", product.name, product.ref, product.qty, product.price, product.size);
    fflush(temp);
    
  }
  if(increase.line!=1){
    fprintf(file, "\n");
    fprintf(temp, "\n");
  }
  fprintf(temp, "%s %d %d %d %d\n", increase.name, increase.ref, increase.qty, increase.price, increase.size);
  fgets(line, 199, file);
  for(int i=increase.line; i<nbr_products; i++){
    fscanf(file, "%s %d %d %d %d", product.name, &product.ref, &product.qty, &product.price, &product.size);
    fprintf(temp, "%s %d %d %d %d\n", product.name, product.ref, product.qty, product.price, product.size);
    fflush(temp);
  }
  remove("products.txt");
  rename("temp.txt", "products.txt");
  printf("The remaining stock is : %d\n", shop_stock-calculate_stock());
}
