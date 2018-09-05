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
  Matriz matriz = Matriz(arquivo);
  matriz.BFS(1);
  //int vizin;
  //cin >> vizin;
  //matriz.vizinhos(1);
  //Lista lista = Lista(arquivo);
  //lista.Grau2();
  //lista.CC();
  //lista.vizinhos(0);
  //lista.DFS(1);
  //lista.vizinhos(2);
  //vector<int> x = lista.BFS(3);
  system("pause");
  return 0;
}
