#include "GrafoWidget.h"
#include "Dijkstra.h"
#include <QPaintEvent>
#include <QMouseEvent>  // Incluir el archivo de cabecera de QMouseEvent
#include <QPainter>
#include <cmath>
#include <limits>

GrafoWidget::GrafoWidget(QWidget *parent) : QWidget(parent), grafo(nullptr) {
    setFixedSize(1050,720);
}

void GrafoWidget::setGrafo(Grafo* grafo) {
    this->grafo = grafo;
    update();  // Redibujar el widget cuando se asigna un nuevo grafo
}

void GrafoWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dibujar imagen de fondo
    QPixmap background(":/Imagenes/battlefield.jpg");
    painter.drawPixmap(0, 0, width(), height(), background);

    // Dibujar el camino si existe
    if (camino != nullptr && longitudCamino > 0) {
        painter.setPen(QPen(Qt::red, 3));  // Dibujar aristas en rojo
        for (int i = 0; i < longitudCamino - 1; ++i) {
            int x1 = grafo->getPosicionX(camino[i]);
            int y1 = grafo->getPosicionY(camino[i]);
            int x2 = grafo->getPosicionX(camino[i + 1]);
            int y2 = grafo->getPosicionY(camino[i + 1]);
            painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));  // Dibujar la línea entre los nodos
        }
    }
}

void GrafoWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && grafo) {
        int clickX = static_cast<int>(event->position().x());
        int clickY = static_cast<int>(event->position().y());

        int numNodos = grafo->getNumNodos();
        int nodoCercano = -1;
        double distanciaMinima = std::numeric_limits<double>::max();

        for (int i = 0; i < numNodos; ++i) {
            int x = grafo->getPosicionX(i);
            int y = grafo->getPosicionY(i);
            double distancia = std::sqrt(std::pow(clickX - x, 2) + std::pow(clickY - y, 2));

            if (distancia < distanciaMinima) {
                distanciaMinima = distancia;
                nodoCercano = i;
            }
        }

        if (nodoCercano != -1) {
            if (seleccionInicial) {
                nodoInicial = nodoCercano;
                seleccionInicial = false;
            } else {
                nodoFinal = nodoCercano;
                seleccionInicial = true;

                // Liberar el camino anterior si existe
                if (camino != nullptr) {
                    delete[] camino;
                    camino = nullptr;  // Asegúrate de restablecer el puntero a nullptr después de liberar
                }

                // Ejecutar Dijkstra
                camino = dijkstra(*grafo, nodoInicial, nodoFinal, longitudCamino);

                // Redibujar el widget para mostrar el camino
                update();
            }
        }
    }
}














    /*
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
    }*/


