#include "../include/clients.h"

struct clientCatalog{
	char** list;
	int size;
};

#define BUFFERSIZE 64
#define MAX 10

ClientCatalog* initCliCat(){

	ClientCatalog* new = malloc(sizeof(ClientCatalog));
	new->list = NULL;
	new->size = 0;
	return new;	
}

void freeCliCat(ClientCatalog *cliCat){

	int i;
	for(i = 0; i < cliCat->size; i++){
		free(cliCat->list[i]);
		cliCat->list[i] = NULL;
	}

	free(cliCat->list);
	cliCat->list = NULL;

	free(cliCat);
	cliCat = NULL;
}


/*
 * Implements the rule of comparation of qsort to be called on sort.
 */

int comparatorClient(const void* a, const void* b){

	return strcmp(*(const char**)a, *(const char**)b);
}


/*
 *Function that calls qsort with the desired catalog, using the comparator defined above.
 */

void sortClient(char** catalog, int size){

	qsort(catalog,size,sizeof(const char*), comparatorClient);
	printf("Catalog sorted!\n");
}


/*
 * Checks if the given clientCode is valid by analyzing it's format (1 Upper case letter + 4 numbers)
 */

int validateClient(const char* clientCodeArg){

	return strlen(clientCodeArg) == 5 && isupper(clientCodeArg[0]) && isdigit(clientCodeArg[1]) && isdigit(clientCodeArg[2]) 
									  							   && isdigit(clientCodeArg[3]) && isdigit(clientCodeArg[4]);
}


/*
 * Function resposible for reading the Clientes.txt file containing the Client Number
 * and allocate all the valid Client Codes to the clientCatalog.
 */

void readClientsFile(char* filePath, ClientCatalog* cliCat){

	FILE* fileClients = fopen(filePath,"r");
	
	if(fileClients == NULL){

		puts("Erro na leitura do file!");
	
	}
	else {
		char buffer[BUFFERSIZE]; 

		while(fgets(buffer, BUFFERSIZE,fileClients)){

			char* code = strtok(buffer,"\r\n");
			if(validateClient(buffer)){ 
				cliCat->list = realloc(cliCat->list, (cliCat->size+1)*(sizeof(char*)));
				cliCat->list[cliCat->size] = malloc(sizeof(char)*MAX);
				strcpy(cliCat->list[cliCat->size],code);
				cliCat->size++;
			}
		}

		sortClient(cliCat->list,(cliCat->size));
		fclose(fileClients);
		fileClients = NULL;
	}
}

int PesquisaBinaria (char** list, char* arg, int size)
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

int existsClient(char* arg, ClientCatalog* cliCat){
	if(!validateClient(arg)) return 0;
	else{
		int ret = PesquisaBinaria(cliCat->list, arg, cliCat->size);
		if(ret == 0) return 0;
		return 1;
	}
}

/*
 *	Prints the catalog os clients.
 */

void printCliCat(ClientCatalog* clientCatalog){
		printf("Printing Client Catalog:\n");
		int i;
		for(i = 0 ; i < clientCatalog->size ; i++){
			printf("%s\n", clientCatalog->list[i] );
		}
}

int getSizeCatalog(ClientCatalog* clientCatalog){
	return clientCatalog->size;
}

/*
	Iterates the array of clients
*/

char* iteratorClientCatalog(ClientCatalog* clientCatalog, int iterator){
	if(iterator < clientCatalog->size){
		return clientCatalog->list[iterator];
	}else{
		return NULL;
	}
}
