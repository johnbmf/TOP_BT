// ConsoleApplication1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>

//Global
using namespace std;

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

int tiempo_maximo(ifstream &entrada) {
	string line;
	getline(entrada, line, ' ');
	getline(entrada, line);
	return stoi(line);
}

void guardar_nodos(ifstream &entrada, vector<vector<float> > &ubicaciones, vector<int> &puntajes) {
	string line;
	int i = 0;

	while (getline(entrada, line, ' ')) {
		ubicaciones[i][0] = stof(line);
		getline(entrada, line, ' ');
		ubicaciones[i][1] = stof(line);
		getline(entrada, line);
		puntajes[i] = stoi(line);
		i++;
	}
	return;
}

float DistanciaEntrePuntos(float x1, float y1, float x2, float y2){
		float dx = (x2 - x1);
		float dy = (y2 - y1);
		return sqrt(pow(dx, 2) + pow(dy, 2));
}

int main()
{
	string line;
	int n_nodos, n_rutas, t_max;
	ifstream entrada ("input.txt");

	if (entrada.is_open()) {
		//Determinar numero de nodos y el numero de rutas a generar
		n_nodos = numero_nodos(entrada);
		n_rutas = numero_rutas(entrada);
		t_max = tiempo_maximo(entrada);

		//2d-Vector que guardara la ubicacion de cada nodo para posteriormente generar una matriz con la distancia entre ellos.
		vector<vector<float>> ubicaciones(n_nodos, vector<float>(2));
		//1d-Vector que guarda el puntaje de cada nodo
		vector<int> puntajes(n_nodos);

		//Funcion que guarda ubicacion y puntaje de nodos.
		guardar_nodos(entrada, ubicaciones, puntajes);
		//while (getline(entrada, line)) {
		//	cout << line << '\n';
		//}
		cout << "Numero de nodos: " << n_nodos << '\n';
		cout << "Numero de rutas: " << n_rutas << '\n';
		entrada.close();

		//Generar matriz que contiene distancias entre cada par de nodos
		vector<vector<float>> distancias(n_nodos, vector<float>(n_nodos));

		for (int i = 0; i <= n_nodos - 1 ; i++){
			for (int j = i + 1; j <= n_nodos - 1; j++){
				distancias[i][j] = DistanciaEntrePuntos(ubicaciones[i][0], ubicaciones[i][1], ubicaciones[j][0], ubicaciones[j][1]);
				distancias[j][i] = distancias[i][j];
			}
			distancias[i][i] = 0;
		}

		// cout << distancias[0][5] << '\n';
	}

	else {
		cout << "No se pudo abrir el archivo de input.";
	}

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
