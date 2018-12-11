//Inlcusion de librerias
#include <iostream>		//cout, stof, stoi
#include <fstream>		//getline, ifstream,
#include <string>			//strings
#include <vector>			//vectors
#include <ctime>			//measure time
#include <cmath>			//sqrt

//Global
using namespace std;

//Definicion de struct que contendra la informacion de un nodo recorrido y la ruta que lo recorre.
struct parada{
	int ruta;
	int nodo;
};
//Variables globales con info del problema
int n_nodos, n_rutas;
float t_max;
vector<vector<float>> distancias;

//Variables globales que contienen la informacion de la mejor solucion encontrada
vector<parada> path_solucion;
int puntaje_solucion = 0;
//1d-Vector que guarda el puntaje de cada nodo
vector<int> puntajes;

//Variables globales que contienen la informacion de la solucion que se va instanciando paso a paso en la recursividad
vector<parada> path_actual;
int puntaje_actual = 0;

int numero_nodos(ifstream &entrada) {
	string line;
	getline(entrada, line, ' ');
	getline(entrada, line);
	return stoi(line);
}

int numero_rutas(ifstream &entrada) {
	string line;
	getline(entrada, line, ' ');
	getline(entrada, line);
	return stoi(line);
}

float tiempo_maximo(ifstream &entrada) {
	string line;
	getline(entrada, line, ' ');
	getline(entrada, line);
	return stof(line);
}

void guardar_nodos(ifstream &entrada, vector<vector<float> > &ubicaciones, vector<int> &puntajes) {
	string line;
	int i = 0;

	while (getline(entrada, line, ' ')) {
		ubicaciones[i][0] = stof(line);
		getline(entrada, line, ' ');
		ubicaciones[i][1] = stof(line);
		getline(entrada, line);
		puntajes.push_back(stoi(line));
		i++;
	}
	return;
}

float DistanciaEntrePuntos(float x1, float y1, float x2, float y2){
		float dx = (x2 - x1);
		float dy = (y2 - y1);
		return sqrt(pow(dx, 2) + pow(dy, 2));
}

bool nodo_in_path(int &nodo){
	if(path_actual.empty()){
		cout << "nodo_in_path, nodo: " << nodo << " No esta en path. Return False.\n";
    return false;
  }
	for (int i = 0; i < path_actual.size(); i++){
		if (path_actual[i].nodo == nodo){
			cout << "true\n";
			return true;
		}
	}
	cout << "false\n";
	return false;
}

bool viola_tiempo(parada &camino){
	if(path_actual.empty()){
		if (distancias[0][camino.nodo] +  distancias[n_nodos - 1][camino.nodo] <= t_max){
			return false;
		}
    	return true;
  }
	vector<int> nodos_misma_ruta;
	float t_ruta = 0;
	for (int i=0; i< path_actual.size(); i++){
		if (path_actual[i].ruta == camino.ruta){
			nodos_misma_ruta.push_back(path_actual[i].nodo);
		}
	}
	nodos_misma_ruta.push_back(camino.nodo);
	cout << "Viola tiempo, nodos en la misma ruta (" << camino.ruta << "): ";
	for (int i=0; i<nodos_misma_ruta.size(); i++){
		cout << nodos_misma_ruta[i] << ' ';
	}
	cout << "\n";
	//En este momento nodos_misma_ruta contiene los nodos utilizados en una ruta a evaluar la restriccion de tiempo.

	for (int i=0; i< nodos_misma_ruta.size()-1; i++){
		t_ruta += distancias[nodos_misma_ruta[i]][nodos_misma_ruta[i+1]];
	}
	cout << "tiempo ruta: " << t_ruta << "\n";
	t_ruta += distancias[0][nodos_misma_ruta[0]];
	t_ruta += distancias[nodos_misma_ruta.back()][n_nodos-1];
	cout << "tiempo ruta: " << t_ruta << "\n";
	if(t_ruta <= t_max){
		return false;
	}

	else{
		return true;
	}
}

void Reg_sol(){
	int cont = 0;

	for (int j=0 ; j<path_actual.size() ; j++){
		cont += puntajes[path_actual[j].nodo];
	}

	if (cont > puntaje_solucion){
		puntaje_solucion = cont;
		path_solucion = path_actual;
	}

	return;
}

void Recursivo(int n_path, bool control){
	parada camino;

	for (int i = 1; i < n_nodos - 1 ; i++){
		camino.ruta = n_path;
		camino.nodo = i;

		//Si el nodo agregado esta en el camino, entonces si o si existe una ruta mas optima, por lo que realiza backtracking (cambio de rama)
		if (nodo_in_path(camino.nodo)){
			continue;
		}

		//Si el nodo agregado hace violar la condicion de tiempo al camino, entonces no es solucion ni ninguno de sus hijos lo sera, por lo que realiza backtracking.
		else if (viola_tiempo(camino)){
			continue;
		}

		//Si el nodo agregado cumple restricciones, se llama a la recursividad.
		//Terminada la recursividad, si hay al menos un nodo en cada ruta, se evalua si es mejor solucion hasta el momento.
		else{
			path_actual.push_back(camino);
			Recursivo(n_path, true);
			if (n_path == n_rutas){
				Reg_sol();
			}
			//En este punto ya se evaluo la solucion y todas las posibles soluciones hijas, por lo que realiza backtracking.
			path_actual.pop_back();
		}

		}

		if (control && (n_path < n_rutas)){
			Recursivo(n_path+1, true);
		}

		return;
}

int main(){
	string line;
	ifstream entrada ("Input.txt");

	if (entrada.is_open()) {
		//Determinar numero de nodos y el numero de rutas a generar
		n_nodos = numero_nodos(entrada);
		n_rutas = numero_rutas(entrada);
		t_max = tiempo_maximo(entrada);

		//2d-Vector que guardara la ubicacion de cada nodo para posteriormente generar una matriz con la distancia entre ellos.
		vector<vector<float>> ubicaciones(n_nodos, vector<float>(2));

		//Funcion que guarda ubicacion y puntaje de nodos.
		guardar_nodos(entrada, ubicaciones, puntajes);
		//while (getline(entrada, line)) {
		//	cout << line << '\n';
		//}
		cout << "Numero de nodos: " << n_nodos << '\n';
		cout << "Numero de rutas: " << n_rutas << '\n';
		cout << "Tiempo maximo por ruta: " << t_max << '\n';
		entrada.close();

		//Generar matriz que contiene distancias entre cada par de nodos
		vector<vector<float>> aux(n_nodos, vector<float>(n_nodos));

		for (int i = 0; i <= n_nodos - 1 ; i++){
			for (int j = i + 1; j <= n_nodos - 1; j++){
				aux[i][j] = DistanciaEntrePuntos(ubicaciones[i][0], ubicaciones[i][1], ubicaciones[j][0], ubicaciones[j][1]);
				aux[j][i] = aux[i][j];
			}
			aux[i][i] = 0;
		}
		distancias = aux;
		//cout << distancias[0][5] << '\n';
	}

	else {
		cout << "No se pudo abrir el archivo de input.";
	}

	ofstream myfile ("disti.txt");
  if (myfile.is_open())
  {
    for (int i=0 ; i<distancias.size(); i++){
			for (int j = 0; j < distancias.size(); j++) {
				myfile << distancias[i][j] << "\t";
			}
			myfile << "\n";
		}
		myfile.close();
  }
  else cout << "Unable to open file";

	clock_t start;
  double duration;
  start = clock();
	//Comienzo de recursion
	//Recursivo(1, false);
	duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
  cout << "Duracion de ejecucion: " << duration << "\n";
	//Resultados
	/*
	int ac = 1;
	for (int i=0; i<path_solucion.size(); i++){
		if (ac != path_solucion[i].ruta){
			cout << '\n';
			ac += 1;
		}

		cout << path_solucion[i].nodo << ' ';
	}*/
	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
