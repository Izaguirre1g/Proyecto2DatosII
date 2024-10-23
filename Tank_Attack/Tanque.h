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
    void reducirVida(int cantidad);
    bool validaExistenciaTanque(int resultado_existenciaTanque);

    // Método para obtener la vida restante
    int obtenerVida() const {
        return vida;
    }

    bool estaVivo() const {
        return vida > 0;
    }


protected:
    Grafo* grafo;
    int nodoActual;
    int nodoObjetivo;
    int* camino;  // Arreglo para almacenar el camino
    int longitudCamino;  // Longitud del camino
    int indiceCamino;
    int vida;
};

#endif // TANQUE_H
