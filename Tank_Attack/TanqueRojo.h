#ifndef TANQUEROJO_H
#define TANQUEROJO_H

#include "Tanque.h"

class TanqueRojo : public Tanque {
public:
    TanqueRojo(Grafo& grafo);

protected:
    void comportamientoEspecial() const override;
    void moverConDijkstra();
    void moverAleatoriamente();
};

#endif //TANQUEROJO_H
