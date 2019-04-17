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

void krusk(struct LISTA *lista, int n)
{
	int aux[n+1];
	int menor, i;
	int flag = 0;
	int soma = 0;
	int k = 1;
	for(i = 0; i<n+1; i++)
		aux[i] = i;
	while(lista != NULL)
	{
		menor = lista->v1 < lista->v2 ? lista->v1 : lista->v2;
		//printf("menor: %d; lista->v1: %d; lista->v2: %d\n", menor, lista->v1, lista->v2);
		for(i = 1; i<n+1; i++)
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
		for(i = 1; i<n+1; i++)
			soma += aux[i];
		if(soma == n)
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

int confere_parametros(int a, int b, int peso, int n)
{
	if(a >= 0 && a <= n)
	{
		if(b >= 0 && b <= n)
		{
			if(peso > 0)
				return 1;
		}
	}
	return 0;
}

int main()
{
	struct LISTA *lista;
	struct LISTA *inicio;
	int vertices, arestas, a, b, peso;
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
	printf("Informe o numero de vertices do grafo: ");
	scanf("%d", &vertices);
	printf("Informe o numero de arestas do grafo: ");
	scanf("%d", &arestas);
	printf("\nInforme o valor das arestas entre os vertices, no seguinte formato:");
	printf("\nVertice_de_saida Vertice_de_entrada Valor_da_aresta\n");
	printf("Se o grafo não for direcionado coloque apenas uma aresta, com o par a sua escolha\n");
	printf("O Valor_da_aresta não pode ser menor que 1\n");
	printf("Os indices dos vertices não podem ser maiores que %d nem menores que 0\n", vertices);
	scanf("%d%d%d", &a, &b, &peso);
	if(confere_parametros(a, b, peso, vertices))
	{
		lista->v1 = a;
		lista->v2 = b;
		lista->val = peso;
	}
	else
	{
		printf("Entrada invalida\n");
		exit(-1);
	}
	scanf("%d%d%d", &a, &b, &peso);
	while(arestas - 2 > 0)
	{
	 	inserir(lista, a, b, peso);
	 	scanf("%d%d%d", &a, &b, &peso);
	 	if(!confere_parametros(a, b, peso, vertices))
		{
			printf("Fim da entrada\n");
			exit(-1);
		}
		arestas--;
	}
	while(lista->prev != NULL)
		lista = lista->prev;
	inicio = lista;
	krusk(lista, vertices);
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