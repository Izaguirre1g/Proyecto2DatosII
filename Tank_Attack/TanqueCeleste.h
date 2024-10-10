#ifndef TANQUE_CELESTE_H
#define TANQUE_CELESTE_H

#include "Tanque.h"

class TanqueCeleste : public Tanque {
public:
    TanqueCeleste(Grafo* grafo, int nodoInicial);

    void mover();
    bool haTerminadoCamino();          // Método para verificar si ha terminado el camino
    void avanzarCaminoPaso();
private:
    int indiceCamino;         // Método para avanzar un paso en el camino
};

#endif
