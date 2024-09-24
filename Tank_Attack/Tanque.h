#ifndef TANQUE_H
#define TANQUE_H

#include "Grafo.h"

class Tanque {
protected:
    Grafo* grafo;
    int nodoActual;
    int nodoObjetivo; // Nodo al que el tanque debe moverse

public:
    Tanque(Grafo* grafo, int nodoInicial);

    virtual void mover() = 0; // Método virtual puro

    int obtenerNodoActual() const;
    void setNodoObjetivo(int nodoObjetivo); // Método para establecer el nodo objetivo
};

#endif // TANQUE_H
