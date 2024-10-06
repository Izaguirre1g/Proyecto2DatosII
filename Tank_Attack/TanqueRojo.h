#ifndef TANQUEROJO_H
#define TANQUEROJO_H

#include "Tanque.h"

class TanqueRojo : public Tanque {
public:
    TanqueRojo(Grafo* grafo, int nodoInicial);
    void mover() ;
};

#endif // TANQUEROJO_H
