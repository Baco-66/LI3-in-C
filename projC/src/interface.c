#include "../include/interface.h"

struct sgv{
	ClientCatalog* clientCatalog;
	ProductCatalog productCatalog;
	Faturacao fat;
	Venda filial[ID][MONTH];
};

SGV initSGV(){
	SGV sgv = {NULL};
	static struct sgv system;
	system.clientCatalog = initCliCat();
	system.productCatalog = initProdCat();
	system.fat = NULL;
	sgv = &system;
	return sgv;
}

extern SGV sgv;

void destroySGV(SGV sgv){
	if(sgv!=NULL){
		if(sgv->clientCatalog != NULL){
			freeCliCat(sgv->clientCatalog);
			sgv->clientCatalog = NULL;
		}
		if(sgv->productCatalog != NULL){
			freeProdCat(sgv->productCatalog);
			sgv->productCatalog = NULL;
		}
		if(sgv->fat != NULL){
			freeFatCat(sgv->fat);
			sgv->fat = NULL;
		}
	freeFilial(sgv->filial);
	sgv=NULL;
	}
}

Faturacao createFaturacao(){
	int size = getProdCatSize(sgv->productCatalog);
	char** list = getProductCat(sgv->productCatalog);
	sgv->fat = initFatCat(list, 0, size-1);

	return sgv->fat;
}

/******QUERIE1******/

SGV loadSGVFromFiles(char* clientsFilePath, char* productsFilePath, char* salesFilePath){
	
	sgv = initSGV();	
	readClientsFile(clientsFilePath, sgv->clientCatalog);
	readProductsFile(productsFilePath, sgv->productCatalog);
	sgv->fat = createFaturacao();
	readSalesFile(salesFilePath, sgv->clientCatalog, sgv->productCatalog, sgv->fat, sgv->filial);

	return sgv;
}

/*******************/
/******QUERIE2******/

DArray getProductSartedByLetter(SGV sgv, char c){
	
	DArray new = malloc(sizeof(struct arrayD)); /*Allocates memory for the result struct*/
	new->list = NULL; /*Sets the struct's char** to NULL to avoid random items inside*/
	new->size = 0; /*As we start on the struct it has 0 elements*/
	
	int i = 0; /*Iterational variable*/

	char s = getProdStart(sgv->productCatalog,i); /*s will be the starting letter for the product Codes read from the catalog*/
	int sizeOfCat = getProdCatSize(sgv->productCatalog); /*calculates the amount total products on SGV*/

	while(s != c && i < sizeOfCat){ /*While s is diffferent from the letter we're looking for, skip*/
		i++;
		s = getProdStart(sgv->productCatalog,i);
	}

	while(s == c && i < sizeOfCat){ /*While s == the letter we're looking for, we save every code to the struct*/
		new->list = realloc(new->list,sizeof(char*)*(new->size+1));
		new->list[new->size] = malloc(sizeof(char)*8);
		strcpy(new->list[new->size],getProdCode(sgv->productCatalog,i));
		i++;
		new->size++;
		s = getProdStart(sgv->productCatalog,i);
	}

	return new; /*Returns the list of products as well as the amount of products found*/
}


/*******************/
/******QUERIE3******/

Fatura* getProductSalesAndProfit(SGV sgv, char* productID, int month){
	Fatura* result = malloc(sizeof(Fatura)*6);
	int i;
	for(i = 0; i< 6; i++){
		result[i] = (Fatura)calloc(1,sizeof(struct fatura));
	}
	Q3(sgv->fat, month, productID, result);
	return result;
}

/*******************/
/******QUERIE4******/

DArray getProductsNeverBought(SGV sgv, int branchID){
	DArray result = (DArray)malloc(sizeof(struct arrayD));
	result->list = NULL;
	result->size = 0;

	Q4(sgv->fat, branchID, result);
	return result;
}

/*******************/
/******QUERIE5******/

DArray getClientsOfAllBranches(SGV sgv){
	DArray result = (DArray)malloc(sizeof(struct arrayD));
	result->list = NULL;
	result->size = 0;

	char clientCode[6];
	int it = 0;
	int i, j, return_value;
	while(iteratorClientCatalog(sgv->clientCatalog, it)){
		return_value = 1;
		strcpy(clientCode, iteratorClientCatalog(sgv->clientCatalog, it));
		for(i = 0; i < ID && return_value; i++){
			return_value = 0;
			for(j = 0; j<MONTH && !return_value; j++){
				if(findClientSales(sgv->filial[i][j], clientCode) != NULL){
					return_value = 1;
				}
			}
		}
		it++;
		if(return_value){
			result->list = realloc(result->list, sizeof(char*)*(result->size+1));
			result->list[result->size] = malloc(sizeof(char)*8);
			strcpy(result->list[result->size], clientCode);
			result->size++;
		}
	}
}

/*******************/
/******QUERIE6******/

void getProductsNeverBoughtCount(SGV sgv){
	return Q6Fat(sgv->fat);
}

void getClientsNeverBoughtCount(SGV sgv){
	int size = getSizeCatalog(sgv->clientCatalog);
	int i, j;
	for(i = 0; i < ID; i++){
		for(j = 0; j<MONTH; j++){
			size = Q6aux(sgv->filial[i][j], size);
		}
	}
}

/*******************/
/******QUERIE7******/

void doQuerySete(SGV sgv){
	char codeClient[6];
	if(scanf("%s",codeClient)== 6){
		int quantity[ID][MONTH];
		Q7(sgv->filial, codeClient, quantity);
		outPrintQ7(quantity);
	}
}

/*******************/
/******QUERIE8******/

Fatura* getProductSalesAndProfit(SGV sgv, char* productID, int month){
	Fatura* result = malloc(sizeof(Fatura));
	Q3(sgv->fat, month, 0, result);
	return result;
}

/*******************/
/******QUERIE9******/



/*
char* getProdFromFatIndex(SGV sgv, int i){
	char* new = malloc(sizeof(char)*8);
	strcpy(new,getProdFromFatIndexAux(sgv->fat,i));
	return new;
}

int getFatSize(SGV sgv){
	int size = getFatSizeAux(sgv->fat);
	return size;
}

int getMonthFromFat(SGV sgv, int i){
	int month = getMonthFromFatAux(sgv->fat,i);
	return month;
}

int getNrSalesN(SGV sgv, int i){
	int qtd = getNrSalesAuxN(sgv->fat,i);
	return qtd;
}

int getNrSalesP(SGV sgv, int i){
	int qtd = getNrSalesAuxP(sgv->fat,i);
	return qtd;
}

float getIncomeN(SGV sgv, int i){
	float res = getIncomeNAux(sgv->fat,i);
	return res;
}

float getIncomeP(SGV sgv, int i){
	float res = getIncomePAux(sgv->fat,i);
	return res;
}
*/

