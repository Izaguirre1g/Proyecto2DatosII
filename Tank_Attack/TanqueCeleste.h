// TanqueCeleste.h
#ifndef TANQUECELESTE_H
#define TANQUECELESTE_H

#include "Tanque.h"
#include "Grafo.h"

class TanqueCeleste : public Tanque {
public:
    TanqueCeleste(Grafo& grafo);

//protected:
    void comportamientoEspecial() const override;

private:
    void moverConBFS() const; // Marcar como const si no modifica el estado
    void moverAleatoriamente() const; // Marcar como const si no modifica el estado

    Grafo& grafo;
};

#endif // TANQUECELESTE_H
