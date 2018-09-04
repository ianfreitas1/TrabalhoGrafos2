#ifndef GRAFO_H_
#define GRAFO_H_
#include <iostream>
#include <string>
#include <vector>
#include <queue>


using namespace std;

struct ListInfo{
    int vertice;
    ListInfo *pNext, *pPrev;
};

class Grafo{
    public:
      Grafo();
      virtual ~Grafo();
      int m_numArestas;
      int m_numVertices;
      //vector<int> BFS(int raiz);
    protected:
      string m_savePath = "output"; // editar
    //  virtual ListInfo** getLista();
    //  virtual vector<int> vizinhos(int v);
};

#endif
