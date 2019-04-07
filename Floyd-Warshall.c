#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getVertices()
{
  int v;
  printf("Por favor, insira quantos vertices o seu grafo terá:\n");
  scanf("%d", &v);
  return v;
}

int getLigações(int i)
{
  int l;
  printf("Quantas ligações o vértice ");
  printf("%d", i);
  printf(" terá:\n");
  scanf("%d", &l);
  return l;
}

void printarGrafo(int size, int grafo[size][size])
{
  int i, j;
  printf("   ");
  for(i=0; i<size; i++) printf("%d ", i);
  printf("\n\n");

  for(i=0; i<size; i++)
    {
      printf("%d  ", i);
      for(j=0; j<size; j++) 
      {
        if(grafo[i][j] == 1000000000) printf("∞ ");
        else printf("%d ", grafo[i][j]);
      }
      printf("\n");
    }
}

int min(int x, int y)
{
  if(x<=y)return x;
  else return y;
}

void FloydWarshall(int size, int grafo[size][size])
{
  int i, j, k;

  for(k=0; k<size; k++)
  {
    for(i=0; i<size; i++)
    {
      for(j=0; j<size; j++)
      {
        grafo[i][j] = min(grafo[i][j], grafo[i][k]+grafo[k][j]);
      }
    }
  }

  printarGrafo(size, grafo);
}

int main(void) 
{
  int v = getVertices(), ligações, ligação, peso, i, j;
  int grafo[v][v];

  for(i=0; i<v; i++)
  {
    for(j=0; j<v; j++)
    {
      if(i!=j) grafo[i][j] = 1000000000;
      else grafo[i][j] = 0;
    }
  }

  for(i=0; i<v; i++)
  {
    ligações = getLigações(i);
    
    for(j=0; j<ligações; j++)
    {
      printf("Insira um vértice que este tenha ligação: (de 0 até %d)\n", v-1);
      scanf("%d", &ligação);
      printf("Qual o peso desta ligação?\n");
      scanf("%d", &peso);
      grafo[i][ligação] = peso;
    }
  }

  printf("Matriz de adjacência do seu Grafo:\n");
  printarGrafo(v, grafo);
  printf("\n");

  printf("Matriz de adjacência após a aplicalção do Algoritmo de Floyd-Warshall:\n");
  FloydWarshall(v, grafo);



  return 0;
}
