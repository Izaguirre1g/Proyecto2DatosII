#include "Grafo.h"
#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>

Grafo::Grafo(int n) : numNodos(n) {
    srand(static_cast<unsigned>(time(0)));
    //Matriz de adyacencia
    matrizAdyacencia = new int*[numNodos];
    for (int i = 0; i < numNodos; ++i) {
        matrizAdyacencia[i] = new int[numNodos];
        for (int j = 0; j < numNodos; ++j) {
            matrizAdyacencia[i][j] = 0;
        }
    }

    //Las posiciones X e Y de los nodos
    posicionesX = new int[numNodos];
    posicionesY = new int[numNodos];

    nodosBloqueados = new bool[numNodos];
    std::fill(nodosBloqueados, nodosBloqueados + numNodos, false);  // Ningún nodo está bloqueado inicialmente
}

void Grafo::asignarPosicion(int nodo, int x, int y) {
    if (nodo >= 0 && nodo < numNodos) {
        posicionesX[nodo] = x;
        posicionesY[nodo] = y;
    } else {
        std::cout << "Nodo fuera de rango.\n";
    }
}

void Grafo::conectarNodos(int nodo1, int nodo2) {
    if (nodo1 >= 0 && nodo1 < numNodos && nodo2 >= 0 && nodo2 < numNodos) {
        int peso = 1 + rand() % 500;  // Peso aleatorio entre 1 y 10
        matrizAdyacencia[nodo1][nodo2] = peso;
    } else {
        std::cout << "Nodos fuera de rango.\n";
    }
}

bool Grafo::esNodoBloqueado(int nodo) const {
    return nodosBloqueados[nodo];  // Retorna true si el nodo está bloqueado
}

// Genera los nodos como una matriz en un área dada y conectarlos en 8 direcciones
void Grafo::generarMatriz(int ancho, int alto, int espaciado) {
    int filas = alto / espaciado;
    int columnas = ancho / espaciado;
    int nodo = 0;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (nodo >= numNodos) break;
            int x = j * espaciado;
            int y = i * espaciado;
            asignarPosicion(nodo, x, y);

            // Conectar con el nodo de la izquierda
            if (j > 0) {
                conectarNodos(nodo, nodo - 1);
                conectarNodos(nodo - 1, nodo);  // Conexión bidireccional
            }

            // Conectar con el nodo de arriba
            if (i > 0) {
                conectarNodos(nodo, nodo - columnas);
                conectarNodos(nodo - columnas, nodo);  // Conexión bidireccional
            }

            // Conectar en las 4 direcciones diagonales
            if (i > 0 && j > 0) {  // Arriba-izquierda
                conectarNodos(nodo, nodo - columnas - 1);
                conectarNodos(nodo - columnas - 1, nodo);
            }
            if (i > 0 && j < columnas - 1) {  // Arriba-derecha
                conectarNodos(nodo, nodo - columnas + 1);
                conectarNodos(nodo - columnas + 1, nodo);
            }
            if (i < filas - 1 && j > 0) {  // Abajo-izquierda
                conectarNodos(nodo, nodo + columnas - 1);
                conectarNodos(nodo + columnas - 1, nodo);
            }
            if (i < filas - 1 && j < columnas - 1) {  // Abajo-derecha
                conectarNodos(nodo, nodo + columnas + 1);
                conectarNodos(nodo + columnas + 1, nodo);
            }

            nodo++;
        }
    }
}


int Grafo::encontrarNodoCercano(int x, int y) {
    int nodoCercano = -1;
    double distanciaMinima = std::numeric_limits<double>::max();

    for (int i = 0; i < numNodos; ++i) {
        int nodoX = getPosicionX(i);
        int nodoY = getPosicionY(i);
        double distancia = std::sqrt(std::pow(x - nodoX, 2) + std::pow(y - nodoY, 2));

        if (distancia < distanciaMinima) {
            distanciaMinima = distancia;
            nodoCercano = i;
        }
    }

    return nodoCercano;
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

int Grafo::obtenerNumNodos() const {
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


//Genera obstáculos aleatorios en el mapa con restricciones para evitar los bordes
void Grafo::asignarObstaculosAleatorios(int numObstaculos) {
    int margen = 5;  // Distancia mínima del borde
    int asignados = 0;
    while (asignados < numObstaculos) {
        int nodoAleatorio = rand() % numNodos;

        // Evitar asignar obstáculos en nodos de inicio de los tanques, nodos ya bloqueados o nodos cerca de los bordes
        int x = getPosicionX(nodoAleatorio);
        int y = getPosicionY(nodoAleatorio);
        if (!nodosBloqueados[nodoAleatorio] && x > margen && x < 800 - margen && y > margen && y < 600 - margen) {
            nodosBloqueados[nodoAleatorio] = true;
            asignados++;

            // Bloquear nodos intermedios entre obstáculos cercanos
            bloquearNodosIntermedios(nodoAleatorio);
        }
    }
}

// Función para bloquear los nodos intermedios entre dos obstáculos cercanos
void Grafo::bloquearNodosIntermedios(int nodo) {
    int columnas = 800 / 50;  // Asumimos que las columnas se basan en el ancho dividido por el espaciado (50 en este caso)

    // Definir las 8 direcciones (horizontal, vertical y diagonal)
    int direcciones[8][2] = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},  // Derecha, Izquierda, Abajo, Arriba
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} // Diagonales
    };

    int x1 = getPosicionX(nodo);
    int y1 = getPosicionY(nodo);

    //Explora las 8 direcciones alrededor del nodo
    for (int i = 0; i < 8; ++i) {
        int dx = direcciones[i][0];
        int dy = direcciones[i][1];

        //Verifica si hay un obstáculo cercano en la dirección actual
        int nodoCercano = encontrarNodoCercano(x1 + dx * 50, y1 + dy * 50);  // Ajustamos el espaciado
        if (nodoCercano != -1 && nodosBloqueados[nodoCercano]) {
            //Bloquea el nodo intermedio entre el nodo actual y el nodo cercano bloqueado
            int nodoIntermedio = encontrarNodoCercano(x1 + (dx * 25), y1 + (dy * 25));  // Mitad de la distancia
            if (nodoIntermedio != -1 && !nodosBloqueados[nodoIntermedio]) {
                nodosBloqueados[nodoIntermedio] = true;
                std::cout << "Nodo intermedio bloqueado entre " << nodo << " y " << nodoCercano << std::endl;
            }
        }
    }
}




Grafo::~Grafo() {
    for (int i = 0; i < numNodos; ++i) {
        delete[] matrizAdyacencia[i];
    }
    delete[] matrizAdyacencia;
    delete[] posicionesX;
    delete[] posicionesY;
    delete[] nodosBloqueados;
}
