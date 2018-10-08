#ifndef LISTA_H_
#define LISTA_H_

#include "Grafo.h"
#include <string>
#include <vector>

using namespace std;

class Lista : public Grafo{
    public:
        Lista(std::string path);
        ~Lista();
        void Grau();
        vector<tuple<int, float> > vizinhos(int v);
        BFSs* BFS(int raiz);
        vector<bool> DFS(int raiz);
        void CC();
        void Grau2();
        vector<float> distDijkstra(int raiz);
        float caminhoMinimo(int x, int y);
        vector<int> retornaCaminho(vector<int> pai, int raiz, int v);
        void PrimMST();
        float excentricidade(int v);
        float distMedia();
        bool grafoNegativo = 0;
        bool grafoComPeso = 0;
        float distMedia_Dijkstra(int raiz);
      //  ListInfo** getLista();

    protected:
        ListInfo** m_pLista;
        void addAresta(int v0,int vf, float peso);
        //std::string m_path;


};
#endif
