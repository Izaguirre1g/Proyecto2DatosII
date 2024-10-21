#include "Bala.h"
#include "Grafo.h"
#include <iostream>
#include <cmath>

// Constructor
Bala::Bala(int xInicial, int yInicial, int xObjetivo, int yObjetivo, int camino[], int longitud)
    : x(xInicial), y(yInicial), xObjetivo(xObjetivo), yObjetivo(yObjetivo), activa(true), longitudCamino(longitud), indiceCamino(0) {
    // Copiar el camino
    this->camino = new int[longitud];
    for (int i = 0; i < longitud; ++i) {
        this->camino[i] = camino[i];
    }
}

// Destructor para liberar la memoria del camino
Bala::~Bala() {
    if (camino) {
        delete[] camino;
        camino = nullptr;
    }
}

// Mueve la bala de su posición actual hacia el nodo siguiente
void Bala::mover() {
    if (indiceCamino < longitudCamino) {
        int nodoSiguiente = camino[indiceCamino];
        // Aquí se asume que el `grafo` se pasa en la función de avanzar, y se calculan x, y del nodo
        // Lo moveremos en `avanzarCaminoPaso`
    }
}

// Avanza la bala al siguiente nodo en el camino
void Bala::avanzarCaminoPaso(Grafo* grafo) {
    if (indiceCamino < longitudCamino - 1) {
        int nodoSiguiente = camino[indiceCamino + 1];

        // Obtener las coordenadas del nodo siguiente
        int xSiguiente = grafo->getPosicionX(nodoSiguiente);
        int ySiguiente = grafo->getPosicionY(nodoSiguiente);

        // Calcular el movimiento en dirección al siguiente nodo
        int dx = xSiguiente - x;
        int dy = ySiguiente - y;
        float dist = std::sqrt(dx * dx + dy * dy);

        // Avance con un paso fijo, proporcional a la distancia
        const float speed = 9.0;  // Ajustar este valor para controlar la velocidad de la bala
        if (dist > speed) {  // Si está lejos, mover hacia el nodo
            // Mover la bala en la dirección del siguiente nodo
            x += (dx / dist) * speed;
            y += (dy / dist) * speed;
        } else {
            // Si la bala está lo suficientemente cerca, saltar al siguiente nodo
            x = xSiguiente;
            y = ySiguiente;
            indiceCamino++;  // Avanzar en el camino
        }

        // Si la bala ha alcanzado el último nodo, marcarla como inactiva
        if (indiceCamino >= longitudCamino - 1) {
            activa = false;
        }
    }
}



// Verificar si la bala ha llegado al final del camino
bool Bala::haTerminadoCamino() {
    return indiceCamino >= longitudCamino-1;
}

// Getter para la posición X actual
int Bala::getX() const {
    return x;
}

// Getter para la posición Y actual
int Bala::getY() const {
    return y;
}

// Obtener el índice actual en el camino
int Bala::getIndiceActual() const {
    return indiceCamino;
}

// Obtener la longitud total del camino
int Bala::getLongitudCamino() const {
    return longitudCamino;
}

// Obtener el array del camino de la bala
int* Bala::getCamino() {
    return camino;
}

// Getter para el estado de la bala (activa o inactiva)
bool Bala::estaActiva() const {
    return activa;
}

// Setter para el estado de la bala
void Bala::setActiva(bool estado) {
    activa = estado;
}

bool Bala::verificarColisionConTanque(int xTanque, int yTanque, float radioColision) {
    // Calcular la distancia entre la posición de la bala y el tanque
    int dx = xTanque - x;
    int dy = yTanque - y;
    float distancia = std::sqrt(dx * dx + dy * dy);

    // Verificar si la distancia es menor al radio de colisión
    return distancia <= radioColision;
}



