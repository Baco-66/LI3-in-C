#ifndef clients_h
#define clients_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

typedef struct clientCatalog ClientCatalog;

ClientCatalog* initCliCat();

void freeCliCat(ClientCatalog *cliCat);

int comparatorClient(const void* a, const void* b);

void sortClient(char** catalog, int size);

int validateClient(const char* clientCodeArg);

void readClientsFile(char* filePath, ClientCatalog* cliCat);

int existsClient(char* arg, ClientCatalog* cliCat);

void printCliCat(ClientCatalog* clientCatalog);

int getSizeCatalog(ClientCatalog* clientCatalog);

char* iteratorClientCatalog(ClientCatalog* clientCatalog, int iterator);

#endif