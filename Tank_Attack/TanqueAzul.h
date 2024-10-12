#ifndef TANQUE_AZUL_H
#define TANQUE_AZUL_H

#include "Tanque.h"

class TanqueAzul : public Tanque {
public:
    TanqueAzul(Grafo* grafo, int nodoInicial);

    void mover();
    bool haTerminadoCamino();
    void avanzarCaminoPaso();
    int getNodoSiguiente();  // Método para obtener el siguiente nodo en el camino

private:
    int indiceCamino;
};

#endif
