#include "Grafo.h"
#include <cmath>
#include <iostream>
#include <random>
using namespace std;

Grafo::Grafo(int n) : numNodos(n) {
    // Inicializar la matriz de adyacencia
    matrizAdyacencia = new int*[numNodos];
    for (int i = 0; i < numNodos; ++i) {
        matrizAdyacencia[i] = new int[numNodos];
        for (int j = 0; j < numNodos; ++j) {
            matrizAdyacencia[i][j] = 0;
        }
    }

    // Inicializar las posiciones X e Y de los nodos
    posicionesX = new int[numNodos];
    posicionesY = new int[numNodos];
}

// Generar números aleatorios en un rango dado
int Grafo::generarPesoAleatorio(int min, int max) {
    static random_device rd;  // Dispositivo de entropía para semilla
    static mt19937 gen(rd());  // Generador Mersenne Twister
    uniform_int_distribution<> dis(min, max);  // Distribución uniforme entre min y max
    return dis(gen);  // Genera un número aleatorio
}

void Grafo::asignarPosicion(int nodo, int x, int y) {
    if (nodo >= 0 && nodo < numNodos) {
        posicionesX[nodo] = x;
        posicionesY[nodo] = y;
    } else {
        cout << "Nodo fuera de rango.\n";
    }
}

void Grafo::conectarNodos(int nodo1, int nodo2, int peso) {
    if (nodo1 >= 0 && nodo1 < numNodos && nodo2 >= 0 && nodo2 < numNodos) {
        matrizAdyacencia[nodo1][nodo2] = peso;
    } else {
        cout << "Nodos fuera de rango.\n";
    }
}

// Generar los nodos como una matriz en un área dada y conectarlos en 8 direcciones
void Grafo::generarMatriz(int ancho, int alto, int espaciado) {
    int filas = alto / espaciado;
    int columnas = ancho / espaciado;
    int nodo = 0;
    int pesoAleatorio = generarPesoAleatorio(1,990);

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (nodo >= numNodos) break;  // Evitar desbordamiento de nodos
            int x = j * espaciado;
            int y = i * espaciado;
            asignarPosicion(nodo, x, y);

            // Conectar con el nodo de la izquierda
            if (j > 0) {
                conectarNodos(nodo, nodo - 1, pesoAleatorio);
                conectarNodos(nodo - 1, nodo, pesoAleatorio);  // Conexión bidireccional
            }

            // Conectar con el nodo de arriba
            if (i > 0) {
                conectarNodos(nodo, nodo - columnas, pesoAleatorio);
                conectarNodos(nodo - columnas, nodo, pesoAleatorio);  // Conexión bidireccional
            }

            // Conectar en las 4 direcciones diagonales
            if (i > 0 && j > 0) {  // Arriba-izquierda
                conectarNodos(nodo, nodo - columnas - 1, pesoAleatorio);
                conectarNodos(nodo - columnas - 1, nodo, pesoAleatorio);
            }
            if (i > 0 && j < columnas - 1) {  // Arriba-derecha
                conectarNodos(nodo, nodo - columnas + 1, pesoAleatorio);
                conectarNodos(nodo - columnas + 1, nodo, pesoAleatorio);
            }
            if (i < filas - 1 && j > 0) {  // Abajo-izquierda
                conectarNodos(nodo, nodo + columnas - 1, pesoAleatorio);
                conectarNodos(nodo + columnas - 1, nodo, pesoAleatorio);
            }
            if (i < filas - 1 && j < columnas - 1) {  // Abajo-derecha
                conectarNodos(nodo, nodo + columnas + 1, pesoAleatorio);
                conectarNodos(nodo + columnas + 1, nodo, pesoAleatorio);
            }

            nodo++;
        }
    }
}

int Grafo::heuristica(int nodo1, int nodo2) {
    if (nodo1 >= 0 && nodo1 < numNodos && nodo2 >= 0 && nodo2 < numNodos) {
        // Calculamos la distancia euclidiana entre nodo1 y nodo2
        int deltaX = posicionesX[nodo2] - posicionesX[nodo1];
        int deltaY = posicionesY[nodo2] - posicionesY[nodo1];
        return static_cast<int>(std::sqrt(deltaX * deltaX + deltaY * deltaY));
    }
    return -1;  // Error: nodos fuera de rango
}

int Grafo::getNumNodos() const {
    return numNodos;
}

int Grafo::getPosicionX(int nodo) const {
    if (nodo >= 0 && nodo < numNodos) {
        return posicionesX[nodo];
    }
    return -1;
}

int Grafo::getPosicionY(int nodo) const {
    if (nodo >= 0 && nodo < numNodos) {
        return posicionesY[nodo];
    }
    return -1;
}

int Grafo::obtenerPeso(int nodo1, int nodo2) const {
    if (nodo1 >= 0 && nodo1 < numNodos && nodo2 >= 0 && nodo2 < numNodos) {
        return matrizAdyacencia[nodo1][nodo2];
    }
    return -1; // Error
}

Grafo::~Grafo() {
    for (int i = 0; i < numNodos; ++i) {
        delete[] matrizAdyacencia[i];
    }
    delete[] matrizAdyacencia;
    delete[] posicionesX;
    delete[] posicionesY;
}


