#include "Bala.h"
#include <cmath>  // Para calcular la dirección

Bala::Bala(int xInicial, int yInicial, int xDestino, int yDestino)
    : x(xInicial), y(yInicial), activa(true) {

    // Calcular la dirección de la bala
    float dx = xDestino - xInicial;
    float dy = yDestino - yInicial;
    float magnitud = std::sqrt(dx * dx + dy * dy);

    if (magnitud != 0) {
        velocidadX = dx / magnitud * 10;  // Ajustar 10 para la velocidad deseada
        velocidadY = dy / magnitud * 10;
    } else {
        velocidadX = 0;
        velocidadY = 0;
    }
}

void Bala::mover() {
    if (!activa) return;

    x += velocidadX;
    y += velocidadY;

    // Aquí puedes agregar la lógica para desactivar la bala si sale del área de juego
}

int Bala::getX() const {
    return x;
}

int Bala::getY() const {
    return y;
}

bool Bala::estaActiva() const {
    return activa;
}

void Bala::desactivar() {
    activa = false;
}

