#include <stdio.h>
#include <stdlib.h>
#define tam 6

void imprimir(int dist[], int ant[], int aux[])
{
	int i;
	char cid_ant;
	for(i = 0; i < tam; i++)
	{
		if(aux[i] == 1)
		{
			switch (i)
			{
				case 0:
				printf("\t\t\tA*");
				break;
				case 1:
				printf("\tB*");
				break;
				case 2:
				printf("\tC*");
				break;
				case 3:
				printf("\tD*");
				break;
				case 4:
				printf("\tE*");
				break;
				default:
				printf("\tF*\n");
			}
		}
		else
		{
			switch (i)
			{
				case 0:
				printf("\t\t\tA");
				break;
				case 1:
				printf("\tB");
				break;
				case 2:
				printf("\tC");
				break;
				case 3:
				printf("\tD");
				break;
				case 4:
				printf("\tE");
				break;
				default:
				printf("\tF\n");
			}
		}
	}
	printf("Distancia:");
	for(i = 0; i < tam; i++)
		printf("\t%d", dist[i]);
	printf("\n");
	printf("Anterior:");
	for(i = 0; i < tam; i++)
	{
		switch (ant[i])
		{
			case 65:
			cid_ant = 'A';
			break;
			case 66:
			cid_ant = 'B';
			break;
			case 67:
			cid_ant = 'C';
			break;
			case 68:
			cid_ant = 'D';
			break;
			case 69:
			cid_ant = 'E';
			break;
			case 70:
			cid_ant = 'F';
			break;
			default: 
			cid_ant = '-';
		}
		printf("\t%c", cid_ant);
	}
	printf("\n");
}

int posicao_menor(int dist[], int aux[])
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

void anterior(int cidade, int ant[], int posicao)
{
	switch (cidade)
	{
		case 0:
		ant[posicao] = 65;
		break;
		case 1:
		ant[posicao] = 66;
		break;
		case 2:
		ant[posicao] = 67;
		break;
		case 3:
		ant[posicao] = 68;
		break;
		case 4:
		ant[posicao] = 69;
		break;
		default:
		ant[posicao] = 70;
	}
}

void Dijk(int grafo[tam][tam], int origem, int destino)
{
	int aux[tam]={0};
	int dist[tam];
	int ant[tam];///65-70 A-F
	int i, k, val1;
	for(i = 0; i < tam; i++)
		dist[i] = 1000000;
	dist[origem] = 0;
	aux[origem] = 1;
	imprimir(dist, ant, aux);
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
					anterior(origem, ant, i);
				}
			}
		}
		k = posicao_menor(dist, aux);
		aux[k] = 1;
		origem = k;
		imprimir(dist, ant, aux);
	}
}

int main()
{
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
	grafo[0][1] = 12;
	grafo[0][2] = 4;
	grafo[1][2] = 6;
	grafo[2][1] = 10;
	grafo[1][3] = 6;
	grafo[3][5] = 6;
	grafo[2][3] = 2;
	grafo[3][2] = 8;
	grafo[2][4] = 2;
	grafo[4][1] = 2;
	grafo[4][5] = 6;
	origem = 0;
	destino = 5;
	Dijk(grafo, origem, destino);
	return 0;
}