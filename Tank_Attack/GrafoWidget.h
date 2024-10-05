#ifndef GRAFOWIDGET_H
#define GRAFOWIDGET_H

#include <QWidget>
#include "Grafo.h"
#include "TanqueAmarillo.h"
#include "TanqueAzul.h"
#include "TanqueCeleste.h"
#include "TanqueRojo.h"
#include <QPixmap>  // Agrega esto para manejar las imágenes

class GrafoWidget : public QWidget {
    Q_OBJECT

public:
    explicit GrafoWidget(QWidget *parent = nullptr);
    void setGrafo(Grafo* grafo);
    void setTanques(TanqueAmarillo* amarillo, TanqueAzul* azul, TanqueCeleste* celeste, TanqueRojo* rojo);  // Asignar los tanques

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Grafo* grafo;
    int nodoInicial;
    int nodoFinal;
    bool seleccionInicial;

    int turnoActual;  // Para gestionar los turnos de los tanques
    TanqueAmarillo* tanqueAmarillo;
    TanqueAzul* tanqueAzul;
    TanqueCeleste* tanqueCeleste;
    TanqueRojo* tanqueRojo;

    // Añade QPixmaps para los tanques
    QPixmap imgTanqueAmarillo;
    QPixmap imgTanqueAzul;
    QPixmap imgTanqueCeleste;
    QPixmap imgTanqueRojo;

    void siguienteTurno();  // Avanzar al siguiente turno
};

#endif // GRAFOWIDGET_H
