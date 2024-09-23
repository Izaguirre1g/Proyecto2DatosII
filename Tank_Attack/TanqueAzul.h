// TanqueAzul.h
#ifndef TANQUEAZUL_H
#define TANQUEAZUL_H

#include "Tanque.h"
#include "Grafo.h"

class TanqueAzul : public Tanque {
public:
    TanqueAzul(Grafo& grafo);

protected:
    void comportamientoEspecial() const override;

private:
    void moverConBFS() const; // Marcar como const si no modifica el estado
    void moverAleatoriamente() const; // Marcar como const si no modifica el estado

    //Grafo& grafo;
};

#endif // TANQUEAZUL_H
