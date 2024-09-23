#ifndef TANQUE_H
#define TANQUE_H

#include <string>

enum class ColorTanque {
    Azul,
    Celeste,
    Amarillo,
    Rojo
};

class Tanque {
public:
    Tanque(ColorTanque color);

    ColorTanque obtenerColor() const;
    std::string obtenerDescripcion() const;

    // Métodos específicos para cada tipo de tanque
    virtual void atacar() const;
    virtual void defender() const;

    // Métodos comunes
    void mover(int x, int y);

protected:
    ColorTanque color;
    int posX;
    int posY;

    // Métodos específicos a implementar en clases derivadas
    virtual void comportamientoEspecial() const = 0;

private:
    std::string obtenerColorComoString() const;
};

#endif // TANQUE_H
