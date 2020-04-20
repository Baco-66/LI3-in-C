#ifndef interface_h
#define interface_h

typedef struct sgv *SGV;

struct arrayD{
	char** list;
	int size;
};

typedef struct arrayD *DArray;

struct fatura{
	int entry;
	float faturado;
	int quantity;
} ;

typedef struct fatura *Fatura;


#define MONTH 12
#define ID 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/clients.h"
#include "../include/products.h"
#include "../include/billing.h"
#include "../include/sales.h"
#include "../include/filial.h"
#include "../include/output.h"

SGV initSGV();

void destroySGV(SGV sgv);

SGV loadSGVFromFiles(char* clientsFilePath, char* productsFilePath, char* salesFilePath);

DArray getProductSartedByLetter(SGV sgv, char c); /*Querie2*/

Fatura* getProductSalesAndProfit(SGV sgv, char* productID, int month);

DArray getProductsNeverBought(SGV sgv, int branchID);

DArray getClientsOfAllBranches(SGV sgv);

/*char* getProdFromFatIndex(SGV sgv, int i);

int getFatSize(SGV sgv);

int getMonthFromFat(SGV sgv, int i);

int getNrSalesN(SGV sgv, int i);

int getNrSalesP(SGV sgv, int i);

float getIncomeN(SGV sgv, int i);

float getIncomeP(SGV sgv, int i);
*/
#endif


