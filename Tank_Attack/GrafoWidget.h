#ifndef GRAFOWIDGET_H
#define GRAFOWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include "Grafo.h"
#include "TanqueAmarillo.h"
#include "TanqueAzul.h"
#include "TanqueCeleste.h"
#include "TanqueRojo.h"
#include "Bala.h"  // Incluir la clase Bala

class GrafoWidget : public QWidget {
    Q_OBJECT

public:
    explicit GrafoWidget(QWidget *parent = nullptr);
    void setGrafo(Grafo* grafo);
    void setTanques(TanqueAmarillo* amarillo1, TanqueAmarillo* amarillo2, TanqueAzul* azul1, TanqueAzul* azul2,
                    TanqueCeleste* celeste1, TanqueCeleste* celeste2, TanqueRojo* rojo1, TanqueRojo* rojo2);
    int calcularCamino(int xInicial, int yInicial, int xObjetivo, int yObjetivo, int camino[]);
    void DobleTurno(int jugadorTurnoClick);
    Tanque* obtenerTanqueActual();  // Método que devuelve el tanque en turno

    bool listasSonIguales(int* lista1, int* lista2, int size);
    //Funcion auxiliar
    bool existeEnArreglo(int arr[], int size, int valor);
    // Declaración de la función tipoPowersUp
    int* tipoPowersUp();  // Asegúrate de que está declarada aquí si pertenece a esta clase


    void startTurn();
    void consumeAction();

    int* obtenerCaminoAEstrella(int nodoInicial, int nodoFinal, int& longitudCamino);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void moverTanquePasoAPaso();
    void moverBala();  // Mover la bala cada vez que el temporizador lo indique

private:
    Grafo* grafo;
    TanqueAmarillo* tanqueAmarillo1;
    TanqueAmarillo* tanqueAmarillo2;
    TanqueAzul* tanqueAzul1;
    TanqueAzul* tanqueAzul2;
    TanqueCeleste* tanqueCeleste1;
    TanqueCeleste* tanqueCeleste2;
    TanqueRojo* tanqueRojo1;
    TanqueRojo* tanqueRojo2;
    QString textoCambiante1;
    QString textoCambiante2;
    QTimer* movimientoTimer;
    QTimer* balaTimer;  // Temporizador para manejar el movimiento de las balas



    int powerUpPendienteJugador1 = 0;
    int powerUpPendienteJugador2 = 0;
    bool turnoDobleActivo = false; // Indica si el doble turno está activo en el turno actual
    bool dobleTurnoPendienteJugador1 = false;  // Estado de doble turno pendiente para Jugador 1
    bool dobleTurnoPendienteJugador2 = false;  // Estado de doble turno pendiente para Jugador 2


    bool dobleTurno = false;  // Indica si el doble turno está activo
    int turnoJugadorDoble = -1;  // 0 para jugador de turnos pares, 1 para jugador de turnos impares
    bool seleccionInicial;
    int turnoActual;
    int nodoInicial, nodoFinal;
    int jugadorActual;
    bool accionRealizada;
    bool seleccionDisparo;
    int contadorTurnos = 1;
    int* powerUpsJugador1;  // Lista de power-ups para el Jugador 1
    int* powerUpsJugador2;  // Lista de power-ups para el Jugador 2

    bool listaLlenaDeCeros(int* lista);  // Función auxiliar para verificar si la lista tiene solo ceros
    bool precisionDeAtaqueActivado;  // Variable para controlar cuándo está activo el power-up de precisión de ataque

    bool dobleturnoActivado;
    bool dobleturnoDisponible;


    bool poderDeAtaqueActivado;  // Variable para indicar si el poder de ataque está activo



    QPixmap imgTanqueAmarillo;
    QPixmap imgTanqueAzul;
    QPixmap imgTanqueCeleste;
    QPixmap imgTanqueRojo;

    Bala* balaActual;  // Bala activa en el juego

    void dibujarCamino(Tanque* tanque, QPainter& painter);
    void dibujarTanque(Tanque* tanque, QPixmap& imagenTanque, QPainter& painter);
    void dibujarBala(QPainter& painter);  // Método para dibujar la bala

    bool validarSeleccionInicial(int nodoCercano);
    void moverTanqueActual();
    void siguienteTurno(bool dobleTurnoObtenido, int contadorTurnos);
    void dispararBala(int xObjetivo, int yObjetivo);  // Método para disparar

    void keyPressEvent(QKeyEvent *event);

    void activarPrecisionAtaque(int xObjetivo, int yObjetivo);

};

#endif
