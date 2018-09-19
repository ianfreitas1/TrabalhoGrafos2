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
  int opcao;
  cout << "1: Grau" << endl;
  cout << "2: BFS" << endl;
  cout << "3: DFS" << endl;
  cout << "4: CC" << endl;
  cout << "5: Vizinhos" << endl;
  cin >> opcao;
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
      int k;
      cout << "Escolha vertice para mostrar vizinhos: ";
      cin >> k;
      lista.vizinhos(k);
      break;
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
