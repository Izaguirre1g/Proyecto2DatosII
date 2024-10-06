#include "GrafoWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <iostream>

GrafoWidget::GrafoWidget(QWidget *parent)
    : QWidget(parent), grafo(nullptr), seleccionInicial(true), turnoActual(0), nodoInicial(-1), nodoFinal(-1) {

    // Cargar las imágenes de los tanques
    imgTanqueAmarillo.load("/home/oem/Documentos/Tank_Attack/Amarillo.png");
    imgTanqueAzul.load("/home/oem/Documentos/Tank_Attack/Azul.png");
    imgTanqueCeleste.load("/home/oem/Documentos/Tank_Attack/Celeste.png");
    imgTanqueRojo.load("/home/oem/Documentos/Tank_Attack/Rojo.png");

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
    QPixmap background("/home/oem/Documentos/Tank_Attack/battlefield.jpg");
    if (!background.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background);
    }

    // Dibujar la línea entre los nodos seleccionados (solo si se ha seleccionado un nodo inicial y final)
    if (nodoInicial != -1 && nodoFinal != -1) {
        QPen pen;
        pen.setColor(Qt::red);  // Un color de línea general
        pen.setWidth(3);
        painter.setPen(pen);

        int x1 = grafo->getPosicionX(nodoInicial);
        int y1 = grafo->getPosicionY(nodoInicial);
        int x2 = grafo->getPosicionX(nodoFinal);
        int y2 = grafo->getPosicionY(nodoFinal);

        painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
    }

    // Dibujar los tanques en sus posiciones actuales (en los nodos correspondientes)
    if (tanqueAmarillo) {
        int x = grafo->getPosicionX(tanqueAmarillo->obtenerNodoActual());
        int y = grafo->getPosicionY(tanqueAmarillo->obtenerNodoActual());
        painter.drawPixmap(x - imgTanqueAmarillo.width() / 2, y - imgTanqueAmarillo.height() / 2, imgTanqueAmarillo);
    }

    if (tanqueAzul) {
        int x = grafo->getPosicionX(tanqueAzul->obtenerNodoActual());
        int y = grafo->getPosicionY(tanqueAzul->obtenerNodoActual());
        painter.drawPixmap(x - imgTanqueAzul.width() / 2, y - imgTanqueAzul.height() / 2, imgTanqueAzul);
    }

    if (tanqueCeleste) {
        int x = grafo->getPosicionX(tanqueCeleste->obtenerNodoActual());
        int y = grafo->getPosicionY(tanqueCeleste->obtenerNodoActual());
        painter.drawPixmap(x - imgTanqueCeleste.width() / 2, y - imgTanqueCeleste.height() / 2, imgTanqueCeleste);
    }

    if (tanqueRojo) {
        int x = grafo->getPosicionX(tanqueRojo->obtenerNodoActual());
        int y = grafo->getPosicionY(tanqueRojo->obtenerNodoActual());
        painter.drawPixmap(x - imgTanqueRojo.width() / 2, y - imgTanqueRojo.height() / 2, imgTanqueRojo);
    }
}


void GrafoWidget::mousePressEvent(QMouseEvent *event) {
    if (!grafo) return;

    int clickX = static_cast<int>(event->position().x());
    int clickY = static_cast<int>(event->position().y());

    int numNodos = grafo->obtenerNumNodos();
    int nodoCercano = -1;
    double distanciaMinima = std::numeric_limits<double>::max();

    // Encontrar el nodo más cercano al clic
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
            // Validar que el nodo inicial coincida con la posición actual del tanque en turno
            bool seleccionValida = false;
            switch (turnoActual) {
            case 0:  // Turno del tanque amarillo
                if (nodoCercano == tanqueAmarillo->obtenerNodoActual()) {
                    seleccionValida = true;
                }
                break;
            case 1:  // Turno del tanque azul
                if (nodoCercano == tanqueAzul->obtenerNodoActual()) {
                    seleccionValida = true;
                }
                break;
            case 2:  // Turno del tanque celeste
                if (nodoCercano == tanqueCeleste->obtenerNodoActual()) {
                    seleccionValida = true;
                }
                break;
            case 3:  // Turno del tanque rojo
                if (nodoCercano == tanqueRojo->obtenerNodoActual()) {
                    seleccionValida = true;
                }
                break;
            }

            if (seleccionValida) {
                nodoInicial = nodoCercano;  // Seleccionar el nodo inicial
                nodoFinal = -1;  // Resetear el nodo final
                seleccionInicial = false;  // Cambiar el estado para seleccionar el nodo final
            } else {
                std::cout << "Por favor, selecciona el nodo donde está el tanque en turno." << std::endl;
            }
        } else {
            // Seleccionar el nodo final para mover el tanque
            nodoFinal = nodoCercano;

            // Mover el tanque actual en base a los nodos seleccionados
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

            siguienteTurno();  // Avanzar al siguiente turno
        }

        update();  // Redibujar la ventana
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
