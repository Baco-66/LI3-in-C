#include "../include/filial.h"

/*
	Estrutura que guarda informação das vendas.
	Esta estrutura é uma arvore binaria com 5 elementos de data;
*/
typedef struct productDetails{
	char product[7];
	float price;
	int quantity;
	char discount;
	struct productDetails* next;
} *Data;

struct venda {
	char clientcode[6]; 
	struct productDetails* data;
	struct venda* right;
	struct venda* left;
};


/*
	Funçao que adiciona uma struct venda* a estrutura filial.
	A nova Venda é colocada no ramo mais a esquerda;
*/
void addSaleToFilial(Venda filial[ID][MONTH], char* prodCode, float price, int quantity, char discount, char* clientCode, int month, int idStore){
	
	Venda prox = malloc(sizeof(struct venda));
	prox->data = malloc(sizeof(struct productDetails));
	strcpy(prox->data->product, prodCode);
	prox->data->price = price;
	prox->data->quantity = quantity;
	prox->data->discount = discount;
	strcpy(prox->clientcode, clientCode);
	prox->right = NULL;
	prox->data->next = NULL;
	prox->left = filial[idStore-1][month-1];
	filial[idStore-1][month-1] = prox;
}

/*
	Esta função organiza a Btree de Venda
	Como os elementos são guardados todos a esquerda, podemos tratar esta estrutura como uma lligada e usar um mergSort para a organizar
*/
Venda mergSortVenda(Venda venda, int* size) {
	int i;
	Venda llist = venda;
	Venda result = NULL, iterador = venda;
	iterador = venda;
	for(i = 0; i < (*size)/2; i++){
		iterador = llist;
		llist = iterador->left;
	}

	iterador->left = NULL;
	if(venda->left != NULL){
		venda = mergSortVenda(venda, &i);
	}
	*size = ((*size)+1)/2;		
	if(llist->left != NULL){
		llist = mergSortVenda(llist, size);
	}
	*size += i;
	if(strcmp(llist->clientcode,venda->clientcode)>0){
		result = llist;
		llist = llist->left;
		result->left = NULL;
	}else{
		result = venda; 
		venda = venda->left;
		result->left = NULL;
	}
	iterador = result;
	Data data = NULL;
	Venda freeVenda = NULL;
	while(llist != NULL && venda != NULL) {
		if(strcmp(llist->clientcode,venda->clientcode)>0){
			if(strcmp(llist->clientcode,iterador->clientcode)){
				iterador->left = llist;
				llist = llist->left;
				iterador = iterador->left;
				}else{
				data = iterador->data;
				iterador->data = llist->data;
				iterador->data->next = data;
				llist->data = NULL;
				freeVenda = llist;
				llist = llist->left;
				free(freeVenda);
				freeVenda = NULL;
				*size = *size-1;
			}
		}else{
			if(strcmp(venda->clientcode,iterador->clientcode)){
				iterador->left = venda;
				venda = venda->left;
				iterador = iterador->left;
			}else{
				data = iterador->data;
				iterador->data = venda->data;
				iterador->data->next = data;
				venda->data = NULL;
				freeVenda = venda;
				venda = venda->left;
				free(freeVenda);
				freeVenda = NULL;
				*size = *size-1;
			}
		}

	}
	if(venda != NULL){
		iterador->left = venda;
	} 
	if(llist != NULL){
		iterador->left = llist;
	}
	return result;
}

/*
	Esta função tranforma uma lligada ordenada de Vendas numa arvore espelhada +-1;
*/
Venda vendaToBTree(Venda bTree, int size){
	int i;
	Venda next = bTree, prev = bTree;
	for (i = 0; i<size/2; i++) {
		prev = next;
		next = next->left;
	}
	next->right = bTree;
	prev->left = NULL;
	if( (size-1)/2 > 1 )
		next->left = vendaToBTree(next->left,(size-1)/2);
	if( size/2 > 1 )
		next->right = vendaToBTree(next->right,size/2);
	return next;
}
/*
	Esta função formata a arvore binaria usando as duas funçoes anteriores;
*/
void filialToBTree(Venda filial[ID][MONTH], int size[ID][MONTH]){
	int i, j, thisSize;
	for(i = 0; i< ID;i++){
		for(j = 0; j<MONTH ; j++){
			if(size[i][j]){
				if(filial[i][j] != NULL) {
					thisSize = size[i][j];
					if(filial[i][j]->left != NULL)
						filial[i][j] = mergSortVenda(filial[i][j],&thisSize);
					filial[i][j] = vendaToBTree(filial[i][j],thisSize);
				}
			}
		}
	}
}

/*
	Função que libeberta a memoria usada pela função addSaleToFilial
*/
void freeVenda(Venda bTree){
	if(bTree->left != NULL){
		freeVenda(bTree->left);
	}
	if(bTree->right != NULL){
		freeVenda(bTree->right);
	}
	Data data = NULL;
	while(bTree->data->next != NULL){
		data = bTree->data;
		bTree->data = bTree->data->next;
		free(data);
		data = NULL;
	}
	free(bTree->data);
	free(bTree);
}

/*
	Função que libeberta a memoria ao destruir a estrutura sgv
*/
void freeFilial(Venda filial[ID][MONTH]){
	int i,j;
	for(i = 0; i<ID ; i++){
		for(j = 0; j< MONTH;j++){
			if (filial[i][j] != NULL){
				freeVenda(filial[i][j]);
				filial[i][j]=NULL;
			}
		}
	}
}

/*
	Função de procura na Venda
*/
Venda findClientSales (Venda bTree, char* clientCode){
	Venda result = NULL;
	if(bTree != NULL){
		if(!strcmp(bTree->clientcode,clientCode)){
			result = bTree;
		}else{
			if(strcmp(bTree->clientcode,clientCode) < 0){
				result = findClientSales(bTree->right, clientCode);
			}else{
				result = findClientSales(bTree->left, clientCode);
			}
		}
	}
	return result;
}

/*
	Q6 auxiliar
*/
int Q6aux(Venda venda,int size){
	if(venda!= NULL){
		size--;
		Q6aux(venda->left, size);
		Q6aux(venda->right, size);
	}
	return size;
}

typedef struct lligada {
	char* codeproduct;
	float total;
	struct lligada* next;
} *LLaux;

/*
	Query7
*/

int Q7aux(Venda bTree, char* clientCode){
	int quantity = 0;
	bTree = findClientSales(bTree, clientCode);
	if(bTree != NULL){
		Data data = bTree->data;
		while(data != NULL){
			quantity += data->quantity;
			data = data->next; 
		}
	}
	return quantity;
}

void Q7(Venda filial[ID][MONTH], char* clientCode, int quantity[ID][MONTH]){
	int i, j;
	for(i = 0; i< ID;i++){
		for(j = 0; j<MONTH ; j++){
			quantity[i][j] = Q7aux(filial[i][j], clientCode);
		}
	}
}

/*
	Query 12
*/

LLaux orderAux(LLaux order, int size){
	LLaux prev = order;
	LLaux iterador = order;
	LLaux aux = order;
	LLaux result = NULL;
	LLaux freeVenda = NULL;
	int i;
	for(i = 0; i < size/2; i++){
		prev = iterador;
		iterador = iterador->next;
	}
	prev->next = NULL;
	aux = iterador;
	if(order->next != NULL)
		order = orderAux(order, size/2);
	if(aux->next != NULL)
		aux = orderAux(aux, (size+1)/2);

	if(strcmp(aux->codeproduct,order->codeproduct)>0){
		result = aux;
		aux = aux->next;
		result->next = NULL;
	}else{
		result = order; 
		order = order->next;
		result->next = NULL;
	}

	iterador = result;
	while(aux != NULL && order != NULL) {
		if(strcmp(aux->codeproduct,order->codeproduct)>0){
			if(strcmp(aux->codeproduct,iterador->codeproduct)){
				iterador->next = aux;
				aux = aux->next;
				iterador = iterador->next;
				}else{
				iterador->total += aux->total;
				freeVenda = aux;
				aux = aux->next;
				free(freeVenda);
				freeVenda = NULL;
			}
		}else{
			if(strcmp(order->codeproduct,iterador->codeproduct)){
				iterador->next = order;
				order = order->next;
				iterador = iterador->next;
			}else{
				iterador->total += order->total;
				freeVenda = order;
				order = order->next;
				free(freeVenda);
				freeVenda = NULL;
			}
		}

	}
	if(order != NULL){
		iterador->next = order;
	} 
	if(aux != NULL){
		iterador->next = aux;
	}
	return result;
}

LLaux addElement(Data data, LLaux result){
	LLaux new = calloc(1,sizeof(struct lligada));
	new->total = (data->price)*(data->quantity);
	new->codeproduct = data->product;
	new->next = result;
	result = new;
	return new;
}

LLaux addElementQ10(Data data, LLaux result){
	LLaux new = calloc(1,sizeof(struct lligada));
	new->total = (data->quantity);
	new->codeproduct = data->product;
	new->next = result;
	result = new;
	return new;
}

void freeAux(LLaux this){
	LLaux iterador = this;
	while(this != NULL){
		this = this->next;
		free(iterador);
		iterador = this;
	}
}

/*
	Query 10
	é prefiso dar-lhe os meses dele na funçao que o chamar
	e tratar de como retornar
*/

void Q10(Venda filial[ID][MONTH], char* clientcode){
	Venda month = NULL;
	int i, j, size;
	LLaux maisQuantity = NULL;
	Data data = NULL;
	for(i = 0; i<ID; i++){
		for(j=0;j<MONTH;j++){
			month = findClientSales(filial[i][j], clientcode);
			if(month != NULL){
				data = month->data;
				while(data != NULL){
					maisQuantity = addElement(data, maisQuantity);
					size++;
				}
			}
		}
	}
	if(maisQuantity != NULL){
		maisQuantity = orderAux(maisQuantity, size);
		freeAux(maisQuantity);
	}
}

/*
	Falta passar o resultado desta e verificar se esta tudo bem
*/
void queryDoze(Venda filial[ID][MONTH], char* clientCode, int N, char* (*result)[N]){
	int i, j, size = 0;
	Venda this = NULL;
	LLaux maisComprados = NULL;
	Data data = NULL;
	for(i = 0; i<ID; i++){
		for(j=0;j<MONTH;j++){
			this = findClientSales(filial[i][j], clientCode);
			if(this != NULL){
				data = this->data;
				while(data != NULL){
					maisComprados = addElement(data, maisComprados);
					size++;
				}
			}
		}
	}
	if(maisComprados != NULL){
		maisComprados = orderAux(maisComprados, size);
		freeAux(maisComprados);
	}
}

/**/
	
/*

void printVenda(Venda venda){
	printf("%s ",venda->codeproduct);
	printf("%f ",venda->price);
	printf("%d ",venda->soldUtd);
	printf("%c ",venda->discount);
	printf("%s\n",venda->clientcode);
}

static void printB (Venda bTree){
	if(bTree == NULL)
		return;
	printB(bTree->left);
	printf("%s\n", bTree->clientcode);
	printB(bTree->right);
}
*/
