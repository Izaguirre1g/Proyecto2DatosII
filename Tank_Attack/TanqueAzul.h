#ifndef TANQUEAZUL_H
#define TANQUEAZUL_H

#include "Tanque.h"

class TanqueAzul : public Tanque {
public:
    TanqueAzul(Grafo* grafo, int nodoInicial);

    void mover() override;
};

#endif // TANQUEAZUL_H
