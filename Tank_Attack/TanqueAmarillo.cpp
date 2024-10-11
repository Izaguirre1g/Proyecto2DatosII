#include "TanqueAmarillo.h"
#include "Dijkstra.h"
#include <cstdlib>  // Para rand()

TanqueAmarillo::TanqueAmarillo(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {}

void TanqueAmarillo::mover() {
    if (rand() % 5 < 4) {  // 80% de probabilidad de usar Dijkstra
        std::cout << "Movimiento mediante Dijkstra de amarillo" << std::endl;
        if (nodoObjetivo != -1) {
            // Verificar si el nodo objetivo está bloqueado antes de realizar el movimiento
            if (grafo->nodosBloqueados[nodoObjetivo]) {
                std::cerr << "El nodo objetivo está bloqueado por un obstáculo. No se puede mover el tanque amarillo." << std::endl;
                return;
            }
            camino = new int[grafo->obtenerNumNodos()];
            longitudCamino = 0;
            dijkstra(*grafo, nodoActual, nodoObjetivo, camino, longitudCamino);
            indiceCamino = 0;  // Reiniciar el índice del camino
        }
    } else {
        std::cout << "Movimiento aleatorio de amarillo" << std::endl;
        nodoActual = rand() % grafo->obtenerNumNodos();  // Movimiento aleatorio
        camino = nullptr;  // No hay camino en el movimiento aleatorio
        longitudCamino = 0;
    }
}

bool TanqueAmarillo::haTerminadoCamino() {
    return indiceCamino >= longitudCamino;
}

void TanqueAmarillo::avanzarCaminoPaso() {
    if (indiceCamino < longitudCamino) {
        nodoActual = camino[indiceCamino];  // Mover al siguiente nodo en el camino
        indiceCamino++;
    }
}

int TanqueAmarillo::getNodoSiguiente() {
    if (indiceCamino < longitudCamino) {
        return camino[indiceCamino];  // Devolver el siguiente nodo en el camino
    }
    return -1;  // No hay más nodos en el camino
}
