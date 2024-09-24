#include "TanqueAmarillo.h"
#include "Dijkstra.h"
#include <cstdlib> // Para rand()

TanqueAmarillo::TanqueAmarillo(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {}

void TanqueAmarillo::mover() {
    if (rand() % 5 < 4) {
        std::cout << "Movimiento mediante Dijkstra de amarillo" << std::endl;
        // Movimiento mediante Dijkstra (80% de probabilidad)
        if (nodoObjetivo != -1) {
            dijkstra(*grafo, nodoActual);
            nodoActual = nodoObjetivo; // Para simplificar, asumimos que el tanque llega al objetivo
        }
    } else {
        std::cout << "Movimiento aleatorio de amarillo" << std::endl;
        // Movimiento aleatorio (20% de probabilidad)
        int numNodos = grafo->obtenerNumNodos();
        nodoActual = rand() % numNodos;
    }
}
