#include "TanqueCeleste.h"
#include "BFS.h"
#include <cstdlib>  // Para rand()

TanqueCeleste::TanqueCeleste(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {}

void TanqueCeleste::mover() {
    if (rand() % 2 == 0) {  // 50% de probabilidad de moverse aleatoriamente
        std::cout << "Movimiento aleatorio de celeste" << std::endl;
        nodoActual = rand() % grafo->obtenerNumNodos();
        camino = nullptr;
        longitudCamino = 0;
    } else {
        std::cout << "Movimiento mediante BFS de celeste" << std::endl;
        if (nodoObjetivo != -1) {
            // Verificar si el nodo objetivo está bloqueado antes de realizar el movimiento
            if (grafo->nodosBloqueados[nodoObjetivo]) {
                std::cerr << "El nodo objetivo está bloqueado por un obstáculo. No se puede mover el tanque celeste." << std::endl;
                return;
            }
            camino = new int[grafo->obtenerNumNodos()];
            longitudCamino = 0;
            bfs(*grafo, nodoActual, nodoObjetivo, camino, longitudCamino);
            indiceCamino = 0;  // Reiniciar el índice del camino
        }
    }
}

bool TanqueCeleste::haTerminadoCamino() {
    return indiceCamino >= longitudCamino;
}

void TanqueCeleste::avanzarCaminoPaso() {
    if (indiceCamino < longitudCamino) {
        nodoActual = camino[indiceCamino];  // Mover al siguiente nodo en el camino
        indiceCamino++;
    }
}
