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

    Tanque* obtenerTanqueActual();  // Método que devuelve el tanque en turno
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

    QTimer* movimientoTimer;
    QTimer* balaTimer;  // Temporizador para manejar el movimiento de las balas

    bool seleccionInicial;
    int turnoActual;
    int nodoInicial, nodoFinal;
    int jugadorActual;
    bool accionRealizada;
    bool seleccionDisparo;


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
    void aplicarDano(Tanque* tanque, int indice);
};

#endif
