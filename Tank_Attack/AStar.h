#ifndef ASTAR_H
#define ASTAR_H

#include "Grafo.h"

// Declaración de la función A* que ahora devuelve el camino y su longitud
int* aEstrella(Grafo& grafo, int inicio, int objetivo, int& longitudCamino);

#endif // ASTAR_H
