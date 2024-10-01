/*#include "TanqueAmarillo.h"
#include "Dijkstra.h"
#include <cstdlib> // Para rand()
#include <iostream>

TanqueAmarillo::TanqueAmarillo(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {
    nodoObjetivo = -1;  // Iniciar sin objetivo definido
}

void TanqueAmarillo::mover() {
    if (rand() % 5 < 4) {
        std::cout << "Movimiento mediante Dijkstra de amarillo" << std::endl;
        // Movimiento mediante Dijkstra (80% de probabilidad)
        if (nodoObjetivo != -1) {
            int longitudCamino = 0;
            int* camino = dijkstra(*grafo, nodoActual, nodoObjetivo, longitudCamino);  // Calcular el camino con Dijkstra

            if (camino != nullptr && longitudCamino > 1) {
                nodoActual = camino[1];  // Moverse al siguiente nodo en el camino
            } else {
                std::cout << "No se encontró un camino válido." << std::endl;
            }

            delete[] camino;  // Liberar la memoria del camino
        } else {
            std::cout << "No se ha establecido un nodo objetivo." << std::endl;
        }
    } else {
        std::cout << "Movimiento aleatorio de amarillo" << std::endl;
        // Movimiento aleatorio (20% de probabilidad)
        int numNodos = grafo->getNumNodos();
        nodoActual = rand() % numNodos;
    }
}*/

