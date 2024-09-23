#include "TanqueAzul.h"
#include "BFS.h" // Asegúrate de incluir la declaración de bfs
#include <cstdlib>
#include <ctime>

TanqueAzul::TanqueAzul(Grafo& grafo)
    : Tanque(ColorTanque::Azul, grafo) {}

void TanqueAzul::comportamientoEspecial() const {
    if (std::rand() % 2 == 0) {
        moverConBFS();
    } else {
        moverAleatoriamente();
    }
}

void TanqueAzul::moverConBFS() const {
    bfs(grafo, posX, posY); // Asegúrate de que posX y posY sean accesibles
}

void TanqueAzul::moverAleatoriamente() const {
    // Implementa la lógica de movimiento aleatorio aquí
}
