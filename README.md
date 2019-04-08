- **Dupla**:
  - **Victor Mafra**
  - **Matheus Ramos**


- **Especificações dos Algoritmos**:
  - *Floyd-Warshall*: O algoritmo de Floyd-Warshall pede que o usuário entre todo o grafo de maneira detalhada, após a passagem do grafo, ele printa a matriz de adjacência criada,
   logo após, aplica em si o algoritmo, onde a entrada do algoritmo é a propria matriz, de maneira que:
    - caso i=j: adj[i][j] = 0;
    - caso i!=j e a aresta a[i][j] pertença ao grupo de arestas: adj[i][j] = peso de a[i][j];
    - caso i!=j e a aresta a[i][j] não pertença ao grupo de arestas: adj[i][j] = infinito positivo.
    
     Retornando assim, a menor distância entre cada par de vértices, sendo: o valor de adj[i][j] representa a menor distância do vértice j ao vértice i.
     O algoritmo aceita pesos negativos para as arestas, porém não devem existir ciclos negativos.
          
  - *Bellman-Ford*: o algoritmo de Bellman-Ford usa structs tanto para vértices, quanto para as arestas, contendo informações necessárias para a aplicação do algoritmo,
  da mesma maneira do anterior, ele pede pra entrar o grafo de maneira detalhada, sendo a entrada para o algoritmo em si o grupo de vértices, o grupo de arestas e o vértice que será a origem na execução do algoritmo,
   retornando uma array de vértices, onde v[i] representa a menor distância do vértice origem ao vértice i.
- *Kruskal* :  O arquivo Kruskal.c contem o exemplo do livro, ja o arquivo Kruskal_2.c aceita entrada do usuario, ambos os arquivos retornam uma tabela com as arestas que não formam ciclo na ordem que são colocadas para formar a arvore geradora minima, isto é, levando em conta qual tem menos  peso.
 -* Dijkstra * : O arquivo Dijkstra.c utiliza o exemplo do livro, mas no livro consta-se 2 erros, o 1º é que el não considera a aresta (C, D) com peso 2 e o 2º erro é que ele soma a distancia de D/E ate F como 10 mas não considera que a distancia de (A, D) e a distancia de (A, E) é 6 e a distancia do vertice D/E para F é 6 logo daria 12 e não 10.
