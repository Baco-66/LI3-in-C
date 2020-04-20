#include "../include/sales.h"

#define BUFFERSIZE 64

int saleValid(float price, int soldUtd, char* discount, int month, int id){
	if(price < 0.0 || price > 1000.0 || soldUtd < 0 || soldUtd > 200 || (discount[0] != 'N' && discount[0] != 'P') || month < 1 || month > 12 || id < 1 || id > 3) return 0;
	return 1;
}

void salesToStructs(char* saleLine, ProductCatalog prodCat, ClientCatalog* cliCat, Faturacao fat, Venda filial[ID][MONTH], int vendasProcessadas[ID][MONTH]){

	char *codeproduct = strtok(saleLine, " ");
	float price = atof(strtok(NULL," "));
	int soldUtd = atoi(strtok(NULL," "));
	char *discount = strtok(NULL," ");
	char *clientcode = strtok(NULL," ");
	int month = atoi(strtok(NULL," "));
	int idstore = atoi(strtok(NULL,"\0"));

	if(existsClient(clientcode, cliCat) && existsProd(codeproduct, prodCat) && saleValid(price,soldUtd,discount,month,idstore)){
		if(fat != NULL){
			addSaleToBilling(fat, codeproduct, price, soldUtd, discount[0], month, idstore);
		}
		addSaleToFilial(filial, codeproduct, price, soldUtd, discount[0], clientcode, month, idstore);
		vendasProcessadas[idstore-1][month-1]++;
	}
}

/*
 * Function resposible for reading the Vendas_1M.txt file containing the Sales list
 * and allocate all the valid sales to the billing. Returns the amount of valid sales.
 */

void readSalesFile(char* filePath, ClientCatalog* cliCat, ProductCatalog prodCat, Faturacao fat, Venda filial[ID][MONTH]){

	FILE* fileSales = fopen(filePath,"r");

	if(fileSales == NULL){

		puts("Erro na leitura do ficheiro!\n");

	} else {
		char buffer[BUFFERSIZE];
		int vendasProcessadas[ID][MONTH] = {0};

		while(fgets(buffer, BUFFERSIZE, fileSales)){

			char *saleNew = strtok(buffer,"\r\n");

			/*Passar info para a billing e filial*/
			salesToStructs(saleNew, prodCat, cliCat, fat, filial, vendasProcessadas);
			
		}
		printf("Catalog sorted!\n");
		filialToBTree(filial, vendasProcessadas);
		fclose(fileSales);
		fileSales = NULL;
		
	}
}
