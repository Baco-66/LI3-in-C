#include "../include/products.h"

struct productCatalog{
	char** list;
	int size;
};

#define BUFFERSIZE 64
#define MAX 10


ProductCatalog initProdCat(){

	ProductCatalog new = calloc(1,sizeof(struct productCatalog));
	return new;
}

void freeProdCat(ProductCatalog prodCat){
	
	int i;

	for(i = 0; i < prodCat->size; i++){
		free(prodCat->list[i]);
		prodCat->list[i] = NULL;
	}

	free(prodCat->list);
	prodCat->list = NULL;

	free(prodCat);
	prodCat = NULL;
}


/*
 * Implements the rule of comparation of qsort to be called on sort.
 */

int comparatorProd(const void* a, const void* b){

	return strcmp(*(const char**)a, *(const char**)b);
}


/*
 *Function that calls qsort with the desired catalog, using the comparator defined above.
 */

void sortProd(char** catalog, int size){

	qsort(catalog,size,sizeof(const char*), comparatorProd);
	printf("Catalog sorted!\n");
}


/*
 * Checks if the given productCode is valid by analyzing it's format (2 Upper case letter + 4 numbers)
 */

int validateProduct(const char* productCode){

	return strlen(productCode) == 6 && isupper(productCode[0]) && isupper(productCode[1]) && isdigit(productCode[2]) && isdigit(productCode[3]) && isdigit(productCode[4]) && isdigit(productCode[5]);
}


/*
 * Function resposible for reading the Produtos.txt file containing the Product number
 * and allocate all the valid Product Codes to the productCatalog.
 */

void readProductsFile(char* filePath, ProductCatalog prodCat){

	FILE* fileProducts = fopen(filePath,"r");
	
	if(fileProducts == NULL){

		puts("Erro na leitura do file!");
	
	}else {
		char buffer[BUFFERSIZE]; 

		while(fgets(buffer, BUFFERSIZE,fileProducts)){ 

			char* code = strtok(buffer,"\r\n");
			if(validateProduct(buffer)){ 
				prodCat->list = realloc(prodCat->list, (prodCat->size+1)*(sizeof(char*)));
				prodCat->list[prodCat->size] = malloc(sizeof(char)*MAX);
				strcpy(prodCat->list[prodCat->size],code); 
				prodCat->size++;
			}
		}

		sortProd(prodCat->list,(prodCat->size)-1);

		fclose(fileProducts);
		fileProducts = NULL;
	}

}



/*
 * Implements a binary search to increase performance.
 */

int PesquisaBinariaP (char** list, char* arg, int size)
{
     int inf = 0;  
     int sup = size-1;
     int meio;
     int flag = 0;
     while (inf <= sup && flag == 0)
     {
          meio = (inf + sup)/2;
          if (strcmp(arg,list[meio]) == 0){
               flag = 1;
               return flag;
          }
          if (strcmp(arg,list[meio]) < 0)
               sup = meio-1;
          else
               inf = meio+1;
     }
     return flag;  
}



/*
 * Checks if a Client Code is valid and belongs to the catalog.
*/

int existsProd(char* arg, ProductCatalog prodCat){
	
	int ret = PesquisaBinariaP(prodCat->list,arg,prodCat->size);
	if(ret == 0) return 0;
	return 1;
}

/*
 *	Prints the catalog os products.
 */

void printProdCat(ProductCatalog productCatalog){
		printf("Printing Product Catalog:\n");
		int i;
		for(i = 0 ; i < productCatalog->size ; i++){
			printf("%s\n", productCatalog->list[i] );
		}
}

char getProdStart(ProductCatalog prodCat, int i){
	char c = prodCat->list[i][0];
	return c;
}

int getProdCatSize(ProductCatalog prodCat){
	int sizeN = prodCat->size;
	return sizeN;
}

char* getProdCode(ProductCatalog prodCat, int i){
	char* new = malloc(sizeof(char)*8);
	strcpy(new,prodCat->list[i]);
	return new;
}

char** getProductCat(ProductCatalog productCatalog){
	return productCatalog->list;
}