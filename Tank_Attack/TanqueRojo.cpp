#include "TanqueRojo.h"
#include "Dijkstra.h"
#include <cstdlib> // Para rand()

TanqueRojo::TanqueRojo(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {}

void TanqueRojo::mover() {
    if (rand() % 5 < 4) {  // 80% de probabilidad de moverse mediante Dijkstra
        std::cout << "Movimiento mediante Dijkstra de rojo" << std::endl;
        if (nodoObjetivo != -1) {
            camino = new int[grafo->obtenerNumNodos()];
            longitudCamino = 0;
            dijkstra(*grafo, nodoActual, nodoObjetivo, camino, longitudCamino);
            indiceCamino = 0;  // Reiniciar el índice del camino
        }
    } else {  // 20% de probabilidad de moverse aleatoriamente
        std::cout << "Movimiento aleatorio de rojo" << std::endl;
        nodoActual = rand() % grafo->obtenerNumNodos();
        camino = nullptr;
        longitudCamino = 0;
    }
}

bool TanqueRojo::haTerminadoCamino() {
    return indiceCamino >= longitudCamino;
}

void TanqueRojo::avanzarCaminoPaso() {
    if (indiceCamino < longitudCamino) {
        nodoActual = camino[indiceCamino];  // Mover al siguiente nodo en el camino
        indiceCamino++;
    }
}

