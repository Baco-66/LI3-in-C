#ifndef output_h
#define output_h

#include <stdio.h>
#include <stdlib.h>
#include "../include/interface.h"

void outPrintMenu();

void outPrintDefault();

void printQ2 (DArray q2, char c);

void printQ3G (Fatura* result, char* product, int month);

void printQ3F (Fatura* result, char* product, int month);

void printQ4 (DArray result);

void printQ5 (DArray result);

void outPrintQ7(int quantity[ID][MONTH]);
/*
void printQ12(char* clientCode, int N, char* productCode[N]);
*/
#endif
