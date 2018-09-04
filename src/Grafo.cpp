#include "Grafo.h"
#include <vector>
#include <queue>

using namespace std;

Grafo::Grafo()
{

}

Grafo::~Grafo()
{

}

// vector<int> Grafo::vizinhos(int v){
//   vector<int> vizinhos;
//   ListInfo* pCrawl = new ListInfo;
//   pCrawl = m_pLista[v];
//   while(pCrawl != NULL){
//     vizinhos.push_back(pCrawl->vertice);
//     pCrawl = pCrawl->pNext;
//   }
//   return vizinhos;
// }

//vector<int> Grafo::BFS(int raiz) {

// vector<int> Grafo::BFS(int raiz) {
//
// //	clock_t begin = clock();
//
// 	int s = raiz-1;
// 	// Initialize vectors and queue
// 	vector<bool> visitado(m_numVertices,0);
// 	vector<int> pai(m_numVertices,-1);
// 	vector<int> nivel(m_numVertices,-1);
// 	vector<int> explorado;
// 	queue<int> fila;
//
// 	//Mark src as visitado and add it to the queue
// 	visitado[s] = 1;
// 	nivel[s] = 0;
// 	fila.push(s);
//
// 	cout << endl<< "BFS(" << raiz << ") Running..." << endl;
//
// 	while(!fila.empty()){
// 		int v = fila.front();
// 		fila.pop();
//     vector<int> w = vizinhos(v);
//     for(int i = 0;i< w.size();i++){
//       if(visitado[w[i]] == 0) {
//         visitado[w[i]] == 1;
//         pai[w[i]] == v;
//         fila.push(w[i]);
//       }
//     }
//     explorado.push_back(v);
//   }
//
//
//
//
// 	return explorado;
// }
