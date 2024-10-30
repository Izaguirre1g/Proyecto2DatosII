#include "GrafoWidget.h"
#include "Bala.h"
#include "AStar.h"
#include "Tanque.h"
#include "LineOfSight.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <iostream>
#include <QKeyEvent>
using namespace std;

GrafoWidget::GrafoWidget(QWidget *parent)
    : QWidget(parent), textoCambiante1("Bienvenidos al Juego"), textoCambiante2("Bienvenidos al Juego"),
    grafo(nullptr), seleccionInicial(true), turnoActual(0), nodoInicial(-1), nodoFinal(-1),
    jugadorActual(0), accionRealizada(false), contadorTurnos(1), poderDeAtaqueActivado(false) {  // Inicializa accionRealizada en false

    // Inicialización
    powerUpsJugador1 = tipoPowersUp();  // Asignar lista de power-ups al Jugador 1
    powerUpsJugador2 = tipoPowersUp();  // Asignar lista de power-ups al Jugador 2

    while(listasSonIguales(powerUpsJugador1,powerUpsJugador2,4)){
        delete[] powerUpsJugador2; //Libera(elimina) la lsita si es igual
        powerUpsJugador2 = tipoPowersUp();//Genera una nueva lista para el jugador 2
    }
    precisionDeAtaqueActivado = false;


    // Cargar las imágenes de los tanques y otras configuraciones
    imgTanqueAmarillo.load(":Imagenes/Amarillo.png");
    imgTanqueAzul.load(":Imagenes/Azul.png");
    imgTanqueCeleste.load(":Imagenes/Celeste.png");
    imgTanqueRojo.load(":Imagenes/Rojo.png");

    // Chequeo de imágenes
    if (imgTanqueAmarillo.isNull()) std::cerr << "Error al cargar la imagen del tanque amarillo\n";
    if (imgTanqueAzul.isNull()) std::cerr << "Error al cargar la imagen del tanque azul\n";
    if (imgTanqueCeleste.isNull()) std::cerr << "Error al cargar la imagen del tanque celeste\n";
    if (imgTanqueRojo.isNull()) std::cerr << "Error al cargar la imagen del tanque rojo\n";

    setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

    movimientoTimer = new QTimer(this);
    connect(movimientoTimer, &QTimer::timeout, this, &GrafoWidget::moverTanquePasoAPaso);

    balaTimer = new QTimer(this);
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
        balaActual->avanzarCaminoPaso(grafo);  // Mueve la bala

        update();  // Actualizar la interfaz en cada paso

        // Obtener el tanque que dispara la bala (para evitar autocolisión)
        Tanque* tanqueAtacante = obtenerTanqueActual();

        // Arreglo de tanques
        Tanque* tanques[8] = {tanqueRojo1, tanqueAmarillo1, tanqueAzul1, tanqueCeleste1,
                              tanqueRojo2, tanqueAmarillo2, tanqueAzul2, tanqueCeleste2};

        bool colisionDetectada = false;

        for (int i = 0; i < 8; ++i) {
            if (tanques[i] != nullptr && tanques[i]->estaVivo() && tanques[i] != tanqueAtacante) {
                int xTanque = grafo->getPosicionX(tanques[i]->obtenerNodoActual());
                int yTanque = grafo->getPosicionY(tanques[i]->obtenerNodoActual());

                if (balaActual->verificarColisionConTanque(xTanque, yTanque)) {
                    int vidaReducida = 0;

                    // Verifica si el power-up de ataque está activado
                    if (poderDeAtaqueActivado) {
                        vidaReducida = 120;
                        poderDeAtaqueActivado = false;
                        std::cout << "Poder de ataque activado. 120% de vida reducida." << std::endl;
                    } else {
                        vidaReducida = (i == 2 || i == 3 || i == 6 || i == 7) ? 25 : 50;
                    }

                    tanques[i]->reducirVida(vidaReducida);  // Aplicar daño
                    std::cout << vidaReducida << "% de vida perdida para el tanque " << i << std::endl;
                    std::cout << "Vida restante del tanque " << i << ": " << tanques[i]->obtenerVida() << "%" << std::endl;

                    if (!tanques[i]->estaVivo()) {
                        std::cout << "El tanque " << i << " ha sido destruido!" << std::endl;
                        tanques[i] = nullptr;  // Marcar el tanque como destruido
                    }

                    colisionDetectada = true;
                }
            }
        }

        // Si hay colisión con un tanque o si la bala ha terminado el camino, cambiar de turno
        if (colisionDetectada || balaActual->haTerminadoCamino()) {
            balaActual->setActiva(false);
            balaTimer->stop();
            siguienteTurno(false,-10);
            return;
        }

        // Comprobar colisiones con obstáculos
        if (!balaActual->estaActiva()) {
            balaTimer->stop();  // Detener el temporizador de movimiento de la bala
            siguienteTurno(false,-10);   // Cambiar al siguiente turno
            return;
        }

        // Actualizar la interfaz después de cada movimiento
        update();
    }
}




void GrafoWidget::paintEvent(QPaintEvent *event) {
    if (!grafo) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);



    // Dimensiones del mapa
    int ancho = 1050;  // Ancho total del mapa
    int alto = 720;    // Alto total del mapa
    int espaciado = 50;  // Espaciado entre nodos
    int numNodos = (ancho / espaciado) * (alto / espaciado);  // Número total de nodos

    // Definir el rango central donde los obstáculos pueden aparecer
    int anchoLateral = ancho / 4;  // Dividimos el ancho en 4 partes, los laterales ocupan 1/4 cada uno
    int margenIzquierdo = anchoLateral;           // Empieza donde termina la franja izquierda
    int margenDerecho = ancho - anchoLateral;     // Termina donde empieza la franja derecha

    // Dibujar el fondo
    QPixmap background(":Imagenes/battlefield.jpg");
    if (!background.isNull()) {
        painter.drawPixmap(0, 0, width(), height(), background);
    }

    // Dibujar obstáculos (nodos bloqueados) solo en la franja central
    painter.setBrush(Qt::black);  // Color negro para los obstáculos
    painter.setPen(Qt::NoPen);    // Sin borde para los obstáculos

    for (int i = 0; i < grafo->obtenerNumNodos(); ++i) {
        if (grafo->nodosBloqueados[i]) {
            int x = grafo->getPosicionX(i);  // Obtener posición X del nodo
            int y = grafo->getPosicionY(i);  // Obtener posición Y del nodo

            // Verificar si el nodo está dentro de la franja central
            if (x >= margenIzquierdo && x <= margenDerecho) {
                int tamanoObstaculo = 40;  // Ajusta el tamaño del obstáculo según sea necesario

                // Dibujar un cuadrado para representar el obstáculo
                QRect cuadrado(x - tamanoObstaculo / 2, y - tamanoObstaculo / 2, tamanoObstaculo, tamanoObstaculo);
                painter.drawRect(cuadrado);
            }
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
    // Configurar el tipo de letra
    QFont font = painter.font();
    font.setPointSize(32);  // Tamaño de letra grande para el mensaje
    font.setBold(true);     // Hacer el texto negrita
    painter.setFont(font);

    // Dibujar el mensaje de bienvenida
    painter.setPen(Qt::cyan);  // Color para el texto
    QString powerups_text = "Power-ups!";
    painter.drawText(1040, 40, powerups_text);  // Centrando el texto

    font.setPointSize(16);// Tamaño de letra más pequeño
    painter.setFont(font);// Aplicar el nuevo tamaño de letra
    QString jugador1="Jugador 1";
    painter.drawText(1090, 80, jugador1);

    QString jugador2="Jugador 2";
    painter.drawText(1090, 290, jugador2);

    // Definir el rectángulo donde se dibujará el texto cambiante
    QRect rectanguloTexto1(1000, 100, 300, 100);  // (x, y, ancho, alto)

    // Dibujar el rectángulo
    painter.setBrush(Qt::lightGray);  // Color de fondo del rectángulo
    painter.drawRect(rectanguloTexto1);

    // Configurar el tipo de letra

    font.setPointSize(16);  // Tamaño de letra para el texto
    painter.setFont(font);

    // Establecer el color del texto
    painter.setPen(Qt::black);

    // Dibujar el texto en el centro del rectángulo
    painter.drawText(rectanguloTexto1, Qt::AlignCenter, textoCambiante1);

    QRect rectanguloTexto2(1000, 300, 300, 100);  // Otra posición (x, y, ancho, alto)
    painter.setBrush(Qt::lightGray);  // Color de fondo
    painter.drawRect(rectanguloTexto2);  // Dibujar el segundo rectángulo

    font.setPointSize(16);  // Tamaño de letra más pequeño para el segundo cuadro
    painter.setFont(font);
    painter.setPen(Qt::black);  // Color del texto
    painter.drawText(rectanguloTexto2, Qt::AlignCenter, textoCambiante2);  // Dibujar el texto en el segundo rectángulo


}


//Se encarga de verificar si ya es momento de generar un nueva lista
bool GrafoWidget::listaLlenaDeCeros(int* lista) {
    for (int i = 0; i < 4; ++i) {
        if (lista[i] != 0) {
            return false;
        }
    }
    return true;
}

//Funcion que verifica si son iguales las listas para evitar los mismos powerups
bool GrafoWidget::listasSonIguales(int* lista1, int* lista2, int size){
    for(int i = 0; i<size; i++){
        if(lista1[i] != lista2[i]){
            return false; //Las listas son diferentes
        }
    }
    return true; //Las listas son iguales
}

//Funcion auxiliar
bool GrafoWidget::existeEnArreglo(int arr[], int size, int valor) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == valor) {
            return true;
        }
    }
    return false;
}

//Genera una lista del 1 al 4, cada numero esta relacionado a un power-up, solo que los genera de forma aleatoria
int* GrafoWidget::tipoPowersUp(){
    int* lista= new int[4];
    for (int i = 0; i < 4; ++i) {
        lista[i] = 0;  // Inicializar en 0
    }

    srand(static_cast<unsigned>(time(0)));

    for(int i =0; i<4; i++){
        int num;
        do{
            num=rand()%4+1;
        }while(existeEnArreglo(lista, 4, num));
        lista[i] = num;
    }
    return lista;
}



void GrafoWidget::startTurn() {
    if (dobleturnoActivado) {
        dobleturnoDisponible = true;
        dobleturnoActivado = false;  // El power-up ya fue activado, así que lo desactivamos
    }
}



//Detecta el uso de la tecla Shift
void GrafoWidget::keyPressEvent(QKeyEvent *event) {
    if (accionRealizada) return;  // No permitir más acciones si ya se realizó una

    if (event->key() == Qt::Key_Shift) {
        std::cout << "Shift presionado por el jugador " << (jugadorActual + 1) << std::endl;

        int* powerUpsActual;  // Lista de power-ups del jugador actual

        if (jugadorActual == 0) {
            powerUpsActual = powerUpsJugador1;
            if (listaLlenaDeCeros(powerUpsJugador1)) {
                delete[] powerUpsJugador1;
                powerUpsJugador1 = tipoPowersUp();
            }
        } else {
            powerUpsActual = powerUpsJugador2;
            if (listaLlenaDeCeros(powerUpsJugador2)) {
                delete[] powerUpsJugador2;
                powerUpsJugador2 = tipoPowersUp();
            }
        }

        // Verificar el primer power-up disponible
        for (int i = 0; i < 4; ++i) {
            if (powerUpsActual[i] != 0) {
                int powerUp = powerUpsActual[i];
                powerUpsActual[i] = 0;  // Marcar como usado

                // Registrar el power-up para aplicarlo en el próximo turno del jugador
                if (jugadorActual == 0) {
                    powerUpPendienteJugador1 = powerUp;
                } else {
                    powerUpPendienteJugador2 = powerUp;
                }

                std::cout << "Power-up " << powerUp << " pendiente para el Jugador " << jugadorActual + 1 << std::endl;

                accionRealizada = true;  // Marcar acción como realizada
                siguienteTurno(false, -10);  // Cambiar turno
                return;
            }
        }
    }
    QWidget::keyPressEvent(event);
}


//Se encarga de mostrar el camino de aristas
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
        return;  // Evitar dibujar si el tanque es nulo o está destruido
    }

    int x = grafo->getPosicionX(tanque->obtenerNodoActual());
    int y = grafo->getPosicionY(tanque->obtenerNodoActual());

    // Dibuja la imagen del tanque
    painter.drawPixmap(x - imagenTanque.width() / 2, y - imagenTanque.height() / 2, imagenTanque);

    // Obtener la vida del tanque y dibujarla encima del tanque
    int vida = tanque->obtenerVida();  // Obtener el porcentaje de vida del tanque

    // Configurar el estilo del texto
    QFont font = painter.font();
    font.setPointSize(16);  // Tamaño de letra pequeño
    painter.setFont(font);
    painter.setPen(Qt::yellow);  // Color blanco para la vida

    // Dibujar el porcentaje de vida sobre el tanque
    QString vidaTexto = QString::number(vida) + "%";
    int anchoTexto = painter.fontMetrics().horizontalAdvance(vidaTexto);  // Ancho del texto
    // Dibujar el porcentaje de vida centrado sobre el tanque
    painter.drawText(x - anchoTexto / 2, y - imagenTanque.height() / 2 - 10, vidaTexto);
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
        siguienteTurno(false,-10);  // Cambiar al siguiente turno
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
        //Colocar el contador para las veces que pulsa el clic
        contadorTurnos+=1;

        cout <<contadorTurnos<<endl;
        if (nodoCercano != -1) {
            std::cout << "Nodo cercano seleccionado (click izquierdo): " << nodoCercano << std::endl;

            if (seleccionInicial) {
                if (validarSeleccionInicial(nodoCercano) && obtenerTanqueActual()->estaVivo()) {

                    nodoInicial = nodoCercano;
                    seleccionInicial = false;
                    std::cout << "Nodo inicial seleccionado para el tanque en turno " << turnoActual << std::endl;
                }else if(validarSeleccionInicial(nodoCercano) && obtenerTanqueActual()->estaVivo() && dobleturnoActivado){

                    nodoInicial = nodoCercano;
                    seleccionInicial = false;
                    std::cout << "Nodo inicial seleccionado para el tanque en turno " << turnoActual << std::endl;
                }
                else {
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
        //Colocar el contador para las veces que pulsa el clic
        contadorTurnos+=1;
        cout <<contadorTurnos<<endl;

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

//bool precisionDeAtaqueActivado = false;  // Bandera para saber si el power-up de precisión de ataque está activo

void GrafoWidget::activarPrecisionAtaque(int xObjetivo, int yObjetivo) {
    std::cout << "Activando Power-Up: Precisión de Ataque" << std::endl;
    precisionDeAtaqueActivado = true;  // Activamos la precisión de ataque
}

int* GrafoWidget::obtenerCaminoAEstrella(int nodoInicial, int nodoFinal, int& longitudCamino) {
    // Llama a la función aEstrella para obtener el camino
    return aEstrella(*grafo, nodoInicial, nodoFinal, longitudCamino);
}

void GrafoWidget::dispararBala(int xObjetivo, int yObjetivo) {
    if (accionRealizada) return;  // No permitir disparar si ya se hizo una acción

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
    }

    // Posiciones iniciales del tanque
    int xInicial = grafo->getPosicionX(tanqueEnTurno->obtenerNodoActual());
    int yInicial = grafo->getPosicionY(tanqueEnTurno->obtenerNodoActual());

    std::cout << "Disparando bala desde (" << xInicial << ", " << yInicial
              << ") hacia (" << xObjetivo << ", " << yObjetivo << ")" << std::endl;

    // Array para almacenar el camino
    int camino[100];
    int longitudCamino = 0;

    // Aquí agregamos la verificación de si se está usando el power-up de precisión de ataque
    if (precisionDeAtaqueActivado) {
        std::cout << "Usando A* para calcular el camino de la bala." << std::endl;
        // Usar A* para calcular el camino desde el nodo inicial al nodo objetivo
        int nodoInicial = grafo->encontrarNodoCercano(xInicial, yInicial);
        int nodoFinal = grafo->encontrarNodoCercano(xObjetivo, yObjetivo);
        int* caminoAEstrella = aEstrella(*grafo, nodoInicial, nodoFinal, longitudCamino);

        // Copiar el camino de A* al array 'camino'
        for (int i = 0; i < longitudCamino && i < 100; ++i) {
            camino[i] = caminoAEstrella[i];
        }

        delete[] caminoAEstrella;  // Liberar memoria asignada por A*

        // Desactivar el power-up de precisión de ataque después de usarlo
        precisionDeAtaqueActivado = false;
    } else {
        // Usar línea de visión si el power-up no está activado
        std::cout << "Usando línea de visión para el disparo." << std::endl;
        longitudCamino = calcularCamino(xInicial, yInicial, xObjetivo, yObjetivo, camino);  // Usar el cálculo existente
    }

    // Crear la bala con la ruta calculada
    balaActual = new Bala(xInicial, yInicial, xObjetivo, yObjetivo, camino, longitudCamino);

    // Iniciar el temporizador para mover la bala
    balaTimer->start(50);

    // Marcar la acción como realizada
    accionRealizada = true;

}





bool GrafoWidget::validarSeleccionInicial(int nodoCercano) {
    cout << "Nodo cercano: " << nodoCercano <<endl;
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
    if (accionRealizada) return;  // No permitir mover si ya se hizo una acción

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

    accionRealizada = false;  // Acción realizada, se cambia esto porque no permite que se muevan los tanques
    // Cambiar el turno después de mover
    movimientoTimer->start(500);  // Comenzar el temporizador para mover el tanque paso a paso
}

/*void GrafoWidget::DobleTurno(int jugadorTurno, bool estado) {

    dobleTurno = true;  // Activar el doble turno
    turnoJugadorDoble = jugadorActual;  // Guardar si es jugador de turnos pares (0) o impares (1)
}*/

/*void GrafoWidget::consumeAction() {
    if (dobleturnoDisponible) {
        dobleturnoDisponible = false;  // El doble turno se consume después de realizar la segunda acción
    }
}*/


void GrafoWidget::siguienteTurno(bool dobleturnoActivado, int contadorTurnos) {
    // Limpiar el camino del tanque en turno actual antes de pasar al siguiente turno
    Tanque* tanqueActual = obtenerTanqueActual();
    if (tanqueActual != nullptr && tanqueActual->estaVivo()) {
        tanqueActual->limpiarCamino();
    }

    // Cambiar de turno
    turnoActual = (turnoActual + 1) % 8;
    jugadorActual = (turnoActual % 2 == 0) ? 0 : 1;

    // Activar el power-up pendiente para el jugador actual
    int powerUpAplicar = (jugadorActual == 0) ? powerUpPendienteJugador1 : powerUpPendienteJugador2;
    if (powerUpAplicar != 0) {
        switch (powerUpAplicar) {
        case 1:  // Doble turno
            dobleturnoActivado = true;
            std::cout << "Aplicando Power-Up Doble Turno al Jugador " << jugadorActual + 1 << std::endl;
            break;
        case 2:  // Precisión de movimiento
            std::cout << "Aplicando Power-Up Precisión de Movimiento al Jugador " << jugadorActual + 1 << std::endl;
            // Aplicar efecto
            break;
        case 3:  // Precisión de ataque
            precisionDeAtaqueActivado = true;
            std::cout << "Aplicando Power-Up Precisión de Ataque al Jugador " << jugadorActual + 1 << std::endl;
            break;
        case 4:  // Poder de ataque
            poderDeAtaqueActivado = true;
            std::cout << "Aplicando Power-Up Poder de Ataque al Jugador " << jugadorActual + 1 << std::endl;
            break;
        }
        // Limpiar el power-up pendiente
        if (jugadorActual == 0) powerUpPendienteJugador1 = 0;
        else powerUpPendienteJugador2 = 0;
    }

    nodoInicial = -1;
    nodoFinal = -1;
    seleccionInicial = true;
    accionRealizada = false;
    seleccionDisparo = false;

    std::cout << "Cambio al turno del tanque: " << turnoActual << " (Jugador " << jugadorActual + 1 << ")" << std::endl;
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


