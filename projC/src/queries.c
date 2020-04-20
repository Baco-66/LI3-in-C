#include "../include/queries.h"

/*
 * Querie 3
*/
/*
Q3* getProductsSalesAndProfitGlobal(SGV sgv, char* productID, int month){

	Q3* new = malloc(sizeof(struct q3));
	new->productCode = malloc(sizeof(char)*8);
	strcpy(new->productCode,productID);
	new->soldQtdN = 0;
	new->soldQtdP = 0;
	new->incomeN = 0.0;
	new->incomeP = 0.0;
	new->month = month;

	int i = 0;

	char* aux = malloc(sizeof(char)*8);
	strcpy(aux,getProdFromFatIndex(sgv,i));
	int sizeOfFat = getFatSize(sgv);
	
	puts(aux);
	printf("%d\n",sizeOfFat);
	
	while((strcmp(aux,productID) != 0) && i < sizeOfFat){
		i++;
		strcpy(aux,getProdFromFatIndex(sgv,i));
	}

	if((strcmp(aux,productID) == 0) && (getMonthFromFat(sgv,i) == month) && i < sizeOfFat){
		
			new->soldQtdN += getNrSalesN(sgv,i);
			new->soldQtdP += getNrSalesP(sgv,i);
			new->incomeN += getIncomeN(sgv,i);
			new->incomeP += getIncomeP(sgv,i);
		
	}

	free(aux);

	return new;
}
*/
/*
	Falta guardar os cliencodes validos 
*/


void Q6(Venda filial[ID][MONTH], ClientCatalog* clientCatalog){
	int size = getSizeCatalog(clientCatalog);
	int i, j;
	for(i = 0; i < ID; i++){
		for(j = 0; j<MONTH; j++){
			size = Q6aux(filial[i][j], size);
		}
	}
}

/*
	Query nº 9
*/

/*int prodNotSold(SalesCatalog* salesCatalog, ProductCatalog* productCatalog, ProductCatalog* notSoldCatalog){
	
	char codProd[7];
	for(int i = 0; i < productCatalog->size; i++){
		strcpy(codProd, productCatalog->list[i]);
		if(!lookForProdct(codProd, saleCatalog)){
			notSoldCatalog->list = realloc(notSoldCatalog->list, (notSoldCatalog->size+1)*(sizeof(char*)));
			notSoldCatalog->list[notSoldCatalog->size] = malloc(sizeof(char)*MAX);
			strcpy(notSoldCatalog->list[notSoldCatalog->size],codProd); 
			notSoldCatalog->size++;
		}
	}
	return 0;	
}*/

/*
int lookForProdct(char codProd[7], SaleCatalog* saleCatalog){
	int return_value = 0;
	int i;
	for(i = 0; i < saleCatalog->size; i++){
		printf("%d \n",i);
		printf("%s\n",(saleCatalog->list[i]).codeproduct);
		if(strcmp(codProd,(saleCatalog->list[i]).codeproduct) == 0){
			return_value = 1;
			break;
		}
	}
	return return_value;
}
*/
