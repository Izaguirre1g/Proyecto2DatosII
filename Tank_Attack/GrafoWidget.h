#ifndef GRAFOWIDGET_H
#define GRAFOWIDGET_H

#include <QWidget>
#include "Grafo.h"

class GrafoWidget : public QWidget {
    Q_OBJECT

public:
    explicit GrafoWidget(QWidget *parent = nullptr);
    void setGrafo(Grafo* grafo);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Grafo* grafo;
    int nodoInicial;      // Nodo inicial seleccionado
    int nodoFinal;        // Nodo final seleccionado
    bool seleccionInicial;  // Saber si estamos seleccionando el nodo inicial o final

    int* camino=nullptr;          // Puntero al arreglo del camino calculado por Dijkstra
    int longitudCamino=0;   // Longitud del camino calculado

};

#endif // GRAFOWIDGET_H
