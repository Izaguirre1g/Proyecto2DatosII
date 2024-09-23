#include "TanqueCeleste.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

TanqueCeleste::TanqueCeleste() : Tanque(ColorTanque::Celeste) {
    //Inicializar la semilla para generación de números aleatorios
    std::srand(std::time(nullptr));
}

void TanqueCeleste::comportamientoEspecial() const {
    //Elegir entre BFS y movimiento aleatorio
    if (std::rand() % 2 == 0) {
        moverConBFS();
    } else {
        moverAleatoriamente();
    }
}

void TanqueCeleste::moverConBFS() {
    std::cout << "El tanque celeste se mueve usando BFS." << std::endl;
    //Aquí va la lógica de BFS
}

void TanqueCeleste::moverAleatoriamente() {
    std::cout << "El tanque celeste se mueve aleatoriamente." << std::endl;
    // Aquí va la lógico del movimiento aleatorio
}
