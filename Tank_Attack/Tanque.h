#ifndef TANQUE_H
#define TANQUE_H

class Grafo; // Forward declaration

class Tanque {
public:
    Tanque(Grafo* grafo, int nodoInicial);

    int obtenerNodoActual() const;
    void setNodoObjetivo(int nodoObjetivo);

    // Métodos para obtener el camino y su longitud
    int* getCamino() const;
    int getLongitudCamino() const;
    void limpiarCamino();
protected:
    Grafo* grafo;
    int nodoActual;
    int nodoObjetivo;
    int* camino;  // Arreglo para almacenar el camino
    int longitudCamino;  // Longitud del camino
    int indiceCamino;
};

#endif // TANQUE_H
