#ifndef filial_h
#define filial_h

#define MONTH 12
#define ID 3

typedef struct venda *Venda;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeFilial(Venda filial[ID][MONTH]);
void freeVenda(Venda bTree);

void addSaleToFilial(Venda filial[ID][MONTH], char* prodCode, float price, int soldQtd, char discount, char* clientCode, int month, int idStore);

void filialToBTree(Venda filial[ID][MONTH], int size[ID][MONTH]);
Venda vendaToBTree(Venda bTree, int size);
Venda mergSortVenda(Venda venda, int* size);

int Q6aux(Venda venda,int size);

void Q7(Venda filial[ID][MONTH], char* clientCode, int quantity[ID][MONTH]);

Venda findClientSales (Venda bTree, char* clientCode);

/*
void queryDoze(Venda filial[ID][MONTH], char* clientCode, int N, char* (*result)[N]);
*/
#endif
