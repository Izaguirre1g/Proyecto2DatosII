#include "LineOfSight.h"
#include <cmath>
#include <iostream>

LineOfSight::LineOfSight(Grafo* grafo) : grafo(grafo) {}

// Método que verifica si hay línea de vista entre dos nodos
bool LineOfSight::tieneLineaVista(int nodoInicial, int nodoFinal) {
    // Obtener las coordenadas de los nodos inicial y final
    int x1 = grafo->getPosicionX(nodoInicial);
    int y1 = grafo->getPosicionY(nodoInicial);
    int x2 = grafo->getPosicionX(nodoFinal);
    int y2 = grafo->getPosicionY(nodoFinal);

    // Crear un arreglo estático para almacenar los puntos de la línea (máximo 1000 puntos)
    int linea[1000][2];

    // Trazar la línea entre los puntos y obtener el número de puntos generados
    int puntos = trazarLinea(x1, y1, x2, y2, linea, 1000);

    // Verificar si hay obstáculos en la línea
    return !hayObstaculosEnLinea(linea, puntos);
}

// Algoritmo de Bresenham para trazar una línea entre dos puntos
int LineOfSight::trazarLinea(int x1, int y1, int x2, int y2, int(*linea)[2], int maxSize) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int i = 0;  // Índice para almacenar puntos en el arreglo
    while (true) {
        if (i >= maxSize) break;  // Evitar desbordamiento del array

        linea[i][0] = x1;
        linea[i][1] = y1;
        i++;

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    return i;  // Devolver el número de puntos generados
}

// Verificar si hay obstáculos en los puntos de la línea generada
bool LineOfSight::hayObstaculosEnLinea(int linea[][2], int puntos) {
    for (int i = 0; i < puntos; ++i) {
        int nodoCercano = grafo->encontrarNodoCercano(linea[i][0], linea[i][1]);

        // Verificar si el nodo cercano está bloqueado
        if (grafo->esNodoBloqueado(nodoCercano)) {
            std::cout << "Obstáculo encontrado en el nodo: " << nodoCercano << std::endl;
            return true;  // Hay un obstáculo
        }
    }
    return false;  // No se encontraron obstáculos
}

// Nuevo método: Obtener el siguiente nodo en la línea de vista hacia el objetivo
int LineOfSight::obtenerSiguienteNodoEnLinea(int nodoInicial, int nodoFinal) {
    int x1 = grafo->getPosicionX(nodoInicial);
    int y1 = grafo->getPosicionY(nodoInicial);
    int x2 = grafo->getPosicionX(nodoFinal);
    int y2 = grafo->getPosicionY(nodoFinal);

    int linea[1000][2];
    int puntos = trazarLinea(x1, y1, x2, y2, linea, 1000);

    for (int i = 0; i < puntos; ++i) {
        int nodoCercano = grafo->encontrarNodoCercano(linea[i][0], linea[i][1]);

        // Si el nodo está bloqueado, devolver el nodo anterior al obstáculo
        if (grafo->esNodoBloqueado(nodoCercano)) {
            if (i > 0) {
                return grafo->encontrarNodoCercano(linea[i - 1][0], linea[i - 1][1]);
            }
            return nodoInicial;  // Si el obstáculo está en el primer punto, quedarse en el nodo actual
        }
    }
    // Si no hay obstáculos, devolver el nodo objetivo
    return nodoFinal;
}
