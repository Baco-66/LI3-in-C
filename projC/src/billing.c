#include "../include/billing.h"

typedef struct bill{
	int entryN;
	float faturadoN;
	int entryP;
	float faturadoP;
	int quantity;
} *Bill;

struct billing{
	char product[7];
	Bill list[3][12];
	struct billing* left;
	struct billing* right;
};


/*
	Precisa de receber size-1
*/
Faturacao initFatCat(char** list, int start, int end) { 

    if (start > end) 
    	return NULL; 

    int meio = (start + end)/2; 

	Faturacao new = calloc(1, sizeof(struct billing));
	strcpy(new->product, list[meio]);
	int i, j;
	for(i = 0; i<3; i++){
		for(j=0;j<12;j++){
			new->list[i][j] = NULL;
		}
	}

	new->right = initFatCat(list, start, meio-1); 

	new->left = initFatCat(list, meio+1, end);
    
    return new; 
} 

void freeFatCat(Faturacao fat){
	if(fat != NULL){
		freeFatCat(fat->left);
		freeFatCat(fat->right);
		int i,j;
		for(i=0; i<3; i++){
			for(j=0;j<12;j++){
				if(fat->list[i][j] != NULL){
					free(fat->list[i][j]);
				}
			}
		}
		free(fat);
	}
}

Faturacao pesquisaProduto (Faturacao fat, char* product){
	if(fat != NULL){
		if(strcmp(product, fat->product)<0){
			fat = pesquisaProduto(fat->right, product);
		}else{
			if(strcmp(product, fat->product)>0){
				fat = pesquisaProduto(fat->left, product);
			}
		}
	}
	return fat;
}

/*
 * Adds the info relative to the sale to the BILLING
 */

void addSaleToBilling(Faturacao fat, char* prodCode, float price, int soldQtd, char discount, int month, int filial){

	fat = pesquisaProduto(fat, prodCode);
	if(fat != NULL){
		if (fat->list[filial-1][month-1] == NULL){
			fat->list[filial-1][month-1] = calloc(1,sizeof(struct bill));
		}
		if(discount == 'P'){
			fat->list[filial-1][month-1]->entryP++;
			fat->list[filial-1][month-1]->faturadoP += price*soldQtd;
		}else{
			fat->list[filial-1][month-1]->entryN++;
			fat->list[filial-1][month-1]->faturadoN += price*soldQtd;
		}
		fat->list[filial-1][month-1]->quantity += soldQtd;
	}else{
		printf("error\n");
	}
}

void Q3(Faturacao fat, int month, char* prod, Fatura *result){
	fat = pesquisaProduto(fat, prod);
	if(fat == 0){
		int i, j;
		for(i = 0; i<3; i++){
			if(fat->list[i][month-1] != NULL){
				result->entry += fat->list[i][month-1]->entryN;
				result->faturado += fat->list[i][month-1]->faturadoN;
				result->entry += fat->list[i][month-1]->entryP;
				result->faturado += fat->list[i][month-1]->faturadoP;
			}
		}
	}else{
		if(fat != NULL){
			int i;
			for(i = 0; i<3; i+=2){
				if(fat->list[i][month-1] != NULL){
					result[i]->entry += fat->list[i][month-1]->entryN;
					result[i]->faturado += fat->list[i][month-1]->faturadoN;
					result[i+1]->entry += fat->list[i][month-1]->entryP;
					result[i+1]->faturado += fat->list[i][month-1]->faturadoP;
				}
			}
		}
	}
}

char* existeBill(Faturacao fat, int filial){
	int i, j;
	if(filial == 0){
		for(i=0;i<3;i++){
			for(j=0;j<12;j++){
				if(fat->list[i][j] != NULL){
					return NULL;
				}
			}
		}
	}else{
		for(j=0;j<12;j++){
			if(fat->list[filial-1][j] != NULL){
				return NULL;
			}
		}
	}
	return fat->product;
}

void Q4(Faturacao fat, int filial, DArray result){
	if(fat != NULL){
		if(existeBill(fat, filial) != NULL){
			result->list = realloc(result->list, sizeof(char*)*(result->size+1));
			result->list[result->size] = malloc(sizeof(char)*8);
			strcpy(result->list[result->size], existeBill(fat, filial));
			result->size++;
		}
		Q4(fat->right, filial, result);
		Q4(fat->left, filial, result);
	}
}



int Q6Fat(Faturacao fat){
	int result = 0;
	if(fat != NULL){
		if(existeBill(fat, 0)){
			result++;
		}
		result = Q6Fat(fat->right);
		result = Q6Fat(fat->left);	
	}
	return result;
}
