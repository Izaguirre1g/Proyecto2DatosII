#ifndef TANQUECELESTE_H
#define TANQUECELESTE_H

#include "Tanque.h"

class TanqueCeleste : public Tanque {
public:
    TanqueCeleste(Grafo* grafo, int nodoInicial);

    void mover();// override;
};

#endif // TANQUECELESTE_H
