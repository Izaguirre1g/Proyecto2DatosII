#ifndef TANQUE_AZUL_H
#define TANQUE_AZUL_H

#include "Tanque.h"

class TanqueAzul : public Tanque {
public:
    TanqueAzul(Grafo* grafo, int nodoInicial);

    void mover();
    bool haTerminadoCamino();
    void avanzarCaminoPaso();
private:
    int indiceCamino;
};

#endif
