#include "Tanque.h"
#include <iostream>

Tanque::Tanque(ColorTanque color) : color(color), posX(0), posY(0) {}

ColorTanque Tanque::obtenerColor() const {
    return color;
}

std::string Tanque::obtenerDescripcion() const {
    return "Tanque de color " + obtenerColorComoString();
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
    std::cout << "Tanque movido a (" << posX << ", " << posY << ")." << std::endl;
}

std::string Tanque::obtenerColorComoString() const {
    switch (color) {
    case ColorTanque::Azul: return "Azul";
    case ColorTanque::Celeste: return "Celeste";
    case ColorTanque::Amarillo: return "Amarillo";
    case ColorTanque::Rojo: return "Rojo";
    default: return "Desconocido";
    }
}
