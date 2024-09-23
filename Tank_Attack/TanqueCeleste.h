#ifndef TANQUECELESTE_H
#define TANQUECELESTE_H

#include "Tanque.h"

class TanqueCeleste : public Tanque {
public:
    TanqueCeleste();

protected:
    void comportamientoEspecial() const override;
    void moverConBFS();
    void moverAleatoriamente();
};

#endif //TANQUECELESTE_H
