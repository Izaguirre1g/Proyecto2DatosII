#ifndef TANQUEAMARILLO_H
#define TANQUEAMARILLO_H

#include "Tanque.h"

class TanqueAmarillo : public Tanque {
public:
    TanqueAmarillo(Grafo* grafo, int nodoInicial);

    void mover() override;
};

#endif // TANQUEAMARILLO_H
