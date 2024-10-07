#ifndef TANQUE_ROJO_H
#define TANQUE_ROJO_H

#include "Tanque.h"

class TanqueRojo : public Tanque {
public:
    TanqueRojo(Grafo* grafo, int nodoInicial);

    void mover();
    bool haTerminadoCamino();          // Método para verificar si ha terminado el camino
    void avanzarCaminoPaso();
private:
    int indiceCamino;         // Método para avanzar un paso en el camino
};

#endif
