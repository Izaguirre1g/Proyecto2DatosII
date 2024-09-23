#include "TanqueAmarillo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

TanqueAmarillo::TanqueAmarillo() : Tanque(ColorTanque::Amarillo) {
    std::srand(std::time(nullptr)); //Inicializar semilla para generación aleatoria
}

void TanqueAmarillo::comportamientoEspecial() const {
    //80% probabilidad para Dijkstra, 20% para movimiento aleatorio
    if (std::rand() % 100 < 80) {
        //moverConDijkstra();
    } else {
        //moverAleatoriamente();
    }
}

void TanqueAmarillo::moverConDijkstra() {
    std::cout << "El tanque amarillo se mueve usando Dijkstra." << std::endl;
    //Implementación del algoritmo Dijkstra aquí
}

void TanqueAmarillo::moverAleatoriamente() {
    std::cout << "El tanque amarillo se mueve aleatoriamente." << std::endl;
    //Implementación del movimiento aleatorio aquí
}
