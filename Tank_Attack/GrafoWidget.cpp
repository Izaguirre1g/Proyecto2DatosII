#include "GrafoWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <iostream>

GrafoWidget::GrafoWidget(QWidget *parent)
    : QWidget(parent), grafo(nullptr), seleccionInicial(true), turnoActual(0), nodoInicial(-1), nodoFinal(-1) {

    // Cargar las imágenes de los tanques
    imgTanqueAmarillo.load(":Imagenes/Amarillo.png");
    imgTanqueAzul.load(":Imagenes/Azul.png");
    imgTanqueCeleste.load(":Imagenes/Celeste.png");
    imgTanqueRojo.load(":Imagenes/Rojo.png");

    // Verificar si las imágenes se cargaron correctamente
    if (imgTanqueAmarillo.isNull()) std::cerr << "Error al cargar la imagen del tanque amarillo\n";
    if (imgTanqueAzul.isNull()) std::cerr << "Error al cargar la imagen del tanque azul\n";
    if (imgTanqueCeleste.isNull()) std::cerr << "Error al cargar la imagen del tanque celeste\n";
    if (imgTanqueRojo.isNull()) std::cerr << "Error al cargar la imagen del tanque rojo\n";

    // Inicializar el temporizador para mover el tanque del turno actual
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

void GrafoWidget::paintEvent(QPaintEvent *event) {
    if (!grafo) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Cargar la imagen de fondo
    QPixmap background(":Imagenes/battlefield.jpg");
    if (!background.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background);
    }

    // Dibujar caminos
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

    // Dibujar los tanques
    dibujarTanque(tanqueAmarillo, imgTanqueAmarillo, painter);
    dibujarTanque(tanqueAzul, imgTanqueAzul, painter);
    dibujarTanque(tanqueCeleste, imgTanqueCeleste, painter);
    dibujarTanque(tanqueRojo, imgTanqueRojo, painter);
}

void GrafoWidget::dibujarCamino(Tanque* tanque, QPainter& painter) {
    int* camino = tanque->getCamino();
    int longitud = tanque->getLongitudCamino();

    for (int i = 0; i < longitud - 1; ++i) {
        int x1 = grafo->getPosicionX(camino[i]);
        int y1 = grafo->getPosicionY(camino[i]);
        int x2 = grafo->getPosicionX(camino[i + 1]);
        int y2 = grafo->getPosicionY(camino[i + 1]);
        painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
    }
}

void GrafoWidget::dibujarTanque(Tanque* tanque, QPixmap& imagenTanque, QPainter& painter) {
    int x = grafo->getPosicionX(tanque->obtenerNodoActual());
    int y = grafo->getPosicionY(tanque->obtenerNodoActual());
    painter.drawPixmap(x - imagenTanque.width() / 2, y - imagenTanque.height() / 2, imagenTanque);
}

void GrafoWidget::moverTanquePasoAPaso() {
    // Mueve el tanque del turno actual paso a paso hasta que complete su camino
    switch (turnoActual) {
    case 0:  // Tanque amarillo
        if (tanqueAmarillo->getCamino() != nullptr && !tanqueAmarillo->haTerminadoCamino()) {
            tanqueAmarillo->avanzarCaminoPaso();
        } else {
            movimientoTimer->stop();
            siguienteTurno();
        }
        break;
    case 1:  // Tanque azul
        if (tanqueAzul->getCamino() != nullptr && !tanqueAzul->haTerminadoCamino()) {
            tanqueAzul->avanzarCaminoPaso();
        } else {
            movimientoTimer->stop();
            siguienteTurno();
        }
        break;
    case 2:  // Tanque celeste
        if (tanqueCeleste->getCamino() != nullptr && !tanqueCeleste->haTerminadoCamino()) {
            tanqueCeleste->avanzarCaminoPaso();
        } else {
            movimientoTimer->stop();
            siguienteTurno();
        }
        break;
    case 3:  // Tanque rojo
        if (tanqueRojo->getCamino() != nullptr && !tanqueRojo->haTerminadoCamino()) {
            tanqueRojo->avanzarCaminoPaso();
        } else {
            movimientoTimer->stop();
            siguienteTurno();
        }
        break;
    }

    update();  // Redibuja la ventana con el tanque en su nueva posición
}

void GrafoWidget::mousePressEvent(QMouseEvent *event) {
    if (!grafo) return;

    int clickX = static_cast<int>(event->position().x());
    int clickY = static_cast<int>(event->position().y());

    int nodoCercano = grafo->encontrarNodoCercano(clickX, clickY);

    if (nodoCercano != -1) {
        if (seleccionInicial) {
            if (validarSeleccionInicial(nodoCercano)) {
                nodoInicial = nodoCercano;
                seleccionInicial = false;
            } else {
                std::cout << "Selecciona el nodo donde está el tanque en turno." << std::endl;
            }
        } else {
            nodoFinal = nodoCercano;
            moverTanqueActual();  // Iniciar el movimiento del tanque en turno
            movimientoTimer->start(500);  // Iniciar el temporizador para mover el tanque cada 500 ms
        }

        update();  // Redibujar la ventana
    }
}

bool GrafoWidget::validarSeleccionInicial(int nodoCercano) {
    switch (turnoActual) {
    case 0: return nodoCercano == tanqueAmarillo->obtenerNodoActual();
    case 1: return nodoCercano == tanqueAzul->obtenerNodoActual();
    case 2: return nodoCercano == tanqueCeleste->obtenerNodoActual();
    case 3: return nodoCercano == tanqueRojo->obtenerNodoActual();
    default: return false;
    }
}

void GrafoWidget::moverTanqueActual() {
    switch (turnoActual) {
    case 0:  // Tanque amarillo
        tanqueAmarillo->setNodoObjetivo(nodoFinal);
        tanqueAmarillo->mover();
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
    turnoActual = (turnoActual + 1) % 4;  // Cambiar al siguiente tanque
    nodoInicial = -1;
    nodoFinal = -1;
    seleccionInicial = true;
    update();
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


