#include <iostream>
#include <vector>
using namespace std;
struct parada{
	int ruta;
	int nodo;
};
vector<parada> path_actual;

bool nodo_in_path(int &nodo){
  if(path_actual.empty()){
    return false;
  }
	for (int i = 0; i < path_actual.size(); i++){
		if (path_actual[i].nodo == nodo){
			return true;
		}
	}
	return false;
}

int main() {
  parada camino;
  camino.ruta = 1;
  camino.nodo = 1;
  //path_actual.push_back(camino);
  if (nodo_in_path(camino.nodo)){
    cout << "En el path" << '\n';
  }
  else{
    cout << "No esta en el path" << '\n';
  }
  return 0;
}
