#ifndef GRAFOWIDGET_H
#define GRAFOWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include "TanqueAmarillo.h"
#include "TanqueAzul.h"
#include "TanqueCeleste.h"
#include "TanqueRojo.h"
#include "Grafo.h"

class GrafoWidget : public QWidget {
    Q_OBJECT

public:
    explicit GrafoWidget(QWidget *parent = nullptr);

    void setGrafo(Grafo* grafo);
    void setTanques(TanqueAmarillo* amarillo, TanqueAzul* azul, TanqueCeleste* celeste, TanqueRojo* rojo);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void moverTanquePasoAPaso();

private:
    Grafo* grafo;
    TanqueAmarillo* tanqueAmarillo;
    TanqueAzul* tanqueAzul;
    TanqueCeleste* tanqueCeleste;
    TanqueRojo* tanqueRojo;

    QPixmap imgTanqueAmarillo;
    QPixmap imgTanqueAzul;
    QPixmap imgTanqueCeleste;
    QPixmap imgTanqueRojo;

    QTimer* movimientoTimer;

    int turnoActual;  // Controla de quién es el turno (0: amarillo, 1: azul, etc.)
    int nodoInicial;  // Nodo de inicio seleccionado
    int nodoFinal;    // Nodo final seleccionado
    bool seleccionInicial;  // Estado de selección inicial del nodo

    // Métodos de utilidad
    void dibujarCamino(Tanque* tanque, QPainter &painter);
    void dibujarTanque(Tanque* tanque, QPixmap &imagenTanque, QPainter &painter);
    bool validarSeleccionInicial(int nodoCercano);
    void moverTanqueActual();
    void siguienteTurno();
};

#endif // GRAFOWIDGET_H
