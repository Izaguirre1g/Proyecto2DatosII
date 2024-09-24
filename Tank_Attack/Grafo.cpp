#include "Grafo.h"
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

void Grafo::conectarConDistancia(int nodo1, int nodo2) {
    if (nodo1 >= 0 && nodo1 < numNodos && nodo2 >= 0 && nodo2 < numNodos) {
        int deltaX = posicionesX[nodo2] - posicionesX[nodo1];
        int deltaY = posicionesY[nodo2] - posicionesY[nodo1];
        int distancia = static_cast<int>(std::sqrt(deltaX * deltaX + deltaY * deltaY));
        conectarNodos(nodo1, nodo2, distancia);
    } else {
        cout << "Nodos fuera de rango.\n";
    }
}

int Grafo::getNumNodos() const {
    return numNodos;
}

int Grafo::getPosicionX(int nodo) const {
    if (nodo >= 0 && nodo < numNodos) {
        return posicionesX[nodo];
    }
    return -1; // Error: nodo fuera de rango
}

int Grafo::getPosicionY(int nodo) const {
    if (nodo >= 0 && nodo < numNodos) {
        return posicionesY[nodo];
    }
    return -1; // Error: nodo fuera de rango
}

int Grafo::obtenerPeso(int nodo1, int nodo2) const {
    if (nodo1 >= 0 && nodo1 < numNodos && nodo2 >= 0 && nodo2 < numNodos) {
        return matrizAdyacencia[nodo1][nodo2];
    }
    return -1; // Error: nodos fuera de rango
}

int Grafo::heuristica(int nodo1, int nodo2) {
    int deltaX = posicionesX[nodo2] - posicionesX[nodo1];
    int deltaY = posicionesY[nodo2] - posicionesY[nodo1];
    return static_cast<int>(std::sqrt(deltaX * deltaX + deltaY * deltaY));
}

void Grafo::mostrarMatriz() {
    for (int i = 0; i < numNodos; ++i) {
        for (int j = 0; j < numNodos; ++j) {
            cout << matrizAdyacencia[i][j] << " ";
        }
        cout << endl;
    }
}

Grafo::~Grafo() {
    for (int i = 0; i < numNodos; ++i) {
        delete[] matrizAdyacencia[i];
    }
    delete[] matrizAdyacencia;
    delete[] posicionesX;
    delete[] posicionesY;
}

