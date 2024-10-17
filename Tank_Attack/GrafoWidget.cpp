#include "GrafoWidget.h"
#include "Bala.h"
#include "LineOfSight.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>
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

    balaTimer = new QTimer(this);  // Temporizador para manejar el movimiento de las balas
    connect(balaTimer, &QTimer::timeout, this, &GrafoWidget::moverBala);
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

void GrafoWidget::dibujarBala(QPainter& painter) {
    if (balaActual) {
        // Posición actual de la bala
        int x = balaActual->getX();
        int y = balaActual->getY();

        // Dibuja una estrella de 8 picos
        QPolygon star;
        const int numPicos = 8;
        const float radioExterior = 20;  // Tamaño del radio exterior de la estrella
        const float radioInterior = 10;   // Tamaño del radio interior de la estrella
        const float anguloPaso = M_PI / numPicos;  // Angulo entre cada punto (mitad de 360° dividido entre el número de picos)

        // Generar los puntos de la estrella
        for (int i = 0; i < numPicos * 2; ++i) {
            float angulo = i * anguloPaso;
            float radio = (i % 2 == 0) ? radioExterior : radioInterior;  // Alterna entre el radio exterior e interior
            int px = static_cast<int>(x + radio * cos(angulo));  // Coordenada X del punto
            int py = static_cast<int>(y + radio * sin(angulo));  // Coordenada Y del punto
            star << QPoint(px, py);  // Añade el punto al polígono
        }

        // Establece el color y dibujar la estrella
        painter.setBrush(Qt::darkGray);
        painter.drawPolygon(star);
    }
}


void GrafoWidget::moverBala() {
    if (balaActual && balaActual->estaActiva()) {
        // Mueve la bala paso a paso por el camino
        balaActual->avanzarCaminoPaso(grafo);

        // Actualizamos la interfaz antes de verificar colisiones
        update();  // Esto asegura que la bala se dibuje en su nueva posición

        // Comprobar colisiones con los tanques
        Tanque* tanques[8] = {tanqueRojo1, tanqueRojo2, tanqueAmarillo1, tanqueAmarillo2,
                              tanqueAzul1, tanqueAzul2, tanqueCeleste1, tanqueCeleste2};

        bool colisionDetectada = false;  // Nueva variable para detectar colisiones

        for (int i = 0; i < 8; ++i) {
            int xTanque = grafo->getPosicionX(tanques[i]->obtenerNodoActual());
            int yTanque = grafo->getPosicionY(tanques[i]->obtenerNodoActual());

            if (balaActual->verificarColisionConTanque(xTanque, yTanque)) {
                //std::cout << "¡Colisión detectada con el tanque " << i << "!" << std::endl;

                if (tanques[i] != nullptr && tanques[i]->estaVivo()) {

                    // Reducir la vida del tanque según el color
                    if (i == 4 || i == 5 || i == 6 || i == 7) {
                        // Tanques azules y celestes (vida disminuye 25%)
                        tanques[i]->reducirVida(25);
                        std::cout << "25% de vida perdida para el tanque " << i << std::endl;
                    } else {
                        // Tanques rojos y amarillos (vida disminuye 50%)
                        tanques[i]->reducirVida(50);
                        std::cout << "50% de vida perdida para el tanque " << i << std::endl;
                    }

                    // Mostrar la vida restante del tanque
                    std::cout << "Vida restante del tanque " << i << ": " << tanques[i]->obtenerVida() << "%" << std::endl;

                    // Verificar si el tanque debe ser eliminado
                    if (!tanques[i]->estaVivo()) {
                        std::cout << "El tanque " << i << " ha sido destruido!" << std::endl;
                        tanques[i] = nullptr;  // Eliminar el tanque (marcarlo como nulo)
                    }

                    // Marcar que se ha detectado una colisión
                    colisionDetectada = true;
                }

                // No rompemos el bucle inmediatamente, dejamos que se actualice la pantalla
            }
        }

        // Si hay colisión, gestionamos el final del turno tras la actualización
        if (colisionDetectada) {
            balaActual->setActiva(false);  // Marcar la bala como inactiva
            balaTimer->stop();  // Detener el temporizador de movimiento de la bala
            siguienteTurno();  // Cambiar al siguiente turno
        }

        // Si la bala ha terminado su camino sin colisión
        if (balaActual->haTerminadoCamino() && !colisionDetectada) {
            std::cout << "Bala ha llegado al destino sin colisión." << std::endl;
            balaTimer->stop();  // Detener el temporizador
            siguienteTurno();   // Cambiar al siguiente turno
        }

        // Aseguramos la actualización de la pantalla en cada paso
        update();
    }
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
    if (tanqueAmarillo1 && tanqueAmarillo1->estaVivo() && tanqueAmarillo1->getCamino() != nullptr) {
        pen.setColor(Qt::yellow);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueAmarillo1, painter);
    }

    if (tanqueAmarillo2 && tanqueAmarillo2->estaVivo() && tanqueAmarillo2->getCamino() != nullptr) {
        pen.setColor(Qt::yellow);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueAmarillo2, painter);
    }

    if (tanqueAzul1 && tanqueAzul1->estaVivo() && tanqueAzul1->getCamino() != nullptr) {
        pen.setColor(Qt::blue);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueAzul1, painter);
    }

    if (tanqueAzul2 && tanqueAzul2->estaVivo() && tanqueAzul2->getCamino() != nullptr) {
        pen.setColor(Qt::blue);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueAzul2, painter);
    }

     if (tanqueCeleste1 && tanqueCeleste1->estaVivo() && tanqueCeleste1->getCamino() != nullptr) {
        pen.setColor(Qt::cyan);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueCeleste1, painter);
    }

    if (tanqueCeleste2 && tanqueCeleste2->estaVivo() && tanqueCeleste2->getCamino() != nullptr) {
        pen.setColor(Qt::cyan);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueCeleste2, painter);
    }

    if (tanqueRojo1 && tanqueRojo1->estaVivo() && tanqueRojo1->getCamino() != nullptr) {
        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueRojo1, painter);
    }

    if (tanqueRojo2 && tanqueRojo2->estaVivo() && tanqueRojo2->getCamino() != nullptr) {
        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        dibujarCamino(tanqueRojo2, painter);
    }

    // Dibujar tanques
    if (tanqueAmarillo1 && tanqueAmarillo1->estaVivo()) dibujarTanque(tanqueAmarillo1, imgTanqueAmarillo, painter);
    if (tanqueAmarillo2 && tanqueAmarillo2->estaVivo()) dibujarTanque(tanqueAmarillo2, imgTanqueAmarillo, painter);
    if (tanqueAzul1 && tanqueAzul1->estaVivo()) dibujarTanque(tanqueAzul1, imgTanqueAzul, painter);
    if (tanqueAzul2 && tanqueAzul2->estaVivo()) dibujarTanque(tanqueAzul2, imgTanqueAzul, painter);
    if (tanqueCeleste1 && tanqueCeleste1->estaVivo()) dibujarTanque(tanqueCeleste1, imgTanqueCeleste, painter);
    if (tanqueCeleste2 && tanqueCeleste2->estaVivo()) dibujarTanque(tanqueCeleste2, imgTanqueCeleste, painter);
    if (tanqueRojo1 && tanqueRojo1->estaVivo()) dibujarTanque(tanqueRojo1, imgTanqueRojo, painter);
    if (tanqueRojo2 && tanqueRojo2->estaVivo()) dibujarTanque(tanqueRojo2, imgTanqueRojo, painter);

    // Dibujar camino de la bala
    if (balaActual && balaActual->estaActiva()) {
        // Seleccionar color según el tanque en turno
        switch (turnoActual) {
        case 0:
        case 4: pen.setColor(Qt::red); break;  // Tanques rojos
        case 1:
        case 5: pen.setColor(Qt::yellow); break;  // Tanques amarillos
        case 2:
        case 6: pen.setColor(Qt::blue); break;  // Tanques azules
        case 3:
        case 7: pen.setColor(Qt::cyan); break;  // Tanques celestes
        }

        pen.setWidth(2);
        painter.setPen(pen);

        // Dibujar las aristas del camino de la bala
        for (int i = 0; i < balaActual->getLongitudCamino() - 1; ++i) {
            int nodo1 = balaActual->getCamino()[i];
            int nodo2 = balaActual->getCamino()[i + 1];

            int x1 = grafo->getPosicionX(nodo1);
            int y1 = grafo->getPosicionY(nodo1);
            int x2 = grafo->getPosicionX(nodo2);
            int y2 = grafo->getPosicionY(nodo2);

            painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
        }

        // Dibujar la bala en su posición actual
        dibujarBala(painter);
    }
}

void GrafoWidget::dibujarCamino(Tanque* tanque, QPainter& painter) {

    if (!tanque || !tanque->estaVivo()) {
        return;  // No dibujar si el tanque no existe o está destruido
    }

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
    if (tanque == nullptr || !tanque->estaVivo()) {
        std::cerr << "Error: El tanque está eliminado, no se puede dibujar." << std::endl;
        return;  // Evitar dibujar si el tanque es nulo
    }
    int x = grafo->getPosicionX(tanque->obtenerNodoActual());
    int y = grafo->getPosicionY(tanque->obtenerNodoActual());
    painter.drawPixmap(x - imagenTanque.width() / 2, y - imagenTanque.height() / 2, imagenTanque);
}

void GrafoWidget::moverTanquePasoAPaso() {
    if(accionRealizada) return;// Impedir movimiento si ya se realizó una acción
    // Mueve el tanque del turno actual paso a paso hasta que complete su camino
    bool mover = false;

    switch (turnoActual) {
    case 0:  // Tanque rojo 1
        if (tanqueRojo1 != nullptr && tanqueRojo1->estaVivo() && tanqueRojo1->getCamino() != nullptr && !tanqueRojo1->haTerminadoCamino()) {
            tanqueRojo1->avanzarCaminoPaso();  // Avanza un paso en el camino
            mover = true;
        }
        break;
    case 1:  // Tanque rojo 2
        if (tanqueAmarillo1 != nullptr && tanqueAmarillo1->estaVivo() && tanqueAmarillo1->getCamino() != nullptr && !tanqueAmarillo1->haTerminadoCamino()) {
            tanqueAmarillo1->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 2:  // Tanque azul 1
        if (tanqueAzul1 != nullptr && tanqueAzul1->estaVivo() && tanqueAzul1->getCamino() != nullptr && !tanqueAzul1->haTerminadoCamino()) {
            tanqueAzul1->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 3:  // Tanque azul 2
        if (tanqueCeleste1 != nullptr && tanqueCeleste1->estaVivo() && tanqueCeleste1->getCamino() != nullptr && !tanqueCeleste1->haTerminadoCamino()) {
            tanqueCeleste1->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 4:  // Tanque amarillo 1
        if (tanqueRojo2 != nullptr && tanqueRojo2->estaVivo() && tanqueRojo2->getCamino() != nullptr && !tanqueRojo2->haTerminadoCamino()) {
            tanqueRojo2->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 5:  // Tanque celeste 1
        if (tanqueAmarillo2 != nullptr && tanqueAmarillo2->estaVivo() && tanqueAmarillo2->getCamino() != nullptr && !tanqueAmarillo2->haTerminadoCamino()) {
            tanqueAmarillo2->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 6:  // Tanque amarillo 2
        if (tanqueAzul2 != nullptr && tanqueAzul2->estaVivo() && tanqueAzul2->getCamino() != nullptr && !tanqueAzul2->haTerminadoCamino()) {
            tanqueAzul2->avanzarCaminoPaso();
            mover = true;
        }
        break;
    case 7:  // Tanque celeste 2
        if (tanqueCeleste2 != nullptr && tanqueCeleste2->estaVivo() && tanqueCeleste2->getCamino() != nullptr && !tanqueCeleste2->haTerminadoCamino()) {
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


Tanque* GrafoWidget::obtenerTanqueActual() {
    switch (turnoActual) {
    case 0: return tanqueRojo1;
    case 1: return tanqueAmarillo1;
    case 2: return tanqueAzul1;
    case 3: return tanqueCeleste1;
    case 4: return tanqueRojo2;
    case 5: return tanqueAmarillo2;
    case 6: return tanqueAzul2;
    case 7: return tanqueCeleste2;
    default: return nullptr;  // En caso de que haya un error, devuelve nullptr
    }
}



void GrafoWidget::mousePressEvent(QMouseEvent *event) {
    if (!grafo || accionRealizada) return;  // No permitir más acciones si ya se realizó una acción

    int clickX = static_cast<int>(event->position().x());
    int clickY = static_cast<int>(event->position().y());

    int nodoCercano = grafo->encontrarNodoCercano(clickX, clickY);

    if (event->button() == Qt::LeftButton) {  // Click izquierdo para moverse
        if (nodoCercano != -1) {
            std::cout << "Nodo cercano seleccionado (click izquierdo): " << nodoCercano << std::endl;

            if (seleccionInicial) {
                if (validarSeleccionInicial(nodoCercano) && obtenerTanqueActual()->estaVivo()) {
                    nodoInicial = nodoCercano;
                    seleccionInicial = false;
                    std::cout << "Nodo inicial seleccionado para el tanque en turno " << turnoActual << std::endl;
                } else {
                    std::cout << "El nodo seleccionado no corresponde al tanque en turno o el tanque está destruido." << std::endl;
                }
            } else {
                nodoFinal = nodoCercano;
                std::cout << "Nodo final seleccionado (click izquierdo): " << nodoFinal << std::endl;

                if (obtenerTanqueActual()->estaVivo()) {
                    moverTanqueActual();  // Iniciar el movimiento del tanque en turno
                    movimientoTimer->start(500);  // Iniciar el temporizador para mover el tanque cada 500 ms
                } else {
                    std::cout << "No se puede mover el tanque, está destruido." << std::endl;
                }
            }

            update();  // Redibujar la ventana
        }
    } else if (event->button() == Qt::RightButton) {  // Click derecho para disparar
        std::cout << "Click derecho para disparar detectado en: (" << clickX << ", " << clickY << ")" << std::endl;

        if (!seleccionDisparo) {  // Selección inicial para disparar
            if (nodoCercano != -1 && validarSeleccionInicial(nodoCercano) && obtenerTanqueActual()->estaVivo()) {
                seleccionDisparo = true;  // Marcar como en proceso de disparo
                std::cout << "Seleccionado tanque en turno para disparar." << std::endl;
            } else {
                std::cout << "No se seleccionó un tanque válido para disparar o el tanque está destruido." << std::endl;
            }
        } else {  // Seleccionar el objetivo para disparar
            dispararBala(clickX, clickY);  // Iniciar el disparo hacia la posición seleccionada
            accionRealizada = true;  // Marca la acción como realizada
            seleccionDisparo = false;  // Restablecer la selección de disparo
        }
    }
}


int GrafoWidget::calcularCamino(int xInicial, int yInicial, int xObjetivo, int yObjetivo, int camino[]) {

    // Verificar si el tanque actual está vivo
    Tanque* tanqueActual = obtenerTanqueActual();
    if (tanqueActual == nullptr || !tanqueActual->estaVivo()) {
        std::cout << "Error: El tanque en turno está destruido o no es válido." << std::endl;
        return 0;  // No calcular camino si el tanque está destruido
    }

    int index = 0;

    // Diferencia en las coordenadas
    int dx = std::abs(xObjetivo - xInicial);
    int dy = std::abs(yObjetivo - yInicial);

    // Determinar la dirección del avance
    int sx = (xInicial < xObjetivo) ? 1 : -1;
    int sy = (yInicial < yObjetivo) ? 1 : -1;

    // Variables para el algoritmo de Bresenham
    int err = dx - dy;

    // Inicialmente se coloca el nodo inicial en el camino
    camino[index++] = grafo->encontrarNodoCercano(xInicial, yInicial);  // Nodo inicial

    // Algoritmo de Bresenham para trazar una línea
    while (xInicial != xObjetivo || yInicial != yObjetivo) {
        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            xInicial += sx;
        }

        if (e2 < dx) {
            err += dx;
            yInicial += sy;
        }

        // Agregar el nodo más cercano al nuevo punto
        int nodoCercano = grafo->encontrarNodoCercano(xInicial, yInicial);

        // Si el nodo ya está en el camino, evitar duplicados
        if (index == 0 || camino[index - 1] != nodoCercano) {
            camino[index++] = nodoCercano;
        }

        // Si el nodo objetivo se alcanza, romper el ciclo
        if (nodoCercano == grafo->encontrarNodoCercano(xObjetivo, yObjetivo)) {
            break;
        }
    }

    return index;  // Retornar el número de nodos en el camino
}



void GrafoWidget::dispararBala(int xObjetivo, int yObjetivo) {
    // Obtener la posición actual del tanque en turno
    Tanque* tanqueEnTurno = nullptr;

    switch (turnoActual) {
    case 0: tanqueEnTurno = tanqueRojo1; break;
    case 1: tanqueEnTurno = tanqueAmarillo1; break;
    case 2: tanqueEnTurno = tanqueAzul1; break;
    case 3: tanqueEnTurno = tanqueCeleste1; break;
    case 4: tanqueEnTurno = tanqueRojo2; break;
    case 5: tanqueEnTurno = tanqueAmarillo2; break;
    case 6: tanqueEnTurno = tanqueAzul2; break;
    case 7: tanqueEnTurno = tanqueCeleste2; break;
    }

    if (tanqueEnTurno == nullptr || !tanqueEnTurno->estaVivo()) {
        std::cout << "Error: El tanque en turno está destruido o no es válido. No puede disparar." << std::endl;
        return;  // No disparar si el tanque está destruido
    } else {
        int xInicial = grafo->getPosicionX(tanqueEnTurno->obtenerNodoActual());
        int yInicial = grafo->getPosicionY(tanqueEnTurno->obtenerNodoActual());

        std::cout << "Disparando bala desde (" << xInicial << ", " << yInicial
                  << ") hacia (" << xObjetivo << ", " << yObjetivo << ")" << std::endl;

        // Calcular el camino con el algoritmo de línea de vista (o el que estés usando)
        int camino[100]; // Un array de tamaño fijo para almacenar el camino
        int longitudCamino = calcularCamino(xInicial, yInicial, xObjetivo, yObjetivo, camino);  // Debes tener este método para obtener el camino

        // Crear la bala con la ruta calculada
        balaActual = new Bala(xInicial, yInicial, xObjetivo, yObjetivo, camino, longitudCamino);

        balaTimer->start(50);  // Iniciar el movimiento de la bala
    }
}



bool GrafoWidget::validarSeleccionInicial(int nodoCercano) {
    // Validar si el nodo pertenece al tanque en turno, si corresponde al turno actual y si está vivo
    switch (turnoActual) {
    case 0: return tanqueRojo1 != nullptr && tanqueRojo1->estaVivo() && nodoCercano == tanqueRojo1->obtenerNodoActual();  // Jugador 1, tanque rojo 1
    case 1: return tanqueAmarillo1 != nullptr && tanqueAmarillo1->estaVivo() && nodoCercano == tanqueAmarillo1->obtenerNodoActual();  // Jugador 2, tanque amarillo 1
    case 2: return tanqueAzul1 != nullptr && tanqueAzul1->estaVivo() && nodoCercano == tanqueAzul1->obtenerNodoActual();  // Jugador 1, tanque azul 1
    case 3: return tanqueCeleste1 != nullptr && tanqueCeleste1->estaVivo() && nodoCercano == tanqueCeleste1->obtenerNodoActual();  // Jugador 2, tanque celeste 1
    case 4: return tanqueRojo2 != nullptr && tanqueRojo2->estaVivo() && nodoCercano == tanqueRojo2->obtenerNodoActual();  // Jugador 1, tanque rojo 2
    case 5: return tanqueAmarillo2 != nullptr && tanqueAmarillo2->estaVivo() && nodoCercano == tanqueAmarillo2->obtenerNodoActual();  // Jugador 2, tanque amarillo 2
    case 6: return tanqueAzul2 != nullptr && tanqueAzul2->estaVivo() && nodoCercano == tanqueAzul2->obtenerNodoActual();  // Jugador 1, tanque azul 2
    case 7: return tanqueCeleste2 != nullptr && tanqueCeleste2->estaVivo() && nodoCercano == tanqueCeleste2->obtenerNodoActual();  // Jugador 2, tanque celeste 2
    default: return false;
    }
}



void GrafoWidget::moverTanqueActual() {
    switch (turnoActual) {
    case 0:  // Tanque rojo 1
        if (tanqueRojo1 != nullptr && tanqueRojo1->estaVivo()) {
            tanqueRojo1->setNodoObjetivo(nodoFinal);
            tanqueRojo1->mover();  // Calcular el camino usando Dijkstra
        }
        break;
    case 1:  // Tanque amarillo 1
        if (tanqueAmarillo1 != nullptr && tanqueAmarillo1->estaVivo()) {
            tanqueAmarillo1->setNodoObjetivo(nodoFinal);
            tanqueAmarillo1->mover();
        }
        break;
    case 2:  // Tanque azul 1
        if (tanqueAzul1 != nullptr && tanqueAzul1->estaVivo()) {
            tanqueAzul1->setNodoObjetivo(nodoFinal);
            tanqueAzul1->mover();
        }
        break;
    case 3:  // Tanque celeste 1
        if (tanqueCeleste1 != nullptr && tanqueCeleste1->estaVivo()) {
            tanqueCeleste1->setNodoObjetivo(nodoFinal);
            tanqueCeleste1->mover();
        }
        break;
    case 4:  // Tanque rojo 2
        if (tanqueRojo2 != nullptr && tanqueRojo2->estaVivo()) {
            tanqueRojo2->setNodoObjetivo(nodoFinal);
            tanqueRojo2->mover();
        }
        break;
    case 5:  // Tanque amarillo 2
        if (tanqueAmarillo2 != nullptr && tanqueAmarillo2->estaVivo()) {
            tanqueAmarillo2->setNodoObjetivo(nodoFinal);
            tanqueAmarillo2->mover();
        }
        break;
    case 6:  // Tanque azul 2
        if (tanqueAzul2 != nullptr && tanqueAzul2->estaVivo()) {
            tanqueAzul2->setNodoObjetivo(nodoFinal);
            tanqueAzul2->mover();
        }
        break;
    case 7:  // Tanque celeste 2
        if (tanqueCeleste2 != nullptr && tanqueCeleste2->estaVivo()) {
            tanqueCeleste2->setNodoObjetivo(nodoFinal);
            tanqueCeleste2->mover();
        }
        break;
    }

    // Cambiar el turno después de mover
    movimientoTimer->start(500);  // Comenzar el temporizador para mover el tanque paso a paso
}



void GrafoWidget::siguienteTurno() {
    std::cout << "Cambiando turno..." << std::endl;

    // Limpiar el camino del tanque en turno actual antes de pasar al siguiente turno
    switch (turnoActual) {
    case 0:  // Tanque rojo 1
        if (tanqueRojo1 != nullptr && tanqueRojo1->estaVivo()) {
            tanqueRojo1->limpiarCamino();
        }
        break;
    case 1:  // Tanque amarillo 1
        if (tanqueAmarillo1 != nullptr && tanqueAmarillo1->estaVivo()) {
            tanqueAmarillo1->limpiarCamino();
        }
        break;
    case 2:  // Tanque azul 1
        if (tanqueAzul1 != nullptr && tanqueAzul1->estaVivo()) {
            tanqueAzul1->limpiarCamino();
        }
        break;
    case 3:  // Tanque celeste 1
        if (tanqueCeleste1 != nullptr && tanqueCeleste1->estaVivo()) {
            tanqueCeleste1->limpiarCamino();
        }
        break;
    case 4:  // Tanque rojo 2
        if (tanqueRojo2 != nullptr && tanqueRojo2->estaVivo()) {
            tanqueRojo2->limpiarCamino();
        }
        break;
    case 5:  // Tanque amarillo 2
        if (tanqueAmarillo2 != nullptr && tanqueAmarillo2->estaVivo()) {
            tanqueAmarillo2->limpiarCamino();
        }
        break;
    case 6:  // Tanque azul 2
        if (tanqueAzul2 != nullptr && tanqueAzul2->estaVivo()) {
            tanqueAzul2->limpiarCamino();
        }
        break;
    case 7:  // Tanque celeste 2
        if (tanqueCeleste2 != nullptr && tanqueCeleste2->estaVivo()) {
            tanqueCeleste2->limpiarCamino();
        }
        break;
    }

    // Cambiar turno y verificar si el tanque está vivo para asegurar que un tanque destruido no tome un turno
    do {
        turnoActual = (turnoActual + 1) % 8;  // Cambiar entre los 8 tanques
    } while ((obtenerTanqueActual() == nullptr || !obtenerTanqueActual()->estaVivo()) && turnoActual != 0);

    // Jugador 1 mueve en turnos 0, 2, 4, 6 (pares)
    // Jugador 2 mueve en turnos 1, 3, 5, 7 (impares)
    jugadorActual = (turnoActual % 2 == 0) ? 0 : 1;  // Jugador 1 para pares, Jugador 2 para impares

    nodoInicial = -1;
    nodoFinal = -1;
    seleccionInicial = true;
    accionRealizada = false;  // Resetear para el próximo turno
    seleccionDisparo = false;  // Resetear selección de disparo
    std::cout << "Cambio al turno del tanque: " << turnoActual << " (Jugador " << jugadorActual + 1 << ")" << std::endl;
    update();
}

