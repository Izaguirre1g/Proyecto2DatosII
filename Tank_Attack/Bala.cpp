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
    const int maxRebotes = 50;
    float velocidadNormal = 8.5;
    float velocidadReduccion = 0.1;
    float velocidadActual = velocidadNormal;

    const int xMin = 0, yMin = 0;
    const int xMax = 1050, yMax = 720;

    if (x < xMin || x > xMax || y < yMin || y > yMax) {
        std::cout << "Bala fuera de los límites del grafo. Deteniendo la bala." << std::endl;
        activa = false;
        return;
    }

    if (indiceCamino < longitudCamino - 1) {
        int nodoSiguiente = camino[indiceCamino + 1];

        // Rebote en obstáculos
        if (grafo->esNodoBloqueado(nodoSiguiente)) {
            std::cout << "¡Colisión con obstáculo detectada!" << std::endl;
            velocidadActual = velocidadReduccion;

            int dx = grafo->getPosicionX(nodoSiguiente) - x;
            int dy = grafo->getPosicionY(nodoSiguiente) - y;
            const int distanciaRebote = 30;

            if (dx != 0) x += (dx > 0 ? -distanciaRebote : distanciaRebote);
            if (dy != 0) y += (dy > 0 ? -distanciaRebote : distanciaRebote);

            contadorRebotes++;
            return;
        } else {
            velocidadActual = velocidadNormal;
        }

        int xSiguiente = grafo->getPosicionX(nodoSiguiente);
        int ySiguiente = grafo->getPosicionY(nodoSiguiente);

        int dx = xSiguiente - x;
        int dy = ySiguiente - y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist > velocidadActual) {
            x += (dx / dist) * velocidadActual;
            y += (dy / dist) * velocidadActual;
        } else {
            x = xSiguiente;
            y = ySiguiente;
            indiceCamino++;
        }

        if (indiceCamino >= longitudCamino - 1) activa = false;
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
