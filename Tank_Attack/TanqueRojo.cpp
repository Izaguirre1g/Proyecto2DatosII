#include "TanqueRojo.h"
#include "Dijkstra.h"
#include <cstdlib> // Para rand()

TanqueRojo::TanqueRojo(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {}

void TanqueRojo::mover() {
    if (rand() % 5 < 4) {
        std::cout << "Movimiento mediante Dijkstra de rojo" << std::endl;
        // Movimiento mediante Dijkstra (80% de probabilidad)
        if (nodoObjetivo != -1) {
            dijkstra(*grafo, nodoActual);
            nodoActual = nodoObjetivo; // Para simplificar, asumimos que el tanque llega al objetivo
        }
    } else {
        std::cout << "Movimiento aleatorio de rojo" << std::endl;
        // Movimiento aleatorio (20% de probabilidad)
        int numNodos = grafo->getNumNodos();
        nodoActual = rand() % numNodos;
    }
}
