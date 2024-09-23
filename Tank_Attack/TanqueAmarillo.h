#ifndef TANQUEAMARILLO_H
#define TANQUEAMARILLO_H

#include "Tanque.h"

class TanqueAmarillo : public Tanque {
public:
    TanqueAmarillo(Grafo& grafo);

protected:
    void comportamientoEspecial() const override;
    void moverConDijkstra();
    void moverAleatoriamente();
};

#endif //TANQUEAMARILLO_H
