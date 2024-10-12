#ifndef BALA_H
#define BALA_H

class Bala {
public:
    Bala(int xInicial, int yInicial, int xObjetivo, int yObjetivo);

    void mover();
    bool estaActiva() const;
    int getX() const;
    int getY() const;

private:
    int x, y;         // Posición actual de la bala
    int xObjetivo, yObjetivo;  // Posición objetivo
    bool activa;      // Si la bala sigue activa (volando)
};

#endif // BALA_H
