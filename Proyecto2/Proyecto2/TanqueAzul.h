#ifndef TANQUEAZUL_H
#define TANQUEAZUL_H

#include "Tanque.h"

class TanqueAzul : public Tanque {
public:
    TanqueAzul();

protected:
    void comportamientoEspecial() const override;
    void moverConBFS();
    void moverAleatoriamente();
};

#endif //TANQUEAZUL_H
