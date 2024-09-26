#include "GrafoWidget.h"
#include <QPainter>

GrafoWidget::GrafoWidget(QWidget *parent) : QWidget(parent), grafo(nullptr) {}

void GrafoWidget::setGrafo(Grafo* grafo) {
    this->grafo = grafo;
    update();  // Redibujar el widget cuando se asigna un nuevo grafo
}

void GrafoWidget::paintEvent(QPaintEvent *event) {
    if (!grafo) return;  // Si no hay grafo, no dibujamos nada

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dibujar los nodos
    int numNodos = grafo->obtenerNumNodos();
    for (int i = 0; i < numNodos; ++i) {
        int x = grafo->getPosicionX(i);
        int y = grafo->getPosicionY(i);
        painter.setBrush(Qt::blue);
        painter.drawEllipse(QPoint(x, y), 10, 10);  // Dibujar el nodo como un círculo
    }

    // Dibujar las conexiones (aristas)
    for (int i = 0; i < numNodos; ++i) {
        for (int j = 0; j < numNodos; ++j) {
            int peso = grafo->obtenerPeso(i, j);
            if (peso > 0) {  // Solo dibujar si hay una conexión (peso > 0)
                int x1 = grafo->getPosicionX(i);
                int y1 = grafo->getPosicionY(i);
                int x2 = grafo->getPosicionX(j);
                int y2 = grafo->getPosicionY(j);
                painter.setPen(Qt::black);
                painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));  // Dibujar la arista
            }
        }
    }
}
