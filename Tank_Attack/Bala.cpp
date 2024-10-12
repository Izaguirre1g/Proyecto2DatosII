#include "Bala.h"
#include <cmath>

Bala::Bala(int xInicial, int yInicial, int xObjetivo, int yObjetivo)
    : x(xInicial), y(yInicial), xObjetivo(xObjetivo), yObjetivo(yObjetivo), activa(true) {}

void Bala::mover() {
    // Lógica simple para mover la bala hacia su objetivo (puedes hacerla más realista)
    int dx = xObjetivo - x;
    int dy = yObjetivo - y;
    int dist = std::sqrt(dx * dx + dy * dy);

    if (dist < 5) {
        activa = false;  // La bala alcanzó el objetivo o está muy cerca
    } else {
        x += dx / 10;  // Mover en dirección al objetivo
        y += dy / 10;
    }
}

bool Bala::estaActiva() const {
    return activa;
}

int Bala::getX() const {
    return x;
}

int Bala::getY() const {
    return y;
}

