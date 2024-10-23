#ifndef TANQUE_AZUL_H
#define TANQUE_AZUL_H

#include "Tanque.h"
#include <QObject>  // Para QObject y las señales/slots de Qt

class TanqueAzul : public QObject, public Tanque {
    Q_OBJECT

public:
    TanqueAzul(Grafo* grafo, int nodoInicial);

    void mover();
    bool haTerminadoCamino();          // Método para verificar si ha terminado el camino
    void avanzarCaminoPaso();
    int getNodoSiguiente();            // Método para obtener el siguiente nodo en el camino

signals:
    void actualizarInterfaz();  // Señal para actualizar la interfaz gráfica

private:
    int indiceCamino;         // Índice del camino para moverse paso a paso
    int obtenerPosicionAleatoriaEnRadio(int radio);
    bool avanzarLoMasLejosPosibleConLineaVista();  // Usar línea de vista para avanzar lo más lejos posible
    bool detectarColision(int siguienteNodo);  // Método para detectar colisiones
    void finalizarMovimientoYTurno();
    void continuarMovimiento();
    void moverAleatoriamenteConValidacion();
};

#endif
