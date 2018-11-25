#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "Lista.h"
#include <vector>
#include <stdlib.h>
#include <ctime>


using namespace std;

int main(){

  string arquivo;
  cout << "nome do arquivo: " << endl;
  cin >> arquivo;
  cout << "Carregando..." << endl;
  //Matriz matriz = Matriz(arquivo);
  //matriz.BFS(1);
  //int vizin;
  //cin >> vizin;
  //matriz.vizinhos(1);
  Lista lista = Lista(arquivo);
  int opcao = 1;
  while (opcao < 14 && opcao > 0){
    cout << "1: Grau" << endl;
    cout << "2: BFS" << endl;
    cout << "3: DFS" << endl;
    cout << "4: Componentes Conexas" << endl;
    cout << "5: Vizinhos" << endl;
    cout << "6: Distancias e caminhos a partir de um vertice" << endl;
    cout << "7: Distancias e caminhos entre dois vertices" << endl;
    cout << "8: PrimMST" << endl;
    cout << "9: Excentricidade de um vertice" << endl;
    cout << "10: Distancia media" << endl;
    cout << "11: Tempo medio Excentricidade (Estudo de caso)" << endl;
    cout << "12: 2-Approximation" << endl;
    cout << "13: DFS Caminho" << endl;
    cout << "13: Sair" << endl;
    cin >> opcao;
    system("CLS");
    switch(opcao){
      case 1:
        lista.Grau2();
        break;
      case 2:
        int i;
        cout << "Escolha vertice da BFS: ";
        cin >> i;
        lista.BFS(i);
        break;
      case 3:
        int j;
        cout << "Escolha vertice da DFS: ";
        cin >> j;
        lista.DFS(j);
        break;
      case 4:
        lista.CC();
        break;
      case 5:
      {
        int k;
        cout << "Escolha vertice para mostrar vizinhos: ";
        cin >> k;
        vector<tuple<int, float> > viz = lista.vizinhos(k);
        for (unsigned int p = 0; p < viz.size(); p++){
          cout << get<0>(viz[p]) << endl;
        }
        break;
      }
      case 6:
        int s;
        cout << "Escolha vertice raiz: ";
        cin >> s;
        //Se o grafo não tiver nenhuma aresta negativa e as arestas tiverem pesos
        //roda Dijkstra para achar a distância e um caminho mínimo de um vértice
        //a todos os outros do grafo
        if (!lista.grafoNegativo && lista.grafoComPeso){
          cout << "Rodando Dijkstra a partir de " << s << endl;
          lista.distDijkstra(s);
        //Caso as arestas do grafo não tenham pesos, roda BFS
        }else if (!lista.grafoComPeso){
          lista.BFS(s);
        //Caso contrário, o grafo tem pesos negativos e não é possível calcular
        //a distância e caminhos mínimos
        }else{
          cout << "O grafo tem pesos negativos. Nao e possivel rodar Dijkstra" << endl;
        }
        break;
      case 7:
        int a, b;
        cout << "Escolha vertice 1:" << endl;
        cin >> a;
        cout << "Escolha vertice 2:" << endl;
        cin >> b;
        //Se o grafo não tiver nenhuma aresta negativa e as arestas tiverem pesos
        //roda Dijkstra para achar a distância e um caminho mínimo de um vértice
        //a outro passados como parâmetro
        if (!lista.grafoNegativo && lista.grafoComPeso){
          cout << "Rodando Dijkstra" << endl;
          lista.caminhoMinimo(a, b);
        //Caso as arestas do grafo tenham peso, roda BFS para achar distância e
        //caminho mínimo de um vértice a outro
        }else if (!lista.grafoComPeso){
          //Variável que recebe o retorno da função BFS
          BFSs* bfs = lista.BFS(a);
          ofstream myOut2;
          myOut2.open("output/BFS - Distancia e Caminho.txt");
          myOut2 << "Distancia entre " << a << " e " << b << ": " << bfs->nivel[b-1] << endl;
          myOut2 << "Caminho entre " << a << " e " << b << endl;
          vector<int> caminho = lista.retornaCaminho(bfs->pai, a-1, b-1);
          //Escrita do caminho no arquivo de saída
          for (unsigned int j = 0; j < caminho.size(); j++){
              myOut2  << caminho[j] + 1 << " " ;
            }
        //Caso contrário, o grafo tem pesos negativos
        }else{
          cout << "O grafo tem pesos negativos. Nao e possivel rodar Dijkstra" << endl;
        }
        break;
      case 8:
        lista.PrimMST();
        break;
      case 9:
        int v;
        cout << "Escolha um vertice: ";
        cin >> v;
        lista.excentricidade(v);
        break;
      case 10:
        lista.distMedia();
        break;
      case 11:
        {double tempototal = 0;
        int count = 0;
        for (int i = 0; i < 100; i++){
          int a = rand() % lista.m_numVertices + 1;
          clock_t inicio = clock();
          lista.excentricidade(a);
          clock_t fim = clock();
          double tempo = double(fim-inicio)/CLOCKS_PER_SEC;
          tempototal += tempo;
          count++;
        }
        cout << count << endl;
        cout << tempototal << endl;
        cout << tempototal/count << endl;}
        break;
      case 12:
        lista.Approx2();
        break;
      case 13:
        lista.DFScaminho(1);
        break;
    }
  }

  //lista.Grau2();
  //lista.CC();
  //lista.vizinhos(0);
  //lista.DFS(1);
  //lista.vizinhos(2);
  //vector<int> x = lista.BFS(3);
  system("pause");
  return 0;
}
