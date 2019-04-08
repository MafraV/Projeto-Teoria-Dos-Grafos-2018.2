#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertice_ vertice;
typedef struct aresta_ aresta;

struct vertice_
{
  int distancia;
  vertice* anterior;
};

struct aresta_
{
  int peso;
  vertice* origem;
  vertice* destino;
};

vertice* createVertice()
{
  vertice* v = malloc(sizeof(vertice));
  v->anterior = NULL;
  return v;
}

aresta* createAresta(int peso, vertice* origem, vertice* destino)
{
  aresta* a = malloc(sizeof(aresta));
  a->peso = peso;
  a->origem = origem;
  a->destino = destino;
  return a;
}

vertice** BellmanFord(vertice** vertices, aresta** arestas, struct vertice_* origem, int vSize, int aSize)
{
  int i, j;
  for(i=0; i<vSize; i++)
  {
    if(vertices[i] == origem) vertices[i]->distancia = 0;
    else
    {
      vertices[i]->distancia = 1000000000;
      vertices[i]->anterior = NULL;
    }
  }

  for(i=0; i<vSize; i++)
  {
    for(j=0; j<aSize; j++)
    {
      aresta* uv = arestas[j];
      vertice* u = uv->origem;
      vertice* v = uv->destino;
      if(v->distancia > u->distancia + uv->peso)
      {
        v->distancia = u->distancia + uv->peso;
        v->anterior = u;
      }
    }
  }

  return vertices;
}

int main(void)
{
  printf("Quantos vértices seu grafo terá?\n");
  int v;
  scanf("%d", &v);
  vertice* vertices[v];

  printf("Quantas arestas seu grafo terá?\n");
  int a;
  scanf("%d", &a);
  aresta* arestas[a];

  int i, j, ligações, ligação, peso, atualAresta = 0;

  for(i=0; i<v; i++)
  {
    vertices[i] = createVertice();
  }

  for(i=0; i<v; i++)
  {
    printf("Quantas ligações o grafo %d possui?\n", i);
    scanf("%d", &ligações);
    for(j=0; j<ligações; j++)
    {
      printf("Entre um dos vértices que este tem ligação: (de 0 até %d)\n", v-1);
      scanf("%d", &ligação);
      printf("Qual o peso desta ligação?\n");
      scanf("%d", &peso);

      aresta* a = createAresta(peso, vertices[i], vertices[ligação]);
      arestas[atualAresta++] = a; 
    }
  }

  printf("Qual vértice será a origem na execução do Algoritmo de Bellman-Ford? (de 0 até %d)\n", v-1);
  int origin;
  scanf("%d", &origin);

  vertice** verticesAlterados = BellmanFord(vertices, arestas, vertices[origin], v, a);

  printf("\nA partir do vértice %d:\n", origin);
  for(i=0; i<v; i++) 
  {
    printf("O caminho mínimo para o vértice %d é: %d\n", i, verticesAlterados[i]->distancia);
  }

  return 0;
}