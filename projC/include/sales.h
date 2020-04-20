#ifndef sales_h
#define sales_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/clients.h"
#include "../include/products.h"
#include "../include/billing.h"
#include "../include/filial.h"

int saleValid(float price, int soldUtd, char* discount, int month, int id);

void salesToStructs(char* saleLine, ProductCatalog prodCat, ClientCatalog* cliCat, Faturacao fat, Venda filial[ID][MONTH], int vendasProcessadas[ID][MONTH]);

void readSalesFile(char* filePath, ClientCatalog* cliCat, ProductCatalog prodCat, Faturacao fat, Venda filial[ID][MONTH]);

#endif
