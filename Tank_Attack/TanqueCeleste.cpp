/*#include "TanqueCeleste.h"
#include "BFS.h"
#include <cstdlib> // Para rand()

TanqueCeleste::TanqueCeleste(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {}

void TanqueCeleste::mover() {
    if (rand() % 2 == 0) {
        std::cout << "Movimiento aleatorio de celeste" << std::endl;
        // Movimiento aleatorio
        int numNodos = grafo->getNumNodos();
        nodoActual = rand() % numNodos;
    } else {
        std::cout << "Movimiento mediante BFS de celeste" << std::endl;
        // Movimiento mediante BFS
        if (nodoObjetivo != -1) {
            bfs(*grafo, nodoActual, nodoObjetivo);
            nodoActual = nodoObjetivo; // Para simplificar, asumimos que el tanque llega al objetivo
        }
    }
}*/
