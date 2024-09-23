#include "TanqueRojo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
TanqueRojo::TanqueRojo() : Tanque(ColorTanque::Rojo) {
    std::srand(std::time(nullptr)); //Inicializar semilla para generación aleatoria
}

void TanqueRojo::comportamientoEspecial() const {
    //80% probabilidad para Dijkstra, 20% para movimiento aleatorio
    if (std::rand() % 100 < 80) {
        //moverConDijkstra();
    } else {
        //moverAleatoriamente();
    }
}

void TanqueRojo::moverConDijkstra() {
    std::cout << "El tanque rojo se mueve usando Dijkstra." << std::endl;
    //Implementación del algoritmo Dijkstra aquí
}

void TanqueRojo::moverAleatoriamente() {
    std::cout << "El tanque rojo se mueve aleatoriamente." << std::endl;
    //Implementación del movimiento aleatorio aquí
}
