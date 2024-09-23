// TanqueCeleste.cpp
#include "TanqueCeleste.h"
#include "BFS.h" // Asegúrate de incluir la declaración de bfs

TanqueCeleste::TanqueCeleste(Grafo& grafo)
    : Tanque(ColorTanque::Celeste, grafo), grafo(grafo) {}

void TanqueCeleste::comportamientoEspecial() const {
    if (std::rand() % 2 == 0) {
        moverConBFS();
    } else {
        moverAleatoriamente();
    }
}

void TanqueCeleste::moverConBFS() const {
    bfs(grafo, posX, posY); // Asegúrate de que posX y posY sean accesibles
}

void TanqueCeleste::moverAleatoriamente() const {
    // Implementa la lógica de movimiento aleatorio aquí
}
