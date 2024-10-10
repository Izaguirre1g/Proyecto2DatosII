#include "TanqueAzul.h"
#include "BFS.h"
#include <cstdlib>  // Para rand()

TanqueAzul::TanqueAzul(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {}

void TanqueAzul::mover() {
    if (rand() % 2 == 0) {  // 50% de probabilidad de moverse aleatoriamente
        std::cout << "Movimiento aleatorio de azul" << std::endl;
        nodoActual = rand() % grafo->obtenerNumNodos();
        camino = nullptr;
        longitudCamino = 0;
    } else {
        std::cout << "Movimiento mediante BFS de azul" << std::endl;
        if (nodoObjetivo != -1) {
            // Verificar si el nodo objetivo está bloqueado antes de realizar el movimiento
            if (grafo->nodosBloqueados[nodoObjetivo]) {
                std::cerr << "El nodo objetivo está bloqueado por un obstáculo. No se puede mover el tanque azul." << std::endl;
                return;
            }
            camino = new int[grafo->obtenerNumNodos()];
            longitudCamino = 0;
            bfs(*grafo, nodoActual, nodoObjetivo, camino, longitudCamino);
            indiceCamino = 0;
        }
    }
}

bool TanqueAzul::haTerminadoCamino() {
    return indiceCamino >= longitudCamino;
}

void TanqueAzul::avanzarCaminoPaso() {
    if (indiceCamino < longitudCamino) {
        nodoActual = camino[indiceCamino];
        indiceCamino++;
    }
}
