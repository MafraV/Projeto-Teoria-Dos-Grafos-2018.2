#include <stdio.h>
#include <stdlib.h>

int tam;

void imprimir(int dist[], int ant[], int aux[], int tam)
{
	int i, k;
	k = 0;
	for(i = 0; i < tam; i++)
	{
		if(aux[i] == 1)
		{
			if(i == 0)
				printf("\t\t\t%d*", i);
			else if(i == tam-1)
				printf("\t%d*\n", i);
			else
				printf("\t%d*", i);
		}
		else
		{
			if(i == 0)
				printf("\t\t\t%d", i);
			else if(i == tam-1)
				printf("\t%d\n", i);
			else
				printf("\t%d", i);
		}
	}
	printf("Distancia:");
	for(i = 0; i < tam; i++)
		printf("\t%d", dist[i]);
	printf("\n");
	printf("Anterior:");
	for(i = 0; i < tam; i++)
	{
		for(int j = 0; j < tam; j++)
		{
			if(ant[i] == j)
			{
				k = 1;
				break;
			}
		}
		if(k)
			printf("\t%d", ant[i]);
		else
			printf("\t-");
		k = 0;
	}
	printf("\n");
}

int posicao_menor(int dist[], int aux[], int tam)
{
	int menor, i, k;
	i=0;
	while(i < tam)
	{
		if(aux[i] != 1)
		{
			menor = dist[i];
			break;
		}
		i++;
	}
	for(i = 0; i < tam; i++)
	{
		if (aux[i] != 1 && dist[i] <= menor)
		{
			menor = dist[i];
			k = i;
		}
	}
	return k;
}

void anterior(int cidade, int ant[], int posicao, int tam)
{
	for(int i = 0; i < tam; i++)
	{
		if(cidade == i)
		{
			ant[posicao] = i;
			break;
		}
	}
}

void Dijk(int grafo[tam][tam], int origem, int destino, int tam)
{
	int aux[tam];
	int dist[tam];
	int ant[tam];///65-70 A-F
	int i, k, val1;
	for(i = 0; i < tam; i++)
	{
		dist[i] = 1000000;
		aux[i] = 0;
	}
	dist[origem] = 0;
	aux[origem] = 1;
	imprimir(dist, ant, aux, tam);
	while(origem != destino)
	{
		for(i = 0; i < tam; i++)
		{
			val1 = dist[origem] + grafo[origem][i];
			if(val1 < dist[i])
			{
				if(aux[i] != 1)
				{
					dist[i] = val1;
					anterior(origem, ant, i, tam);
				}
			}
		}
		k = posicao_menor(dist, aux, tam);
		aux[k] = 1;
		origem = k;
		imprimir(dist, ant, aux, tam);
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
	int arestas;
	printf("Informe o numero de vertices do grafo: ");
	scanf("%d", &tam);
	printf("Informe o numero de arestas do grafo: ");
	scanf("%d", &arestas);
	int grafo[tam][tam];
	int origem, destino;
	for(int i = 0; i < tam; i++)
	{
		for(int j = 0; j < tam; j++)
		{
			if(i == j)
				grafo[i][j] = 0;
			else
				grafo[i][j] = 1000000;
		}
	}
	///a parte do usuario colocar o grafo n esta pronta pois teria q modificar na função de imprimir e de marcar
	///o vertice anterior
	printf("\nInforme o valor das arestas entre os vertices, no seguinte formato:");
	printf("\nVertice_de_saida Vertice_de_entrada Valor_da_aresta\n");
	printf("O Valor_da_aresta não pode ser menor que 1\n");
	printf("Os indices dos vertices não podem ser maiores que %d nem menores que 0\n", tam);
	int v1, v2, v;
	scanf("%d%d%d", &v1, &v2, &v);
	if(!confere_parametros(v1, v2, v, tam))
	{
		printf("Entrada invalida\n");
		exit(-1);
	}
	while(arestas - 1 > 0)
	{
		grafo[v1][v2] = v;
		scanf("%d%d%d", &v1, &v2, &v);
		if(!confere_parametros(v1, v2, v, tam))
		{
			printf("Fim da entrada\n");
			exit(-1);
		}
		arestas--;
	}
	printf("\nInforme o vertice de origem e o de destino");
	printf("\nOs indices dos vertices não podem ser maiores que %d nem menores que 0\n", tam);
	scanf("%d%d", &origem, &destino);
	if(confere_parametros(origem, destino, 1, tam))
		Dijk(grafo, origem, destino, tam);
	else
	{
		printf("Erro!\n");
		printf("A origem ou o destino estão fora do intervalo\n");
		exit(-1);
	}
	return 0;
}