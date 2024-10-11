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

class GrafoWidget : public QWidget {
    Q_OBJECT

public:
    explicit GrafoWidget(QWidget *parent = nullptr);
    void setGrafo(Grafo* grafo);
    void setTanques(TanqueAmarillo* amarillo1, TanqueAmarillo* amarillo2, TanqueAzul* azul1, TanqueAzul* azul2,
                    TanqueCeleste* celeste1, TanqueCeleste* celeste2, TanqueRojo* rojo1, TanqueRojo* rojo2);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void moverTanquePasoAPaso();

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
    bool seleccionInicial;
    int turnoActual;
    int nodoInicial, nodoFinal;
    int jugadorActual;  // 0: Jugador 1, 1: Jugador 2

    QPixmap imgTanqueAmarillo;
    QPixmap imgTanqueAzul;
    QPixmap imgTanqueCeleste;
    QPixmap imgTanqueRojo;

    void dibujarCamino(Tanque* tanque, QPainter& painter);
    void dibujarTanque(Tanque* tanque, QPixmap& imagenTanque, QPainter& painter);
    bool validarSeleccionInicial(int nodoCercano);
    void moverTanqueActual();  // Iniciar el movimiento
    void siguienteTurno();     // Cambiar entre los jugadores
};

#endif
