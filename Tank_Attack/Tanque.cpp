// Tanque.cpp
#include "Tanque.h"
#include <cmath> // Para la función std::sqrt

// Constructor
Tanque::Tanque(ColorTanque color, Grafo& grafo)
    : color(color), grafo(grafo), posX(0), posY(0) {}

// Obtener el color como string
std::string Tanque::obtenerColorComoString() const {
    switch (color) {
    case ColorTanque::Azul: return "Azul";
    case ColorTanque::Celeste: return "Celeste";
    case ColorTanque::Amarillo: return "Amarillo";
    case ColorTanque::Rojo: return "Rojo";
    default: return "Desconocido";
    }
}

ColorTanque Tanque::obtenerColor() const {
    return color;
}

std::string Tanque::obtenerDescripcion() const {
    return "Tanque " + obtenerColorComoString();
}

void Tanque::atacar() const {
    std::cout << "El tanque está atacando." << std::endl;
}

void Tanque::defender() const {
    std::cout << "El tanque está defendiendo." << std::endl;
}

void Tanque::mover(int x, int y) {
    posX = x;
    posY = y;
}

void Tanque::moverAleatorio() {
    std::cout << "El tanque se mueve aleatoriamente." << std::endl;
    // Implementar la lógica de movimiento aleatorio
}

int Tanque::obtenerPosicionActual() const {
    // Encuentra el nodo más cercano a la posición actual del tanque
    int numNodos = grafo.obtenerNumNodos();
    int nodoCercano = 0;
    double menorDistancia = std::numeric_limits<double>::max(); // Inicializa con infinito

    for (int i = 0; i < numNodos; ++i) {
        int xNodo = grafo.obtenerPosX(i);
        int yNodo = grafo.obtenerPosY(i);
        double distancia = std::sqrt(std::pow(xNodo - posX, 2) + std::pow(yNodo - posY, 2));

        if (distancia < menorDistancia) {
            menorDistancia = distancia;
            nodoCercano = i;
        }
    }

    return nodoCercano;
}
