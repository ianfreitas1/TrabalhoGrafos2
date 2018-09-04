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
        vector<int> vizinhos(int v);
        vector<int> BFS(int raiz);
        vector<bool> DFS(int raiz);


      //  ListInfo** getLista();

    protected:
        ListInfo** m_pLista;
        void addAresta(int v0,int vf);
        //std::string m_path;


};
#endif
