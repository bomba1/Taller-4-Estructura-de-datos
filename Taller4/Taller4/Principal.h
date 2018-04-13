#pragma once
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
#include <iostream>
#include <thread>
class Principal
{
public:

	void menuPrincipal();
	void subMenu();
	void leerDatos();
	void ordenamientoQuick(int * arr, int izq, int dere,int hilos);
	void ordenamientoQuickConHilos(int* arr, int izq, int dere,int hilos);
	void merge_S(int * arr, int l, int r);
	void merge(int * arr, int l, int m, int r);
	void imprimirDatosOriginales();
	void imprimirDatosOrdenados();
	void mergeSortConHilos(int* arr, int izq, int dere, int hilos);
	void crearTxt();
	Principal();
	~Principal();

private:
	int* datoPtr = new int[1000];
	int* datoPtr2 = new int[1000];
	int contador = 0;
};


