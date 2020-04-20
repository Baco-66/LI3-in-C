#ifndef products_h
#define products_h

typedef struct productCatalog *ProductCatalog;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/billing.h"

ProductCatalog initProdCat();

void freeProdCat(ProductCatalog prodCat);

int comparatorProd(const void* a, const void* b);

void sortProd(char** catalog, int size);

int validateProduct(const char* productCode);

void readProductsFile(char* filePath, ProductCatalog prodCat);

int existsProd(char* arg, ProductCatalog prodCat);

void printProdCat(ProductCatalog productCatalog);

char getProdStart(ProductCatalog prodCat, int i);

int getProdCatSize(ProductCatalog prodCat);

char* getProdCode(ProductCatalog prodCat, int i);

char** getProductCat(ProductCatalog productCatalog);

#endif