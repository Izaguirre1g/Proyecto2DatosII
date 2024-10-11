#include "GrafoWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <iostream>

GrafoWidget::GrafoWidget(QWidget *parent)
    : QWidget(parent), grafo(nullptr), seleccionInicial(true), turnoActual(0), nodoInicial(-1), nodoFinal(-1), jugadorActual(0) {

    // Cargar las imágenes de los tanques
    imgTanqueAmarillo.load("/home/oem/Documentos/Tank_Attack/Amarillo.png");
    imgTanqueAzul.load("/home/oem/Documentos/Tank_Attack/Azul.png");
    imgTanqueCeleste.load("/home/oem/Documentos/Tank_Attack/Celeste.png");
    imgTanqueRojo.load("/home/oem/Documentos/Tank_Attack/Rojo.png");

    if (imgTanqueAmarillo.isNull()) std::cerr << "Error al cargar la imagen del tanque amarillo\n";
    if (imgTanqueAzul.isNull()) std::cerr << "Error al cargar la imagen del tanque azul\n";
    if (imgTanqueCeleste.isNull()) std::cerr << "Error al cargar la imagen del tanque celeste\n";
    if (imgTanqueRojo.isNull()) std::cerr << "Error al cargar la imagen del tanque rojo\n";

    movimientoTimer = new QTimer(this);
    connect(movimientoTimer, &QTimer::timeout, this, &GrafoWidget::moverTanquePasoAPaso);
}

void GrafoWidget::setGrafo(Grafo* grafo) {
    this->grafo = grafo;
    update();
}

void GrafoWidget::setTanques(TanqueAmarillo* amarillo1, TanqueAmarillo* amarillo2, TanqueAzul* azul1, TanqueAzul* azul2,
                             TanqueCeleste* celeste1, TanqueCeleste* celeste2, TanqueRojo* rojo1, TanqueRojo* rojo2) {
    this->tanqueAmarillo1 = amarillo1;
    this->tanqueAmarillo2 = amarillo2;
    this->tanqueAzul1 = azul1;
    this->tanqueAzul2 = azul2;
    this->tanqueCeleste1 = celeste1;
    this->tanqueCeleste2 = celeste2;
    this->tanqueRojo1 = rojo1;
    this->tanqueRojo2 = rojo2;
}

void GrafoWidget::paintEvent(QPaintEvent *event) {
    if (!grafo) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dibujar el fondo
    QPixmap background("/home/oem/Documentos/Tank_Attack/battlefield.jpg");
    if (!background.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background);
    }

    // Dibujar obstáculos (nodos bloqueados)
    painter.setBrush(Qt::black);  // Color negro para los obstáculos
    painter.setPen(Qt::NoPen);    // Sin borde para los obstáculos

    for (int i = 0; i < grafo->obtenerNumNodos(); ++i) {
        if (grafo->nodosBloqueados[i]) {  // Verificar si el nodo está bloqueado
            int x = grafo->getPosicionX(i);  // Obtener posición X del nodo
            int y = grafo->getPosicionY(i);  // Obtener posición Y del nodo
            int radioObstaculo = 15;  // Tamaño del obstáculo (puedes ajustarlo)

            // Dibujar un círculo para representar el obstáculo
            painter.drawEllipse(QPoint(x, y), radioObstaculo, radioObstaculo);
        }
    }

    QPen pen;

    // Dibujar caminos
    if (tanqueAmarillo1 && tanqueAmarillo1->getCamino() != nullptr) {
        pen.setColor(Qt::yellow);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueAmarillo1, painter);
    }

    if (tanqueAmarillo2 && tanqueAmarillo2->getCamino() != nullptr) {
        pen.setColor(Qt::yellow);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueAmarillo2, painter);
    }

    if (tanqueAzul1 && tanqueAzul1->getCamino() != nullptr) {
        pen.setColor(Qt::blue);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueAzul1, painter);
    }

    if (tanqueAzul2 && tanqueAzul2->getCamino() != nullptr) {
        pen.setColor(Qt::blue);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueAzul2, painter);
    }

    if (tanqueCeleste1 && tanqueCeleste1->getCamino() != nullptr) {
        pen.setColor(Qt::cyan);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueCeleste1, painter);
    }

    if (tanqueCeleste2 && tanqueCeleste2->getCamino() != nullptr) {
        pen.setColor(Qt::cyan);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueCeleste2, painter);
    }

    if (tanqueRojo1 && tanqueRojo1->getCamino() != nullptr) {
        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueRojo1, painter);
    }

    if (tanqueRojo2 && tanqueRojo2->getCamino() != nullptr) {
        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueRojo2, painter);
    }

    // Dibujar tanques
    if (tanqueAmarillo1) dibujarTanque(tanqueAmarillo1, imgTanqueAmarillo, painter);
    if (tanqueAmarillo2) dibujarTanque(tanqueAmarillo2, imgTanqueAmarillo, painter);
    if (tanqueAzul1) dibujarTanque(tanqueAzul1, imgTanqueAzul, painter);
    if (tanqueAzul2) dibujarTanque(tanqueAzul2, imgTanqueAzul, painter);
    if (tanqueCeleste1) dibujarTanque(tanqueCeleste1, imgTanqueCeleste, painter);
    if (tanqueCeleste2) dibujarTanque(tanqueCeleste2, imgTanqueCeleste, painter);
    if (tanqueRojo1) dibujarTanque(tanqueRojo1, imgTanqueRojo, painter);
    if (tanqueRojo2) dibujarTanque(tanqueRojo2, imgTanqueRojo, painter);
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
    if (tanque == nullptr) {
        std::cerr << "Error: El tanque es nullptr, no se puede dibujar." << std::endl;
        return;  // Evitar dibujar si el tanque es nulo
    }
    int x = grafo->getPosicionX(tanque->obtenerNodoActual());
    int y = grafo->getPosicionY(tanque->obtenerNodoActual());
    painter.drawPixmap(x - imagenTanque.width() / 2, y - imagenTanque.height() / 2, imagenTanque);
}

void GrafoWidget::moverTanquePasoAPaso() {
    // Mueve el tanque del turno actual paso a paso hasta que complete su camino
    bool mover = false;

    switch (turnoActual) {
    case 0:  // Tanque rojo 1
        if (tanqueRojo1->getCamino() != nullptr && !tanqueRojo1->haTerminadoCamino()) {
            tanqueRojo1->avanzarCaminoPaso();  // Avanza un paso en el camino
            mover = true;
        }
        break;
    case 1:  // Tanque rojo 2
        if (tanqueAmarillo1->getCamino() != nullptr && !tanqueAmarillo1->haTerminadoCamino()) {
            tanqueAmarillo1->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 2:  // Tanque azul 1
        if (tanqueAzul1->getCamino() != nullptr && !tanqueAzul1->haTerminadoCamino()) {
            tanqueAzul1->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 3:  // Tanque azul 2
        if (tanqueCeleste1->getCamino() != nullptr && !tanqueCeleste1->haTerminadoCamino()) {
            tanqueCeleste1->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 4:  // Tanque amarillo 1
        if (tanqueRojo2->getCamino() != nullptr && !tanqueRojo2->haTerminadoCamino()) {
            tanqueRojo2->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 5:  // Tanque celeste 1
        if (tanqueAmarillo2->getCamino() != nullptr && !tanqueAmarillo2->haTerminadoCamino()) {
            tanqueAmarillo2->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 6:  // Tanque amarillo 2
        if (tanqueAzul2->getCamino() != nullptr && !tanqueAzul2->haTerminadoCamino()) {
            tanqueAzul2->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 7:  // Tanque celeste 2
        if (tanqueCeleste2->getCamino() != nullptr && !tanqueCeleste2->haTerminadoCamino()) {
            tanqueCeleste2->avanzarCaminoPaso();
            mover = true;
        }
        break;
    }

    if (!mover) {
        movimientoTimer->stop();  // Detener el temporizador cuando termina el movimiento
        siguienteTurno();  // Cambiar al siguiente turno
    }

    update();  // Redibuja la ventana con el tanque en su nueva posición
}


void GrafoWidget::mousePressEvent(QMouseEvent *event) {
    if (!grafo) return;

    int clickX = static_cast<int>(event->position().x());
    int clickY = static_cast<int>(event->position().y());

    int nodoCercano = grafo->encontrarNodoCercano(clickX, clickY);

    if (nodoCercano != -1) {
        std::cout << "Nodo cercano seleccionado: " << nodoCercano << std::endl;

        if (seleccionInicial) {
            if (validarSeleccionInicial(nodoCercano)) {
                nodoInicial = nodoCercano;
                seleccionInicial = false;
                std::cout << "Nodo inicial seleccionado para el tanque en turno " << turnoActual << std::endl;
            } else {
                std::cout << "El nodo seleccionado no corresponde al tanque en turno." << std::endl;
            }
        } else {
            nodoFinal = nodoCercano;
            std::cout << "Nodo final seleccionado: " << nodoFinal << std::endl;
            moverTanqueActual();  // Iniciar el movimiento del tanque en turno
            movimientoTimer->start(500);  // Iniciar el temporizador para mover el tanque cada 500 ms
        }

        update();
    }
}

bool GrafoWidget::validarSeleccionInicial(int nodoCercano) {
    // Validar si el nodo pertenece al tanque en turno y si corresponde al turno actual
    switch (turnoActual) {
    case 0: return nodoCercano == tanqueRojo1->obtenerNodoActual();  // Jugador 1, tanque rojo 1
    case 1: return nodoCercano == tanqueAmarillo1->obtenerNodoActual();  // Jugador 2, tanque amarillo 1
    case 2: return nodoCercano == tanqueAzul1->obtenerNodoActual();  // Jugador 1, tanque azul 1
    case 3: return nodoCercano == tanqueCeleste1->obtenerNodoActual();  // Jugador 2, tanque celeste 1
    case 4: return nodoCercano == tanqueRojo2->obtenerNodoActual();  // Jugador 1, tanque rojo 2
    case 5: return nodoCercano == tanqueAmarillo2->obtenerNodoActual();  // Jugador 2, tanque amarillo 2
    case 6: return nodoCercano == tanqueAzul2->obtenerNodoActual();  // Jugador 1, tanque azul 2
    case 7: return nodoCercano == tanqueCeleste2->obtenerNodoActual();  // Jugador 2, tanque celeste 2
    default: return false;
    }
}


void GrafoWidget::moverTanqueActual() {
    switch (turnoActual) {
    case 0:  // Tanque rojo 1
        tanqueRojo1->setNodoObjetivo(nodoFinal);
        tanqueRojo1->mover();  // Calcular el camino usando Dijkstra
        break;
    case 1:  // Tanque amarillo 1
        tanqueAmarillo1->setNodoObjetivo(nodoFinal);
        tanqueAmarillo1->mover();
        break;
    case 2:  // Tanque azul 1
        tanqueAzul1->setNodoObjetivo(nodoFinal);
        tanqueAzul1->mover();
        break;
    case 3:  // Tanque celeste 1
        tanqueCeleste1->setNodoObjetivo(nodoFinal);
        tanqueCeleste1->mover();
        break;
    case 4:  // Tanque rojo 2
        tanqueRojo2->setNodoObjetivo(nodoFinal);
        tanqueRojo2->mover();
        break;
    case 5:  // Tanque amarillo 2
        tanqueAmarillo2->setNodoObjetivo(nodoFinal);
        tanqueAmarillo2->mover();
        break;
    case 6:  // Tanque azul 2
        tanqueAzul2->setNodoObjetivo(nodoFinal);
        tanqueAzul2->mover();
        break;
    case 7:  // Tanque celeste 2
        tanqueCeleste2->setNodoObjetivo(nodoFinal);
        tanqueCeleste2->mover();
        break;
    }

    // Cambiar el turno después de mover
    movimientoTimer->start(500);  // Comenzar el temporizador para mover el tanque paso a paso
}


void GrafoWidget::siguienteTurno() {
    turnoActual = (turnoActual + 1) % 8;  // Cambiar entre los 8 tanques

    // Jugador 1 mueve en turnos 0, 2, 4, 6 (pares)
    // Jugador 2 mueve en turnos 1, 3, 5, 7 (impares)
    jugadorActual = (turnoActual % 2 == 0) ? 0 : 1;  // Jugador 1 para pares, Jugador 2 para impares

    nodoInicial = -1;
    nodoFinal = -1;
    seleccionInicial = true;
    std::cout << "Cambio al turno del tanque: " << turnoActual << " (Jugador " << jugadorActual + 1 << ")" << std::endl;
    update();
}
