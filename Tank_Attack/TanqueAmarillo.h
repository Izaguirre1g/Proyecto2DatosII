#ifndef TANQUE_AMARILLO_H
#define TANQUE_AMARILLO_H

#include "Tanque.h"

class TanqueAmarillo : public Tanque {
public:
    TanqueAmarillo(Grafo* grafo, int nodoInicial);

    void mover();
    bool haTerminadoCamino();          // Método para verificar si ha terminado el camino
    void avanzarCaminoPaso();          // Método para avanzar un paso en el camino
    int getNodoSiguiente();            // Método para obtener el siguiente nodo en el camino

private:
    int indiceCamino;  // Variable para hacer seguimiento del progreso en el camino
};

#endif
