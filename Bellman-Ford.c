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
  printf("Por favor, entre qual o número de vértices, arestas e o vértice origem:\n");
  int v, a, origin, i;
  scanf("%d%d%d", &v, &a, &origin);
  vertice* vertices[v];
  aresta* arestas[a];

  for(i=0; i<v; i++)
  {
    vertices[i] = createVertice();
  }

  printf("Por favor, insira as arestas de seu grafo:\n");

  int origem, destino, peso;
  for(i=0; i<a; i++)
  {
    scanf("%d%d%d", &origem, &destino, &peso);
    aresta* newAresta = createAresta(peso, vertices[origem], vertices[destino]);
    arestas[i] = newAresta;
  }

  vertice** verticesAlterados = BellmanFord(vertices, arestas, vertices[origin], v, a);

  printf("\nA partir do vértice %d:\n", origin);
  for(i=0; i<v; i++) 
  {
    printf("O caminho mínimo para o vértice %d é: %d\n", i, verticesAlterados[i]->distancia);
  }

  return 0;
}