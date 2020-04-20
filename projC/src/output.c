#include "../include/output.h"

void outPrintMenu(){
	puts("---------------------------");
	puts("1- Ler os ficheiros de Clientes, Produtos e Vendas.\n");
	puts("2- Mostrar o total e a lista de Produtos começados por uma certa letra.\n");
	puts("3- Mostrar o numero total de vendas de um Produto num determinado mes.\n");
	puts("4- Mostrar a list de Produtos não comprados bem como o seu numero total.\n");
	/*Introduzir restantes opções*/
	puts("0- Fechar o sistema.\n");
	puts("---------------------------");

}

void outPrintDefault(){
	printf("Invalid input, please try again\n");
}

void printQ2 (DArray q2, char c){

	int i = 0; 				/*Iterable variable used to go through the list of char* given by DArray q2*/
	int j; 					/*Superior limit of elements printed by page. Default value set to 50.*/	
	int pag = 0;			/*Variable that indicates the page we're currenlty looking at.*/
	char control = 49;      /*Default value is 1, if changed to 0, exits the function*/

	printf("%d produtos foram encontrados a começar pela letra %c\n",q2->size,c);
	
	while(control != '0'){ /*control will only be '0' if we give it the instruction to close the function*/
		printf("---Page %d---\n",pag); /*Prints the page number*/

		for(j = i+50; i < q2->size && i < j; i++){ /* This bit is responsible for printing 50 consecutive elements of the resultant struct.                               */
			printf("%d -> %s\n",i,q2->list[i]);    /* It will print either 50 elements or enough to finish printing the char** list on the struct, whichever comes first. */
		}

		if(pag == 0){ /*If we are on the 1st page, we can't see the previous page - there isn't one.*/
			printf("Escreva 2 para ver a página seguinte e 3 para fechar.\n");	
			
			control = getchar();
			getchar(); /*Corrige o erro de ler o "\n"*/

			switch(control){
				case 50: 					/*ASCII code for '2'*/
					pag++; 					/*page incrementer*/
					i = (pag)*50;			/*the first element on page n is the n*50th element of the list*/
					break;

				case 51: 					/*ASCII code for '3'*/
					control = '0';			/*Command to exit*/
					puts("Saindo.");		/*Exiting warning*/
					break;

				default: 
					puts("Invalid code."); 	/*If it receives an invalid input, prints the same page again*/
					i = i-50;
					break;
			}
		}
		else if(pag == ((q2->size/50))){ /*If we are on the last page, we can't see the next one - there isn't one.*/
			printf("Escreva 1 para ver a página anterior e 3 para fechar.\n");
			
			control = getchar();
			getchar(); /*Corrige o erro de ler o "\n"*/

			switch(control){
				case 49: 					/*ASCII code for '1'*/
					pag--;					/*page decrementer*/
					i = (pag)*50;			/*the first element on page n is the n*50th element of the list*/
					break;
				case 51: 					/*ASCII code for '3'*/
					control = '0';			/*Command to exit*/
					puts("Saindo.");        /*Exiting warning*/
					break;

				default: 
					puts("Invalid code."); /*If it receives an invalid program, prints the same page again*/
					i = i-50;
					break;
			}
		}
		else{ /*In case we can see both the previous and next pages*/
			printf("Escreva 1 para ver a página anterior, 2 para ver a página seguinte e 3 para fechar.\n");
			
			control = getchar();
			getchar(); /*Corrige o erro de ler o "\n"*/

			switch(control){
				case 49:   					/*ASCII code for '1'*/
					pag--;					/*page decrementer*/
					i = (pag)*50;			/*the first element on page n is the n*50th element of the list*/
					break;

				case 50:					/*ASCII code for '2'*/ 
					pag++;					/*page incrementer*/
					i = (pag)*50;		    /*the first element on page n is the n*50th element of the list*/
					break;

				case 51:         			/*ASCII code for '3'*/	
					control = '0'; 			/*Command to exit*/
					puts("Saindo.");		/*Exiting warning.*/
					break;
					
				default: 
					puts("Invalid code."); /*If it receives an invalid program, prints the same page again*/
					i = i-50;
					break;
			}
		}
	}
}

void printQ3G (Fatura* result, char* product, int month){
	int totalN, totalP;
	float fatN, fatP;
	totalN = result[0]->entry + result[2]->entry + result[4]->entry;
	fatN = result[0]->faturado + result[2]->faturado + result[4]->faturado;
	totalP = result[1]->entry + result[3]->entry + result[5]->entry;
	fatP = result[1]->faturado + result[3]->faturado + result[5]->faturado;
	printf("Vendas do produto %s no mês %d para a faturação global.\n",product,month);
	printf("               N           P  \n");
	printf("total         %i          %i    \n", totalN , totalP);
	printf("faturado      %.2f       %.2f  \n",fatN,fatP);
}

void printQ3F (Fatura* result, char* product, int month){
	printf("Vendas do produto %s no mês %d para a faturação global.\n",product,month);
	int totalN, totalP;
	float fatN , fatP;
	totalN = result[0]->entry;
	fatN = result[0]->faturado;
	totalP = result[1]->entry;
	fatP = result[1]->faturado;
	printf("               N           P  \n");
	printf("total         %i          %i    \n", totalN , totalP);
	printf("faturado      %.2f       %.2f  \n",fatN,fatP);
	totalN = result[2]->entry;
	fatN = result[2]->faturado;
	totalP = result[3]->entry;
	fatP = result[3]->faturado ;
	printf("               N           P  \n");
	printf("total         %i          %i    \n", totalN , totalP);
	printf("faturado      %.2f       %.2f  \n",fatN,fatP);
	totalN = result[4]->entry;
	fatN = result[4]->faturado;
	totalP =  result[5]->entry;
	fatP =  result[5]->faturado;
	printf("               N           P  \n");
	printf("total         %i          %i    \n", totalN , totalP);
	printf("faturado      %.2f       %.2f  \n",fatN,fatP);
}

void printQ4 (DArray result){
	int i = 0; 				/*Iterable variable used to go through the list of char* given by DArray q2*/
	int j; 					/*Superior limit of elements printed by page. Default value set to 50.*/	
	int pag = 0;			/*Variable that indicates the page we're currenlty looking at.*/
	char control = 49;      /*Default value is 1, if changed to 0, exits the function*/

	printf("Foram encontrados %d produtos que nunca foram vendidos.\n",result->size);
	
	while(control != '0'){ /*control will only be '0' if we give it the instruction to close the function*/
		printf("---Page %d---\n",pag); /*Prints the page number*/

		for(j = i+50; i < result->size && i < j; i++){ /* This bit is responsible for printing 50 consecutive elements of the resultant struct.                               */
			printf("%d -> %s\n", i, result->list[i]);    /* It will print either 50 elements or enough to finish printing the char** list on the struct, whichever comes first. */
		}

		if(pag == 0){ /*If we are on the 1st page, we can't see the previous page - there isn't one.*/
			printf("Escreva 2 para ver a página seguinte e 3 para fechar.\n");	
			
			control = getchar();
			getchar(); /*Corrige o erro de ler o "\n"*/

			switch(control){
				case 50: 					/*ASCII code for '2'*/
					pag++; 					/*page incrementer*/
					i = (pag)*50;			/*the first element on page n is the n*50th element of the list*/
					break;

				case 51: 					/*ASCII code for '3'*/
					control = '0';			/*Command to exit*/
					puts("Saindo.");		/*Exiting warning*/
					break;

				default: 
					puts("Invalid code."); 	/*If it receives an invalid input, prints the same page again*/
					i = i-50;
					break;
			}
		}
		else if(pag == ((result->size/50))){ /*If we are on the last page, we can't see the next one - there isn't one.*/
			printf("Escreva 1 para ver a página anterior e 3 para fechar.\n");
			
			control = getchar();
			getchar(); /*Corrige o erro de ler o "\n"*/

			switch(control){
				case 49: 					/*ASCII code for '1'*/
					pag--;					/*page decrementer*/
					i = (pag)*50;			/*the first element on page n is the n*50th element of the list*/
					break;
				case 51: 					/*ASCII code for '3'*/
					control = '0';			/*Command to exit*/
					puts("Saindo.");        /*Exiting warning*/
					break;

				default: 
					puts("Invalid code."); /*If it receives an invalid program, prints the same page again*/
					i = i-50;
					break;
			}
		}
		else{ /*In case we can see both the previous and next pages*/
			printf("Escreva 1 para ver a página anterior, 2 para ver a página seguinte e 3 para fechar.\n");
			
			control = getchar();
			getchar(); /*Corrige o erro de ler o "\n"*/

			switch(control){
				case 49:   					/*ASCII code for '1'*/
					pag--;					/*page decrementer*/
					i = (pag)*50;			/*the first element on page n is the n*50th element of the list*/
					break;

				case 50:					/*ASCII code for '2'*/ 
					pag++;					/*page incrementer*/
					i = (pag)*50;		    /*the first element on page n is the n*50th element of the list*/
					break;

				case 51:         			/*ASCII code for '3'*/	
					control = '0'; 			/*Command to exit*/
					puts("Saindo.");		/*Exiting warning.*/
					break;
					
				default: 
					puts("Invalid code."); /*If it receives an invalid program, prints the same page again*/
					i = i-50;
					break;
			}
		}
	}
}

void printQ5 (DArray result){
	int i = 0; 				/*Iterable variable used to go through the list of char* given by DArray q2*/
	int j; 					/*Superior limit of elements printed by page. Default value set to 50.*/	
	int pag = 0;			/*Variable that indicates the page we're currenlty looking at.*/
	char control = 49;      /*Default value is 1, if changed to 0, exits the function*/

	printf("Foram encontrados %d clientes que compraram em todas as filiais.\n",result->size);
	
	while(control != '0'){ /*control will only be '0' if we give it the instruction to close the function*/
		printf("---Page %d---\n",pag); /*Prints the page number*/

		for(j = i+50; i < result->size && i < j; i++){ /* This bit is responsible for printing 50 consecutive elements of the resultant struct.                               */
			printf("%d -> %s\n", i, result->list[i]);    /* It will print either 50 elements or enough to finish printing the char** list on the struct, whichever comes first. */
		}

		if(pag == 0){ /*If we are on the 1st page, we can't see the previous page - there isn't one.*/
			printf("Escreva 2 para ver a página seguinte e 3 para fechar.\n");	
			
			control = getchar();
			getchar(); /*Corrige o erro de ler o "\n"*/

			switch(control){
				case 50: 					/*ASCII code for '2'*/
					pag++; 					/*page incrementer*/
					i = (pag)*50;			/*the first element on page n is the n*50th element of the list*/
					break;

				case 51: 					/*ASCII code for '3'*/
					control = '0';			/*Command to exit*/
					puts("Saindo.");		/*Exiting warning*/
					break;

				default: 
					puts("Invalid code."); 	/*If it receives an invalid input, prints the same page again*/
					i = i-50;
					break;
			}
		}
		else if(pag == ((result->size/50))){ /*If we are on the last page, we can't see the next one - there isn't one.*/
			printf("Escreva 1 para ver a página anterior e 3 para fechar.\n");
			
			control = getchar();
			getchar(); /*Corrige o erro de ler o "\n"*/

			switch(control){
				case 49: 					/*ASCII code for '1'*/
					pag--;					/*page decrementer*/
					i = (pag)*50;			/*the first element on page n is the n*50th element of the list*/
					break;
				case 51: 					/*ASCII code for '3'*/
					control = '0';			/*Command to exit*/
					puts("Saindo.");        /*Exiting warning*/
					break;

				default: 
					puts("Invalid code."); /*If it receives an invalid program, prints the same page again*/
					i = i-50;
					break;
			}
		}
		else{ /*In case we can see both the previous and next pages*/
			printf("Escreva 1 para ver a página anterior, 2 para ver a página seguinte e 3 para fechar.\n");
			
			control = getchar();
			getchar(); /*Corrige o erro de ler o "\n"*/

			switch(control){
				case 49:   					/*ASCII code for '1'*/
					pag--;					/*page decrementer*/
					i = (pag)*50;			/*the first element on page n is the n*50th element of the list*/
					break;

				case 50:					/*ASCII code for '2'*/ 
					pag++;					/*page incrementer*/
					i = (pag)*50;		    /*the first element on page n is the n*50th element of the list*/
					break;

				case 51:         			/*ASCII code for '3'*/	
					control = '0'; 			/*Command to exit*/
					puts("Saindo.");		/*Exiting warning.*/
					break;
					
				default: 
					puts("Invalid code."); /*If it receives an invalid program, prints the same page again*/
					i = i-50;
					break;
			}
		}
	}
}

void outPrintQ7(int quantity[ID][MONTH]){
	printf(".---,------,------,------,------,------,------,------,------,------,------,------,------.\n");
	printf("|   | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | 12   |\n");
	int i,j;
	for(i=0;i<ID;i++){
		printf("|---+------+------+------+------+------+------+------+------+------+------+------+------|\n");
		printf("| %d |",i+1);
		for(j=0;j<MONTH;j++){
			printf(" %d",quantity[i][j]);
			if (!quantity[i][j])
				quantity[i][j]++;
			while(quantity[i][j] <1000){
				quantity[i][j] *= 10;
				printf(" ");
			}
			printf(" |");
		}
		printf("\n");
	}
	printf("'---'------'------'------'------'------'------'------'------'------'------'------'------'\n");
}
/*
void printQ12(char* clientCode, int N, char* productCode[N]) {
	printf("%i produtos mais comprados pelo cliente %s\n", N, clientCode);
	int i;
	for(i=0;i<N;i++){
		if(productCode[i] != NULL){
			printf("%iº -%s\n",i ,productCode[i]);
		}
	}
}
*/