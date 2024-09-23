#include "TanqueAzul.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

TanqueAzul::TanqueAzul() : Tanque(ColorTanque::Azul) {
    //Inicializar la semilla para generación de números aleatorios
    std::srand(std::time(nullptr));
}

void TanqueAzul::comportamientoEspecial() const {
    //Elegir entre BFS y movimiento aleatorio
    if (std::rand() % 2 == 0) {
        //moverConBFS();
    } else {
        //moverAleatoriamente();
    }
}

void TanqueAzul::moverConBFS() {
    std::cout << "El tanque azul se mueve usando BFS." << std::endl;
    // Aquí va la lógica de BFS
}

void TanqueAzul::moverAleatoriamente() {
    std::cout << "El tanque azul se mueve aleatoriamente." << std::endl;
    // Aquí va la lógica del movimiento aleatorio
}
