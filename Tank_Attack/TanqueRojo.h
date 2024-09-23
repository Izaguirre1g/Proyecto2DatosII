#ifndef TANQUEROJO_H
#define TANQUEROJO_H

#include "Tanque.h"

class TanqueRojo : public Tanque {
public:
    TanqueRojo();

protected:
    void comportamientoEspecial() const override;
    void moverConDijkstra();
    void moverAleatoriamente();
};

#endif //TANQUEROJO_H
