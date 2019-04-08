#include <stdio.h>
#include <stdlib.h>

struct LISTA
{
	int v1, v2, val;
	struct LISTA *next;
	struct LISTA *prev;
};

void imprimir(int a, int b, int flag, int valor, int k)
{
	if(flag)
	{
		printf("(%d, %d)\tInclui a %dª aresta\t%d\n", a, b, k, valor);
	}
	else
	{
		printf("(%d, %d)\tForma ciclo\t\t-\n", a, b);
	}
}

void krusk(struct LISTA *lista)
{
	int aux[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int menor, i;
	int flag = 0;
	int soma = 0;
	int k = 1;
	while(lista != NULL)
	{
		menor = lista->v1 < lista->v2 ? lista->v1 : lista->v2;
		//printf("menor: %d; lista->v1: %d; lista->v2: %d\n", menor, lista->v1, lista->v2);
		for(i = 1; i<10; i++)
		{
			if(aux[i] == lista->v1 || aux[i] == lista->v2)
			{
				if(aux[i] != menor)
				{
					aux[i] = aux[menor];
					flag = 1;
				}
			}
			//printf("%d ", aux[i]);
		}
		//printf("\n");
		if(flag)
			imprimir(lista->v1, lista->v2, flag, lista->val, k++);
		else
			imprimir(lista->v1, lista->v2, flag, lista->val, k);
		flag = 0;
		for(i = 1; i<10; i++)
			soma += aux[i];
		if(soma == 9)
			break;
		else 
			soma = 0;
		lista = lista->next;
	}
}

void ordena(struct LISTA *lista, struct LISTA *aux)//ordenação de 3 niveis, crescente
{
	///nvl 1
	if(lista->val < aux->val)
	{
		if(lista->next==NULL)
		{
			lista->next = aux;
			aux->prev = lista;
		}	
		else
		{
			if(lista->next->val  <= aux->val)
				ordena(lista->next, aux);
			
			else //if(lista->next->val  < aux->val)
			{
				aux->next = lista->next;
				lista->next->prev = aux;
				aux->prev = lista;
				lista->next = aux;
			}
		}
	}
	else if(lista->val > aux->val)
	{
		if(lista->prev==NULL)
		{
			lista->prev = aux;
			aux->next = lista;
		}
		else
		{
			if(lista->prev->val >= aux->val)
				ordena(lista->prev, aux);
			else
			{
				aux->next = lista;
				aux->prev = lista->prev;
				lista->prev->next = aux;
				lista->prev = aux;
			}
		}
	}
	///nvl 2
	else //if(lista->val == aux->val)
	{
		if(lista->v1 < aux->v1)
		{
			if(lista->next==NULL)
			{
				lista->next = aux;
				aux->prev = lista;
			}	
			else
			{
				if((lista->next->val == aux->val) && (lista->next->v1  <= aux->v1))
					ordena(lista->next, aux);
				else //if(lista->next->val  < aux->val)
				{
					aux->next = lista->next;
					lista->next->prev = aux;
					aux->prev = lista;
					lista->next = aux;
				}
			}
		}
		else if(lista->v1 > aux->v1)
		{
			if(lista->prev==NULL)
			{
				lista->prev = aux;
				aux->next = lista;
			}
			else
			{
				if((lista->next->val == aux->val) && (lista->next->v1  >= aux->v1))
					ordena(lista->prev, aux);
				else
				{
					aux->next = lista;
					aux->prev = lista->prev;
					lista->prev->next = aux;
					lista->prev = aux;
				}
			}
		}
		///nvl 3
		else //if(lista->v1 == aux->v1)
		{
			if(lista->v2 < aux->v2)
			{
				if(lista->next==NULL)
				{
					lista->next = aux;
					aux->prev = lista;
				}	
				else
				{
					if((lista->next->val == aux->val) && (lista->next->v1  == aux->v1))
					{
						if((lista->next->v2  < aux->v2))
							ordena(lista->next, aux);
					}
					else //if(lista->next->val  < aux->val)
					{
						aux->next = lista->next;
						lista->next->prev = aux;
						aux->prev = lista;
						lista->next = aux;
					}
				}
			}
			else if(lista->v2 > aux->v2)
			{
				if(lista->prev==NULL)
				{
					lista->prev = aux;
					aux->next = lista;
				}
				else
				{
					if((lista->next->val == aux->val) && (lista->next->v1  == aux->v1))
					{
						if((lista->next->v2  > aux->v2))
							ordena(lista->next, aux);
					}
					else
					{
						aux->next = lista;
						aux->prev = lista->prev;
						lista->prev->next = aux;
						lista->prev = aux;
					}
				}
			}
		}
	}
}

void inserir(struct LISTA *lista, int a, int b, int p)
{
	struct LISTA *aux;
	aux = calloc(1, sizeof(struct LISTA));
	if(aux==NULL)
	{
		printf("Erro de alocacao\n");
		exit(-1);
	}
	aux->v1 = a;
	aux->v2 = b;
	aux->val = p;
	aux->next = NULL;
	aux->prev = NULL;
	ordena(lista, aux);
}

void imprimir_lista(struct LISTA *lista)
{
	while(lista != NULL)
	{
		printf("A aresta (%d, %d) com peso %d\n", lista->v1, lista->v2, lista->val);
		lista = lista->next;
	}
}

int main()
{
	struct LISTA *lista;
	struct LISTA *inicio;
	///criando a lista
	lista = calloc(1, sizeof(struct LISTA));
	if(lista==NULL)
	{
		printf("Erro na alocação da memoria\n");
		exit(-1);
	}
	lista->next = NULL;
	lista->prev = NULL;
	///entrada no formato vertice 1, vertice 2, peso da aresta
	// a entrada 1, 2, 4 foi colocada de outra forma para poder melhor ordenar
	lista->v1 = 1;
	lista->v2 = 2;
	lista->val = 4;
	inserir(lista, 1, 6, 5);
	inserir(lista, 2, 6, 3);
	inserir(lista, 2, 3, 7);
	inserir(lista, 3, 4, 5);
	inserir(lista, 3, 7, 6);
	inserir(lista, 4, 5, 3);
	inserir(lista, 5, 7, 2);
	inserir(lista, 5, 8, 4);
	inserir(lista, 6, 7, 7);
	inserir(lista, 6, 9, 5);
	inserir(lista, 7, 8, 6);
	inserir(lista, 8, 9, 8);
	while(lista->prev != NULL)
		lista = lista->prev;
	inicio = lista;
	krusk(lista);
  	//imprimir_lista(lista);
  	lista=inicio;
	while(lista->next!=NULL)
	{
		struct LISTA *prox;
		prox = lista->next;
		free(lista);
		lista = NULL;
		lista = prox;
	}
	return 0;
}