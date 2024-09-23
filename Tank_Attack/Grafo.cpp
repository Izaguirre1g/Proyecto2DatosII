// Grafo.cpp
#include "Grafo.h"

Grafo::Grafo(int n) : numNodos(n) {
    matrizAdyacencia = new int*[numNodos];
    for (int i = 0; i < numNodos; ++i) {
        matrizAdyacencia[i] = new int[numNodos];
        for (int j = 0; j < numNodos; ++j) {
            matrizAdyacencia[i][j] = 0;
        }
    }
    posicionesX = new int[numNodos];
    posicionesY = new int[numNodos];
}

// Método que devuelve el número de nodos
int Grafo::obtenerNumNodos() const {
    return numNodos;
}

// Nuevo método para acceder a la matriz de adyacencia
int Grafo::obtenerPeso(int nodo1, int nodo2) const {
    if (nodo1 >= 0 && nodo1 < numNodos && nodo2 >= 0 && nodo2 < numNodos) {
        return matrizAdyacencia[nodo1][nodo2];
    }
    return -1; // Devuelve -1 si los nodos no son válidos
}

void Grafo::asignarPosicion(int nodo, int x, int y) {
    if (nodo >= 0 && nodo < numNodos) {
        posicionesX[nodo] = x;
        posicionesY[nodo] = y;
    } else {
        std::cout << "Nodo fuera de rango.\n";
    }
}

void Grafo::conectarNodos(int nodo1, int nodo2, int peso) {
    if (nodo1 >= 0 && nodo1 < numNodos && nodo2 >= 0 && nodo2 < numNodos) {
        matrizAdyacencia[nodo1][nodo2] = peso;
    } else {
        std::cout << "Nodos fuera de rango.\n";
    }
}

void Grafo::conectarConDistancia(int nodo1, int nodo2) {
    if (nodo1 >= 0 && nodo1 < numNodos && nodo2 >= 0 && nodo2 < numNodos) {
        int deltaX = posicionesX[nodo2] - posicionesX[nodo1];
        int deltaY = posicionesY[nodo2] - posicionesY[nodo1];
        int distancia = static_cast<int>(std::sqrt(deltaX * deltaX + deltaY * deltaY));
        conectarNodos(nodo1, nodo2, distancia);
    } else {
        std::cout << "Nodos fuera de rango.\n";
    }
}

void Grafo::mostrarMatriz() {
    for (int i = 0; i < numNodos; ++i) {
        for (int j = 0; j < numNodos; ++j) {
            std::cout << matrizAdyacencia[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int Grafo::heuristica(int nodo1, int nodo2) {
    int deltaX = posicionesX[nodo2] - posicionesX[nodo1];
    int deltaY = posicionesY[nodo2] - posicionesY[nodo1];
    return static_cast<int>(std::sqrt(deltaX * deltaX + deltaY * deltaY));
}

int Grafo::obtenerPosX(int nodo) const {
    if (nodo >= 0 && nodo < numNodos) {
        return posicionesX[nodo];
    }
    std::cout << "Nodo fuera de rango.\n";
    return -1; // Valor por defecto en caso de error
}

int Grafo::obtenerPosY(int nodo) const {
    if (nodo >= 0 && nodo < numNodos) {
        return posicionesY[nodo];
    }
    std::cout << "Nodo fuera de rango.\n";
    return -1; // Valor por defecto en caso de error
}


Grafo::~Grafo() {
    for (int i = 0; i < numNodos; ++i) {
        delete[] matrizAdyacencia[i];
    }
    delete[] matrizAdyacencia;
    delete[] posicionesX;
    delete[] posicionesY;
}
