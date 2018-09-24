#ifndef GRAFO_H_
#define GRAFO_H_
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>


using namespace std;

struct ListInfo{
    int vertice;
    float peso;
    ListInfo *pNext, *pPrev;
};

//Essa struct serve para a função BFS retornar os três vetores, pois serão
//utilizados em diferentes ocasiões na biblioteca
struct BFSs{
    vector<int> explorado;
    vector<int> pai;
    vector<int> nivel;
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
