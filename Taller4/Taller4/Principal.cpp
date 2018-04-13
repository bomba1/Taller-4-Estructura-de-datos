#include "stdafx.h"
#include "Principal.h"
#include <chrono>
#include <ctime>
#include<vector>

/*Este metodo es el que ejecuta el menu principal del programa
*/
void Principal::menuPrincipal() {

	bool menu = true;

	cout << "Bienvenido al menu principal" << endl;
	string opcion;
	while (menu) {  //While infinito que es usado para el menu principal

		cout << "Menu principal:" << endl;
		cout << "1.-Ordenar arreglos\n2.-Salir" << endl;
		cin >> opcion;
		try
		{
			std::stoi(opcion);
		}
		catch (const std::exception&)
		{
			cout << "Error,no escribio un numero" << endl;
			continue;
		}
		int opcionDef = std::stoi(opcion);

		switch (opcionDef) //Menu
		{
		case 1:
			subMenu();
			break;
		case 2:
			cout << "Adios, Buena suerte!" << endl;
			return;
		default:
			cout << "Error, ingrese una opcion valida porfavor" << endl;
			break;
		}

	}
}

/*Metodo que ejectuta el submenu de modificacion de arboles
*/
void Principal::subMenu() {
	
	bool menu = true;
	cout << "Usted escogio ordenar arreglo" << endl;
	string opcion;
	int hilos = 0;
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	while (menu) { //While infinito que sera usado para el submenu

		cout << "Escoja el algoritmo que desee" << endl;
		cout << "1.-QuickSort-Secuencial\n2.-QuickSort-Paralelo\n3.-MergeSort-Secuencial\n4.-MergeSort-Paralelo\n5.-Volver" << endl;
		cin >> opcion;
		try
		{
			std::stoi(opcion);
		}
		catch (const std::exception&)

		{
			cout << "Error,no escribio un numero" << endl;
			continue;
		}
		int opcionDef = std::stoi(opcion);

		switch (opcionDef) //Menu
		{
		case 1:
			t1 = std::chrono::high_resolution_clock::now();
			ordenamientoQuick(this->datoPtr,0,this->contador-1,0);  //Se ordena el vector y se calcula el tiempo de ejecucion
			t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> tiempo = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			cout<<"El algoritmo de ordenamiento se llama" << " Quicksort Secuencial " << endl;
			cout << "El arrego ordenado tiene " << this->contador << " datos" << endl;
			cout << "Este es el arreglo original:" << endl;
			imprimirDatosOriginales();
			cout << "Y este es el arreglo ordenado:" << endl;
			imprimirDatosOrdenados();
			std::cout << "El algoritmo se demoro " << tiempo.count() << " segundos. \n" << endl;
			*this->datoPtr = *this->datoPtr2;
			break;
		case 2:
			cout << "Ingrese la cantidad de hilos que desea usar" << endl;
			cin >> hilos;
			t1 = std::chrono::high_resolution_clock::now();
			ordenamientoQuickConHilos(this->datoPtr,0,this->contador-1,hilos);	//Se ordena el vector y se calcula el tiempo de ejecucion
			t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> tiempo2 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			cout << "El algoritmo de ordenamiento se llama" << " Quicksort Paralelo " << endl;
			cout << "El arrego ordenado tiene " << this->contador << " datos" << endl;
			cout << "La cantidad de hilos utilizados fue de " << hilos << endl;
			cout << "Este es el arreglo original:" << endl;
			imprimirDatosOriginales();
			cout << "Y este es el arreglo ordenado:" << endl;
			imprimirDatosOrdenados();
			std::cout << "El algoritmo se demoro " << tiempo2.count() << " segundos. \n" << endl;
			*this->datoPtr = *this->datoPtr2;
			break;
		case 3:
			t1 = std::chrono::high_resolution_clock::now();
			merge_S(this->datoPtr, 0, this->contador - 1);//Se ordena el vector y se calcula el tiempo de ejecucion
			t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> tiempo3 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			cout << "El algoritmo de ordenamiento se llama" << " MedgeSort Secuencial" << endl;
			cout << "El arrego ordenado tiene " << this->contador << " datos" << endl;
			cout << "Este es el arreglo original:" << endl;
			imprimirDatosOriginales();
			cout << "Y este es el arreglo ordenado:" << endl;
			imprimirDatosOrdenados();
			std::cout << "El algoritmo se demoro " << tiempo3.count() << " segundos. \n" << endl;
			*this->datoPtr = *this->datoPtr2;
			
			break;
		case 4:
			cout << "Ingrese la cantidad de hilos que desea usar" << endl;
			cin >> hilos;
			t1 = std::chrono::high_resolution_clock::now();
			mergeSortConHilos(this->datoPtr, 0, this->contador - 1, hilos);//Se ordena el vector y se calcula el tiempo de ejecucion
			t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> tiempo4 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
			cout << "El algoritmo de ordenamiento se llama" << " MedgeSort Paralelo " << endl;
			cout << "El arrego ordenado tiene " << this->contador << " datos" << endl;
			cout << "La cantidad de hilos utilizados fue de " << hilos << endl;
			cout << "Este es el arreglo original:" << endl;
			imprimirDatosOriginales();
			cout << "Y este es el arreglo ordenado:" << endl;
			imprimirDatosOrdenados();
			std::cout << "El algoritmo se demoro " << tiempo4.count() << " segundos. \n" << endl;
			*this->datoPtr = *this->datoPtr2;
			break;
		case 5:
			cout << "Volviendo..." << endl;
			return;
		default:
			cout << "Error, ingrese una opcion valida porfavor" << endl;
			break;
		}

	}
}
/*Metodo que deja lee los datos desde un archivo de texto e introduce estos datos a un arreglo sobredimensionado
*/
void Principal::leerDatos()
{
	string linea;
	int dato;
	string numStr;
	ifstream archEntr("Datos.txt");
	if (archEntr.is_open()) {
		while (getline(archEntr, linea))
		{
			stringstream st(linea);
			while (getline(st, numStr, ',')) {
				dato = stoi(numStr.c_str());
				datoPtr[this->contador] = dato;
				datoPtr2[this->contador] = dato;
				this->contador++;
			}


		}



	}archEntr.close();
	

}
/*Metodo que ordena un algoritmo usando quicksort
*/
void Principal::ordenamientoQuick(int * arr, int izq, int dere,int hilos)
{
	int i = izq, j = dere;
	int tmp;
	int pivote = arr[(izq + dere) / 2];
	/* particion */
	while (i <= j) {
		while (arr[i] < pivote)i++;
		while (arr[j] > pivote)j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}

	};
	/* recursion */
	if (izq < j)ordenamientoQuick(arr, izq, j,hilos);
	if (i < dere)ordenamientoQuick(arr, i, dere,hilos);



}


/*Metodo que imprime los datos del arreglo copiado con los datos leidos del archivo
*/
void Principal::imprimirDatosOriginales()
{
	cout << "[";
	for (int i = 0; i < this->contador; i++) {
		cout << this->datoPtr2[i];
		if ((i + 1) == this->contador) {
			break;
		}
		cout << ",";
	}
	cout << "]" << endl;
}
/*Metodo que imprime los datos del arreglo editado por los quicksort
*/
void Principal::imprimirDatosOrdenados()
{
	cout << "[";
	for (int i = 0; i < this->contador; i++) {
		cout << this->datoPtr[i];
		if ((i + 1) == this->contador) {
			break;
		}
		cout << ",";
	}
	cout << "]" << endl;
}
/*Metodo de medgeSort con hilos
*/
void Principal::mergeSortConHilos(int * arr, int izq, int dere, int hilos)
{
	if (izq < dere) {
		int m = izq + (dere - izq) / 2;
		if (hilos > 0) {
			std::thread t1([&] {mergeSortConHilos(ref(arr), izq, dere, hilos - 1); });
			std::thread t2([&] {mergeSortConHilos(ref(arr), izq, dere, hilos - 1); });
			t1.join();
			t2.join();
			
		}
		else {
			
			merge_S(arr, izq, m);
			merge_S(arr, m + 1, dere);
			merge(arr, izq, m, dere);
		}

	}
	 
		
	

}
/*Crea arreglos con numeros random
*/
void Principal::crearTxt()
{
	std::ofstream ofile;
	ofile.open("Datos1.txt", std::ios::app);

	for (int i = 0; i < 1000 - 1; i++)
	{
		int output = 0 + (rand() % static_cast<int>(1000 - 0 + 1));
		ofile << output << ",";
	}
	ofile << 14 << endl;
	ofile.close();
}

/*Metodo de ordenamiento quicksort con hilos
*/
void Principal::ordenamientoQuickConHilos(int* arr, int izq, int dere,int hilos)
{	
	int i = izq, j = dere;
	int tmp;
	int pivote = arr[(izq + dere) / 2];
	/* particion */
	while (i <= j) {
		while (arr[i] < pivote)i++;
		while (arr[j] > pivote)j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}

	};
	
	if (hilos > 0) {
		std::thread t1([&] {ordenamientoQuickConHilos(ref(arr), izq,j, hilos - 1); });
		std::thread t2([&] {ordenamientoQuickConHilos(ref(arr), i, dere, hilos - 1); });
		t1.join();
		t2.join();
	}
	else {
		if (izq < j)ordenamientoQuick(arr, izq, j, hilos);
		if (i < dere)ordenamientoQuick(arr, i, dere, hilos);
	}
	
	
	

}
/*Metodo recursivo de mergesort
*/
void Principal::merge_S(int * arr, int l, int r)
{

	if (l < r) {
		int m = l + (r - l) / 2;
		merge_S(arr, l, m);
		merge_S(arr, m + 1, r);
		merge(arr, l, m, r);

	}



}

/*Metodo de mezcla de medgesort
*/
void Principal::merge(int * arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	//sobre dimensiono los arreglos 
	int L[5000], R[5000];
	for (i = 0; i < n1; i++)L[i] = arr[l + i];
	for (j = 0; j < n2; j++)R[j] = arr[m + 1 + j];
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}


	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}


	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}

}









/*Constructor de la clase
*/
Principal::Principal()
{
	
	leerDatos();
	menuPrincipal();
}


/*Destructor de la clase
*/
Principal::~Principal()
{	
	
}
