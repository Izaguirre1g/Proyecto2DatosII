#ifndef LINEOFSIGHT_H
#define LINEOFSIGHT_H

#include "Grafo.h"

class LineOfSight {
public:
    LineOfSight(Grafo* grafo);

    // Método principal para verificar si hay línea de vista entre dos nodos
    bool tieneLineaVista(int nodoInicial, int nodoFinal);

private:
    Grafo* grafo;

    // Trazar la línea usando el algoritmo de Bresenham
    int trazarLinea(int x1, int y1, int x2, int y2, int(*linea)[2], int maxSize);

    // Verificar si hay obstáculos a lo largo de la línea
    bool hayObstaculosEnLinea(int(*linea)[2], int puntos);
};

#endif  // LINEOFSIGHT_H
