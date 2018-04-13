#include <iostream>
#include <fstream>
#include <string>
#include "mingw.thread.h"
#include <thread>
#include <vector>
#include <ctime>

using namespace std;


int stoint(string texto) {
    int numero = 0;
    char* ch = &texto.at(0);
    for(int i=0; i<texto.length(); i++) {
        if(*ch == '-'){
            ch++;
            continue;
        }
        if (*ch < '0' || *ch > '9') {
            if(*ch == '\n' || *ch == ' ') return numero;
            throw exception();
        }
        numero = numero * 10 + (*ch - '0');
        ch++;
    }
    if(texto.at(0) == '-') return 0 - numero;
    return numero;
}


void setChar(string* texto, char* letra) {
    string aux;
    while(true) {
        cout << "ingrese la letra a buscar: " << endl;
        getline(cin, aux);
        if (aux.length() == 1) {
            *letra = aux.at(0);
            if(*letra >= 'A' && *letra <= 'Z') {
                *letra = 'a' + aux.at(0) - 'A';
                return;
            }
            else if (*letra >= 'a' && *letra <= 'z') {
                *letra = aux.at(0);
                return;
            }
            else {
                cout << "Letra invalida o escribio mas de una." << endl;
            }
        }
    }
}


bool leerArchivo(string* texto, char* letra){
    *texto = "";
    ifstream archivo("TextoTaller4.txt");
    if (!archivo.is_open()) return false;
    string aux;
    while(!archivo.eof()){
        getline(archivo,aux);
        *texto = *texto + aux;
    }
    if(!(texto->compare(""))) return false;
    archivo.close();
    return true;
}

void leerPantalla(string* texto, char* letra){
    cout << "Escriba el texto deseado: " << endl;
    *texto = "vacio";
        cout <<"Ingrese un texto: " << endl;
        getline(cin, *texto);
}


void ingresarTexto(string* texto, char* letra) {
    string numero;
    int opcion;
    while(true) {
        cout << "1 Leer archivo" << endl << "2 Ingreso por pantalla" << endl;
        getline(cin, numero);
        try {
            opcion = stoint(numero);
        } catch(...) {
            cout << "opcion invalida" << endl;
            continue;
        }
        switch(opcion) {
            case 1:
                if(!leerArchivo(texto, letra)) {
                    cout << "No se encontro el archivo o esta vacio." << endl;
                } else return;
                break;
            case 2:
                leerPantalla(texto, letra);
                return;
            default:
                cout << "Entrada invalida" << endl;
                break;
        }
    }
}



int contarLetra(string* texto, char* letra, char* inicio, int cantidad) {
    int contador = 0;
    for(;cantidad != 0; cantidad--, inicio ++) {
        if(*inicio == *letra || *inicio == (*letra - 'a' + 'A')) {
            contador ++;
        }
    }
    return contador;
}


void contarSecuencial(string* texto, char* letra) {
    double inicio = clock();
    int resultado = 0;
    cout << "Veces que aparece la letra " << *letra << ": " << contarLetra(texto, letra, &texto->at(0), texto->length()) << endl;
    cout << "Duracion de busqueda: " << (clock() - inicio) << " unidades de tiempo" << endl;
}

void contarRecursivoHilo(string* texto, char* letra, int* resultado, char* inicio, int cantidad) {
    const int max = 250;
    if(cantidad <= max) {
        *resultado = contarLetra(texto, letra, inicio, cantidad);
    } else {
        int resultado1, resultado2;
        char* letra2 = letra + cantidad/2; // abecedari -> letra 2 = e cant2 = cantidad - cantidad / 2
        thread hilo1(&contarRecursivoHilo, texto, letra, &resultado1, letra, cantidad/2);
        thread hilo2(&contarRecursivoHilo, texto, letra, &resultado2, letra2, cantidad - cantidad/2);
        hilo1.join();
        hilo2.join();
        *resultado = resultado1 + resultado2;
    }
}

void contarRecursivo(string* texto, char* letra) {
    double inicio = clock();
    if(texto->length() == 0) {
        cout << "El texto està vacio" << endl;
    }
    int resultado = 0;
    contarRecursivoHilo(texto, letra, &resultado, &texto->at(0), texto->length());
    cout << "Veces que aparece la letra " << *letra << ": " << contarLetra(texto, letra, &texto->at(0), texto->length()) << endl;
    cout << "Duracion de busqueda: " << (clock() - inicio) << " unidades de tiempo" << endl;
}

void desplegarMenu() {
    string texto;
    char letra;
    
    string aux;
    int opcion;
    while(true) {
        cout << "Seleccione una opcion: " << endl;
        cout << "1 Ingresar texto." << endl;
        cout << "2 Definir caracter a buscar" << endl;
        cout << "3 Conteo secuencial" << endl;
        cout << "4 Conteo recursivo en paralelo" << endl;
        cout << "5 Salir" << endl;
        getline(cin, aux);
        try {
            opcion = stoint(aux);
        } catch(...) {
            cout << "opcion invalida" << endl;
            continue;
        }
        switch(opcion) {
            case 1:
                ingresarTexto(&texto, &letra);
                break;
            case 2:
                setChar(&texto, &letra);
                break;
            case 3:
                contarSecuencial(&texto, &letra);
                break;
            case 4:
                contarRecursivo(&texto, &letra);
                break;
            case 5:
                return;
            default:
                cout << "Entrada invalida" << endl;
                break;
        }
    }
}

int main(int argc, char** argv) {
    desplegarMenu();
    return 0;
    
}