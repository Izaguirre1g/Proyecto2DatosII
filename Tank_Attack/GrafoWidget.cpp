#include "GrafoWidget.h"
#include <QPainter>
#include <QPixmap>

GrafoWidget::GrafoWidget(QWidget *parent) : QWidget(parent), grafo(nullptr) {
    setFixedSize(1050,720);
}

void GrafoWidget::setGrafo(Grafo* grafo) {
    this->grafo = grafo;
    update();  // Redibujar el widget cuando se asigna un nuevo grafo
}

void GrafoWidget::paintEvent(QPaintEvent *event) {
    //if (!grafo) return;  // Si no hay grafo, no dibujamos nada

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Cargar y dibujar la imagen de fondo (background.png)
    QPixmap background(":/battlefield.jpg");  // Ajusta la ruta según tu proyecto
    if (!background.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background);
    } else {
        qDebug() << "Error: No se pudo cargar la imagen.";
    }


    // Dibujar los nodos
    int numNodos = grafo->getNumNodos();
    for (int i = 0; i < numNodos; ++i) {
        int x = grafo->getPosicionX(i);
        int y = grafo->getPosicionY(i);
        painter.setBrush(Qt::green);
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

