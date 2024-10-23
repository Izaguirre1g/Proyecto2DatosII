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

// Mueve la bala de su posición actual hacia el nodo siguiente
void Bala::avanzarCaminoPaso(Grafo* grafo) {
    const int maxRebotes = 50;  // Número máximo de rebotes permitidos
    float velocidadNormal = 8.5;  // Velocidad inicial
    float velocidadReduccion = 0.1;  // Velocidad después de un rebote
    float velocidadActual = velocidadNormal;  // Inicializamos con la velocidad normal

    // Definir los límites del grafo
    const int xMin = 0, yMin = 0;
    const int xMax = 1050, yMax = 720;  // Límites del área del grafo

    // Verificar si la bala está fuera de los límites del grafo
    if (x < xMin || x > xMax || y < yMin || y > yMax) {
        std::cout << "Bala fuera de los límites del grafo. Rebote en la pared." << std::endl;
        activa = false;
        return;
    }

    // Si ha rebotado demasiadas veces, detener la bala
    if (contadorRebotes >= maxRebotes) {
        std::cout << "Bala ha rebotado demasiadas veces. Deteniendo bala." << std::endl;
        activa = false;
        return;
    }

    // Verificar colisiones con los límites del grafo (paredes)
    if (x <= xMin || x >= xMax) {
        // Rebote en el eje X (paredes laterales)
        std::cout << "Bala ha rebotado en la pared vertical (x)." << std::endl;
        x = (x <= xMin) ? xMin + 1 : xMax - 1;  // Ajustar la posición para evitar que se salga
        contadorRebotes++;  // Incrementar el contador de rebotes
        velocidadActual = velocidadReduccion;  // Reducir la velocidad tras el rebote
    }

    if (y <= yMin || y >= yMax) {
        // Rebote en el eje Y (paredes superior e inferior)
        std::cout << "Bala ha rebotado en la pared horizontal (y)." << std::endl;
        y = (y <= yMin) ? yMin + 1 : yMax - 1;  // Ajustar la posición para evitar que se salga
        contadorRebotes++;  // Incrementar el contador de rebotes
        velocidadActual = velocidadReduccion;  // Reducir la velocidad tras el rebote
    }

    // Movimiento normal si no hay colisión con paredes ni obstáculos
    if (indiceCamino < longitudCamino - 1) {
        int nodoSiguiente = camino[indiceCamino + 1];

        // Verificar si el nodo siguiente es un obstáculo
        if (grafo->esNodoBloqueado(nodoSiguiente)) {
            std::cout << "¡Colisión con obstáculo detectada en el nodo: " << nodoSiguiente << "!" << std::endl;

            // Reducir la velocidad tras la colisión con un obstáculo
            velocidadActual = velocidadReduccion;

            // Alejar la bala del obstáculo
            int xActual = grafo->getPosicionX(camino[indiceCamino]);
            int yActual = grafo->getPosicionY(camino[indiceCamino]);
            int xSiguiente = grafo->getPosicionX(nodoSiguiente);
            int ySiguiente = grafo->getPosicionY(nodoSiguiente);

            // Vector incidente (dirección de la bala)
            int dx = xSiguiente - xActual;
            int dy = ySiguiente - yActual;

            // Alejar un poco la bala para evitar colisiones repetidas
            const int distanciaRebote = 30;

            if (dx != 0) {
                x += (dx > 0) ? -distanciaRebote : distanciaRebote;
            }
            if (dy != 0) {
                y += (dy > 0) ? -distanciaRebote : distanciaRebote;
            }

            contadorRebotes++;  // Incrementar el contador de rebotes para esta bala
            return;  // Evitar que la bala continúe moviéndose en este ciclo
        } else {
            // Restablecer la velocidad cuando no hay colisión
            velocidadActual = velocidadNormal;
        }

        // Movimiento normal si no hay colisión con obstáculos
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
