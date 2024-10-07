#include "GrafoWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <cmath>
#include <iostream>

GrafoWidget::GrafoWidget(QWidget *parent)
    : QWidget(parent), grafo(nullptr), seleccionInicial(true), turnoActual(0), nodoInicial(-1), nodoFinal(-1) {

    // Cargar las imágenes de los tanques
    imgTanqueAmarillo.load(":Imagenes/Amarillo.png");
    imgTanqueAzul.load(":Imagenes/Azul.png");
    imgTanqueCeleste.load(":Imagenes/Celeste.png");
    imgTanqueRojo.load(":Imagenes/Rojo.png");

    // Verificar si las imágenes se cargaron correctamente
    if (imgTanqueAmarillo.isNull()) {
        std::cerr << "Error al cargar la imagen del tanque amarillo\n";
    }
    if (imgTanqueAzul.isNull()) {
        std::cerr << "Error al cargar la imagen del tanque azul\n";
    }
    if (imgTanqueCeleste.isNull()) {
        std::cerr << "Error al cargar la imagen del tanque celeste\n";
    }
    if (imgTanqueRojo.isNull()) {
        std::cerr << "Error al cargar la imagen del tanque rojo\n";
    }

    // Configurar el temporizador para el movimiento paso a paso
    movimientoTimer = new QTimer(this);
    connect(movimientoTimer, &QTimer::timeout, this, &GrafoWidget::moverTanquePasoAPaso);
}

void GrafoWidget::setGrafo(Grafo* grafo) {
    this->grafo = grafo;
    update();
}

void GrafoWidget::setTanques(TanqueAmarillo* amarillo, TanqueAzul* azul, TanqueCeleste* celeste, TanqueRojo* rojo) {
    this->tanqueAmarillo = amarillo;
    this->tanqueAzul = azul;
    this->tanqueCeleste = celeste;
    this->tanqueRojo = rojo;
}

void GrafoWidget::moverTanquePasoAPaso() {
    // Mueve el tanque paso a paso según el turno actual
    switch (turnoActual) {
    case 0:  // Tanque amarillo
        if (tanqueAmarillo->getCamino() != nullptr && !tanqueAmarillo->haTerminadoCamino()) {
            tanqueAmarillo->avanzarCaminoPaso();  // Mueve el tanque al siguiente nodo
        } else {
            movimientoTimer->stop();  // Detener el temporizador si el tanque ha llegado a su destino
        }
        break;
    case 1:  // Tanque azul
        if (tanqueAzul->getCamino() != nullptr && !tanqueAzul->haTerminadoCamino()) {
            tanqueAzul->avanzarCaminoPaso();
        } else {
            movimientoTimer->stop();
        }
        break;
    case 2:  // Tanque celeste
        if (tanqueCeleste->getCamino() != nullptr && !tanqueCeleste->haTerminadoCamino()) {
            tanqueCeleste->avanzarCaminoPaso();
        } else {
            movimientoTimer->stop();
        }
        break;
    case 3:  // Tanque rojo
        if (tanqueRojo->getCamino() != nullptr && !tanqueRojo->haTerminadoCamino()) {
            tanqueRojo->avanzarCaminoPaso();
        } else {
            movimientoTimer->stop();
        }
        break;
    }

    update();  // Redibuja la ventana con el tanque en su nueva posición
}

void GrafoWidget::dibujarCamino(Tanque* tanque, QPainter& painter) {
    if (!tanque || !tanque->getCamino()) return;  // Verifica si el tanque o su camino es nulo

    int* camino = tanque->getCamino();  // Obtener el camino del tanque
    int longitud = tanque->getLongitudCamino();  // Obtener la longitud del camino

    for (int i = 0; i < longitud - 1; ++i) {
        // Obtener las coordenadas X e Y de los nodos en el camino
        int x1 = grafo->getPosicionX(camino[i]);
        int y1 = grafo->getPosicionY(camino[i]);
        int x2 = grafo->getPosicionX(camino[i + 1]);
        int y2 = grafo->getPosicionY(camino[i + 1]);

        // Dibujar una línea entre el nodo actual y el siguiente
        painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
    }
}

void GrafoWidget::dibujarTanque(Tanque* tanque, QPixmap& imagenTanque, QPainter& painter) {
    if (!tanque) return;  // Verifica si el tanque es nulo

    // Obtener las coordenadas del tanque basado en el nodo actual
    int x = grafo->getPosicionX(tanque->obtenerNodoActual());
    int y = grafo->getPosicionY(tanque->obtenerNodoActual());

    // Dibujar la imagen del tanque centrada en la posición del nodo
    painter.drawPixmap(x - imagenTanque.width() / 2, y - imagenTanque.height() / 2, imagenTanque);
}

void GrafoWidget::paintEvent(QPaintEvent *event) {
    if (!grafo) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Cargar la imagen de fondo
    QPixmap background(":Imagenes/battlefield.jpg");
    if (!background.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background);
    }

    // Dibujar el camino de aristas (en color diferente para cada tanque)
    QPen pen;

    if (tanqueAmarillo && tanqueAmarillo->getCamino() != nullptr) {
        pen.setColor(Qt::yellow);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueAmarillo, painter);
    }

    if (tanqueAzul && tanqueAzul->getCamino() != nullptr) {
        pen.setColor(Qt::blue);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueAzul, painter);
    }

    if (tanqueCeleste && tanqueCeleste->getCamino() != nullptr) {
        pen.setColor(Qt::cyan);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueCeleste, painter);
    }

    if (tanqueRojo && tanqueRojo->getCamino() != nullptr) {
        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueRojo, painter);
    }

    // Dibujar los tanques en sus posiciones actuales
    if (tanqueAmarillo) {
        dibujarTanque(tanqueAmarillo, imgTanqueAmarillo, painter);
    }

    if (tanqueAzul) {
        dibujarTanque(tanqueAzul, imgTanqueAzul, painter);
    }

    if (tanqueCeleste) {
        dibujarTanque(tanqueCeleste, imgTanqueCeleste, painter);
    }

    if (tanqueRojo) {
        dibujarTanque(tanqueRojo, imgTanqueRojo, painter);
    }
}

bool GrafoWidget::validarSeleccionInicial(int nodoCercano) {
    switch (turnoActual) {
    case 0:  // Turno del tanque amarillo
        return nodoCercano == tanqueAmarillo->obtenerNodoActual();
    case 1:  // Turno del tanque azul
        return nodoCercano == tanqueAzul->obtenerNodoActual();
    case 2:  // Turno del tanque celeste
        return nodoCercano == tanqueCeleste->obtenerNodoActual();
    case 3:  // Turno del tanque rojo
        return nodoCercano == tanqueRojo->obtenerNodoActual();
    default:
        return false;
    }
}

void GrafoWidget::mousePressEvent(QMouseEvent *event) {
    if (!grafo) return;

    int clickX = static_cast<int>(event->position().x());
    int clickY = static_cast<int>(event->position().y());

    int nodoCercano = grafo->encontrarNodoCercano(clickX, clickY);

    if (nodoCercano != -1) {
        if (seleccionInicial) {
            // Validar que el nodo inicial coincida con el nodo actual del tanque en turno
            if (validarSeleccionInicial(nodoCercano)) {
                nodoInicial = nodoCercano;  // Seleccionamos el nodo inicial
                seleccionInicial = false;   // Cambiamos a la selección del nodo final
            } else {
                std::cout << "Selecciona el nodo donde está el tanque en turno." << std::endl;
            }
        } else {
            nodoFinal = nodoCercano;  // Seleccionar el nodo final

            // Asignar el objetivo al tanque y calcular el camino
            moverTanqueActual();

            movimientoTimer->start(500);  // Iniciar el temporizador para mover el tanque cada 500ms
            siguienteTurno();  // Pasar al siguiente turno
        }

        update();  // Redibujar la ventana
    }
}

void GrafoWidget::moverTanqueActual() {
    switch (turnoActual) {
    case 0:  // Tanque amarillo
        tanqueAmarillo->setNodoObjetivo(nodoFinal);
        tanqueAmarillo->mover();  // Aquí calculamos el camino
        break;
    case 1:  // Tanque azul
        tanqueAzul->setNodoObjetivo(nodoFinal);
        tanqueAzul->mover();
        break;
    case 2:  // Tanque celeste
        tanqueCeleste->setNodoObjetivo(nodoFinal);
        tanqueCeleste->mover();
        break;
    case 3:  // Tanque rojo
        tanqueRojo->setNodoObjetivo(nodoFinal);
        tanqueRojo->mover();
        break;
    }
}

void GrafoWidget::siguienteTurno() {
    // Ciclo entre los 4 tanques (amarillo, azul, celeste, rojo)
    turnoActual = (turnoActual + 1) % 4;
    nodoInicial = -1;  // Reiniciar el nodo inicial para el siguiente turno
    nodoFinal = -1;    // Reiniciar el nodo final para el siguiente turno
    seleccionInicial = true;  // Reiniciar para permitir una nueva selección de nodos
    update();  // Asegurar que se redibuje la ventana al cambiar de turno
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


