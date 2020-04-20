#ifndef billing_h
#define billing_h

typedef struct billing *Faturacao;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sales.h"
#include "../include/interface.h"

#define MaxNrSales 1000000

Faturacao initFatCat(char** list, int start, int end);

void freeFatCat(Faturacao fat);


/*
int comparatorFat(const void* a, const void* b);
void sortFat(Faturacao fat);
char* getProdFromFatIndexAux(Faturacao fat, int i);
int getFatSizeAux(Faturacao fat);
int getMonthFromFatAux(Faturacao fat, int i);
int getNrSalesAuxN(Faturacao fat, int i);
int getNrSalesAuxP(Faturacao fat, int i);
float getIncomeNAux(Faturacao fat, int i);
float getIncomePAux(Faturacao fat, int i);
*/

void addSaleToBilling(Faturacao fat, char* prodCode, float price, int soldQtd, char discount, int month, int filial);

Faturacao pesquisaProduto (Faturacao fat, char* product);

void Q3(Faturacao fat, int month, char* prod, Fatura *result);
void Q4(Faturacao fat, int filial, DArray result);
int Q6Fat(Faturacao fat);

#endif
