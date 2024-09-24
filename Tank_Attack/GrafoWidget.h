#ifndef GRAFOWIDGET_H
#define GRAFOWIDGET_H

#include <QWidget>
#include "Grafo.h"

class GrafoWidget : public QWidget {
    Q_OBJECT

public:
    explicit GrafoWidget(QWidget *parent = nullptr);
    void setGrafo(Grafo* grafo);  // Método para asignar el grafo que queremos dibujar

protected:
    void paintEvent(QPaintEvent *event) override;  // Sobrescribimos el método para dibujar

private:
    Grafo* grafo;  // Puntero al grafo que queremos dibujar
};

#endif // GRAFOWIDGET_H
