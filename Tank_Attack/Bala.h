#ifndef BALA_H
#define BALA_H

class Grafo;  // Forward declaration de Grafo

class Bala {
private:
    int x, y;  // Posición actual de la bala
    int xObjetivo, yObjetivo;  // Objetivo final de la bala
    int* camino;  // Camino de nodos por los que pasa la bala
    int longitudCamino;  // Cantidad de nodos en el camino
    int indiceCamino;  // Índice del nodo actual en el camino
    bool activa;  // Indica si la bala está en movimiento

public:
    Bala(int xInicial, int yInicial, int xObjetivo, int yObjetivo, int camino[], int longitud);
    ~Bala();  // Destructor para liberar memoria

    void mover();  // Mueve la bala
    void avanzarCaminoPaso(Grafo* grafo);  // Avanza al siguiente nodo
    bool haTerminadoCamino();  // Verifica si la bala ha llegado al final del camino
    void limpiarCamino();  // Limpia el camino de la bala

    int getX() const;
    int getY() const;
    int getIndiceActual() const;
    int getLongitudCamino() const;
    int* getCamino();

    bool estaActiva() const;
    void setActiva(bool estado);
};

#endif
