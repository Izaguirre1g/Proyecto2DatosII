#ifndef BALA_H
#define BALA_H

class Bala {
public:
    Bala(int xInicial, int yInicial, int xDestino, int yDestino);

    void mover();      // Mueve la bala en la dirección calculada
    int getX() const;  // Obtener la posición actual en X
    int getY() const;  // Obtener la posición actual en Y
    bool estaActiva() const;  // Saber si la bala está activa (en pantalla)
    void desactivar(); // Desactiva la bala cuando alcanza su destino o sale del área

private:
    int x, y;        // Posición de la bala
    float velocidadX, velocidadY;  // Velocidades en las direcciones X e Y
    bool activa;     // Estado de la bala (activa/inactiva)
};

#endif // BALA_H
