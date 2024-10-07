#ifndef GRAFOWIDGET_H
#define GRAFOWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>  // Necesario para usar QPixmap
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
    void setTanques(TanqueAmarillo* amarillo, TanqueAzul* azul, TanqueCeleste* celeste, TanqueRojo* rojo);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void moverTanquePasoAPaso();  // Un solo temporizador para manejar el tanque en turno.

private:
    Grafo* grafo;
    TanqueAmarillo* tanqueAmarillo;
    TanqueAzul* tanqueAzul;
    TanqueCeleste* tanqueCeleste;
    TanqueRojo* tanqueRojo;

    QTimer* movimientoTimer;  // Un solo temporizador que controla el tanque en turno.

    bool seleccionInicial;
    int turnoActual;  // Turno actual del tanque que se mueve
    int nodoInicial, nodoFinal;  // Nodo de origen y destino

    QPixmap imgTanqueAmarillo;  // Agregamos las imágenes de los tanques
    QPixmap imgTanqueAzul;
    QPixmap imgTanqueCeleste;
    QPixmap imgTanqueRojo;

    void dibujarCamino(Tanque* tanque, QPainter& painter);
    void dibujarTanque(Tanque* tanque, QPixmap& imagenTanque, QPainter& painter);
    bool validarSeleccionInicial(int nodoCercano);
    void moverTanqueActual();  // Llamado para comenzar a mover el tanque en turno
    void siguienteTurno();  // Cambiar de turno solo cuando el tanque ha terminado de moverse.
};

#endif
