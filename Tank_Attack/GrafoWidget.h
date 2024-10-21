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
    void activarDobleTurno();
    Tanque* obtenerTanqueActual();  // Método que devuelve el tanque en turno


    //Ecuacion auxiliar
    bool existeEnArreglo(int arr[], int size, int valor);
    // Declaración de la función tipoPowersUp
    int* tipoPowersUp();  // Asegúrate de que está declarada aquí si pertenece a esta clase


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


    bool dobleTurno = false;  // Indica si el doble turno está activo
    int turnoJugadorDoble = -1;  // 0 para jugador de turnos pares, 1 para jugador de turnos impares
    bool seleccionInicial;
    int turnoActual;
    int nodoInicial, nodoFinal;
    int jugadorActual;
    bool accionRealizada;
    bool seleccionDisparo;

    int* powerUpsJugador1;  // Lista de power-ups para el Jugador 1
    int* powerUpsJugador2;  // Lista de power-ups para el Jugador 2

    bool listaLlenaDeCeros(int* lista);  // Función auxiliar para verificar si la lista tiene solo ceros


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
    void siguienteTurno();
    void dispararBala(int xObjetivo, int yObjetivo);  // Método para disparar

    void keyPressEvent(QKeyEvent *event);



};

#endif
