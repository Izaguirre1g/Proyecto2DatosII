#include "TanqueAzul.h"
#include "BFS.h"
#include <cstdlib> // Para rand()

TanqueAzul::TanqueAzul(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {}

void TanqueAzul::mover() {
    if (rand() % 2 == 0) {
        std::cout << "Movimiento aleatorio de azul" << std::endl;
        // Movimiento aleatorio
        int numNodos = grafo->getNumNodos();
        nodoActual = rand() % numNodos;
    } else {
        std::cout << "Movimiento mediante BFS de azul" << std::endl;
        // Movimiento mediante BFS
        if (nodoObjetivo != -1) {
            bfs(*grafo, nodoActual, nodoObjetivo);
            nodoActual = nodoObjetivo; // Para simplificar, asumimos que el tanque llega al objetivo
        }
    }
}
