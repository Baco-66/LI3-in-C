#include "../include/interface.h"
#include "../include/output.h"

#define MAX 10

SGV sgv = NULL;

int menu(char* fileClients, char* fileProducts, char* fileSales){

	outPrintMenu();

	char q = 49;
	printf("Escolha a ação a realizar: ");
	
	q = getchar();
	getchar();

	printf("Performing task %c.\n",q);
	
	char c;
	char* product;
	int month = -1;

	switch(q){
		case 49: /* Escolha da querie 1 */
			destroySGV(sgv); /*Caso já exista um SGV, permite-nos limpar essa memória e criar um novo SGV*/
			/*
			falta pedir ficheiros de entrada;
			*/
			sgv = loadSGVFromFiles(fileClients,fileProducts,fileSales);
			puts("Ficheiros carregados com sucesso.");
			break;

		case 50: /* Escolha da querie 2 */
			if(sgv!= NULL){	
				puts("Procurar os produtos começados pela letra: ");
				
				c = getchar(); /*Lê a letra indicada pelo user*/
				getchar(); /*Corrige o erro de ledr o "\n"*/
				
				if(c >= 97 && c <= 122){ /*Se o char lido for minusculo, passa-o a maiuscula */
					c = c - 32; /*ASCII Code shananigans*/
				}
				DArray querie2 = getProductSartedByLetter(sgv,c); /*Execução da querie2*/
				
				printQ2(querie2,c); /*Processo de display dos resultados da execução da querie2*/
				
				free(querie2); /*Liberta a memória alocada para os resultados da querie2 */
			}else{
				printf("Por favor insira os ficheiros primeiro.\n");
			}

			break;

		case 51:
			if(sgv!= NULL){	

				product = malloc(sizeof(char)*8);
				puts("Procurar o produto: ");
				scanf("%s", product);
				getchar();

				puts("Procurar o mes: ");
				scanf("%d", &month);
				getchar();

				puts("Pretende ver o resultado global (1) ou filial (2)?");
				c = getchar();
				getchar();

				Fatura* result = getProductSalesAndProfit(sgv, product, month);
				
				if(c == '1'){
					printQ3G(result,product,month);	
				}
				else if(c == '2'){
					printQ3F(result,product,month);	
				} 
				else{
					puts("Invalid input");
				}
				int i;
				for(i = 0; i< 6; i++){
					free(result[i]);
					result[i] = NULL;
				}
				free(result);
				result = NULL;
				free(product);
				product = NULL;
			}
			else{
				puts("Por favor insira os ficheiros primeiro.");
			}

			break;
		
		case 52:
			if(sgv!= NULL){	
				puts("Pretende ver o resultado global (1) ou filial (2)?");
				
				c = getchar();
				getchar();
				
				DArray result = NULL;

				if(c == '1'){
					result =  getProductsNeverBought(sgv, 0);
					printQ4(result);
				}
				else if(c == '2'){
					puts("Pretende ver a lista de Produtos não vendidas relativa que filial? (1/2/3)");
					c = getchar();
					getchar();
					if(c == '1'){
						result = getProductsNeverBought(sgv, 1);
						printQ4(result);
					}
					else if(c == '2'){
						result = getProductsNeverBought(sgv, 2);
						printQ4(result);
					}
					else if(c == '3'){
						result = getProductsNeverBought(sgv, 3);
						printQ4(result);
					}
					else{
						puts("Invalid input");
					}
				}
			}else{
				printf("Por favor insira os ficheiros primeiro.\n");
			}
			break;

		case 53:
			if(sgv!= NULL){	
				DArray result = getClientsOfAllBranches(sgv);
				printQ5(result);
			}else{
				printf("Por favor insira os ficheiros primeiro.\n");
			}
			break;

		case 54:
			if(sgv!= NULL){	
				int getProductsNeverBoughtCount(SGV sgv);
				int getClientsNeverBoughtCount(SGV sgv);
			}else{
				printf("Por favor insira os ficheiros primeiro.\n");
			}
			break;

		case 55:
			if(sgv!= NULL){	
				void doQuerySete(SGV sgv)
			}else{
				printf("Por favor insira os ficheiros primeiro.\n");
			}
			doQuerySete();
			break;

		case 56:
			if(sgv!= NULL){	
			}else{
				printf("Por favor insira os ficheiros primeiro.\n");
			}
			break;

		case 57:
			if(sgv!= NULL){	
			}else{
				printf("Por favor insira os ficheiros primeiro.\n");
			}
			break;

		case 58:
			if(sgv!= NULL){	
			}
			else{
				printf("Por favor insira os ficheiros primeiro.\n");
			}
			break;

		case 59:
			if(sgv!= NULL){	
			}else{
				printf("Por favor insira os ficheiros primeiro.\n");
			}
			break;
			if(sgv!= NULL){}	

		case 60:
			if(sgv!= NULL){	
			}
			else{
				printf("Por favor insira os ficheiros primeiro.\n");
			}
			break;
			
		case 48:
			destroySGV(sgv);
			return 1;
			break;

		default:
			outPrintDefault();
			outPrintMenu();
			break;
	}

	return 0;
}

int main(){

	char* fileClients = "../input_files/Clientes.txt";
	char* fileProducts = "../input_files/Produtos.txt";
	char* fileSales = "../input_files/Vendas_1M.txt";
	
	int close = 0;
	while(close != 1){
		close = menu(fileClients, fileProducts, fileSales);
	}
	destroySGV(sgv);

	return 0;
}
