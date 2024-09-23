#ifndef TANQUE_H
#define TANQUE_H

#include <string>
#include "Grafo.h"
#include <vector> // Para manejar la lista de nodos adyacentes

enum class ColorTanque {
    Azul,
    Celeste,
    Amarillo,
    Rojo
};

class Tanque {
public:
    Tanque(ColorTanque color, Grafo& grafo);

    ColorTanque obtenerColor() const;
    std::string obtenerDescripcion() const;

    // Métodos específicos para cada tipo de tanque
    virtual void atacar() const;
    virtual void defender() const;

    // Métodos comunes
    void mover(int x, int y);

    // Método para movimiento aleatorio
    void moverAleatorio();

    // Coordenadas del tanque
    int obtenerPosX() const { return posX; }
    int obtenerPosY() const { return posY; }

    // Métodos para obtener el grafo y la posición actual
    Grafo& obtenerGrafo() { return grafo; }
    int obtenerPosicionActual() const;

protected:
    ColorTanque color;
    int posX;
    int posY;
    Grafo& grafo;  // Referencia al grafo

    // Métodos específicos a implementar en clases derivadas
    virtual void comportamientoEspecial() const = 0;

private:
    std::string obtenerColorComoString() const;
};

#endif // TANQUE_H
