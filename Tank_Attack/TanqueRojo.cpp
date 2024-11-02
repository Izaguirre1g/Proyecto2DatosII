#include "TanqueRojo.h"
#include "LineOfSight.h"
#include <cstdlib>  // Para rand()
#include "Dijkstra.h"
#include <QTimer>

TanqueRojo::TanqueRojo(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {
    srand(time(nullptr));  // Inicializar el generador de números aleatorios
}

// Método principal para mover el tanque
void TanqueRojo::mover() {
    //Determina si el movimiento será con Dijkstra o aleatorio basado en el power-up de precisión
    bool usarDijkstra = (precisionDeMovimientoActivado) ? (rand() % 10 < 9) : (rand() % 5 < 4);

    if (precisionDeMovimientoActivado) {
        std::cout << "Power-up de precisión activado: Probabilidad aumentada de usar Dijkstra" << std::endl;
    }

    if (usarDijkstra) {  // Movimiento con Dijkstra
        std::cout << "Movimiento mediante Dijkstra de rojo" << std::endl;
        if (nodoObjetivo != -1) {
            if (grafo->nodosBloqueados[nodoObjetivo]) {
                std::cerr << "El nodo objetivo está bloqueado. No se puede mover el tanque rojo." << std::endl;
                return;
            }
            camino = new int[grafo->obtenerNumNodos()];
            longitudCamino = 0;
            dijkstra(*grafo, nodoActual, nodoObjetivo, camino, longitudCamino);
            indiceCamino = 0;  //Reinicia el índice del camino
        }
    } else {  //Movimiento aleatorio
        std::cout << "Movimiento aleatorio de rojo" << std::endl;

        LineOfSight los(grafo);

        // Verificar si desde la posición actual hay línea de vista hacia el nodo objetivo
        if (los.tieneLineaVista(nodoActual, nodoObjetivo)) {
            std::cout << "Línea de vista despejada desde la posición actual. Moviendo al nodo objetivo: " << nodoObjetivo << std::endl;
            nodoActual = nodoObjetivo;  //Mueve directamente al nodo objetivo
            emit actualizarInterfaz();  //Actualiza la interfaz
            finalizarMovimientoYTurno();  //Finaliza el turno
        } else {
            moverAleatoriamenteConValidacion();  //Mueve de forma aleatoria con validaciones
        }
    }

    // Desactiva el power-up de precisión de movimiento después de usarlo en el turno
    precisionDeMovimientoActivado = false;
}


// Función que selecciona una posición aleatoria dentro de un radio definido
int TanqueRojo::obtenerPosicionAleatoriaEnRadio(int radio) {
    int nodoAleatorio;
    int intentos = 0;
    do {
        // Genera una posición aleatoria dentro del radio
        int xAleatorio = grafo->getPosicionX(nodoActual) + (rand() % (radio * 2 + 1)) - radio;
        int yAleatorio = grafo->getPosicionY(nodoActual) + (rand() % (radio * 2 + 1)) - radio;
        nodoAleatorio = grafo->encontrarNodoCercano(xAleatorio, yAleatorio);

        // Si no se encuentra una posición válida después de varios intentos, retorna -1
        if (intentos++ > 10 || nodoAleatorio == nodoActual) {
            return -1;
        }
    } while (grafo->esNodoBloqueado(nodoAleatorio));  // Se asegura de que el nodo no esté bloqueado

    return nodoAleatorio;
}

// Mueve el tanque aleatoriamente con validaciones y luego continúa el movimiento con línea de vista
void TanqueRojo::moverAleatoriamenteConValidacion() {
    int radioMovimiento = 150;  // Radio para el movimiento aleatorio
    int nuevoNodo = obtenerPosicionAleatoriaEnRadio(radioMovimiento);

    if (nuevoNodo != -1 && nodoActual != nuevoNodo) {
        std::cout << "Posición aleatoria encontrada. Nodo: " << nuevoNodo << std::endl;
        nodoActual = nuevoNodo;  //Actualiza la posición del tanque
        emit actualizarInterfaz();  //Fuerza la actualización de la interfaz

        // Pausa brevemente para permitir que el movimiento aleatorio sea visible
        QTimer::singleShot(200, this, [this]() {
            continuarMovimiento();  //Continua el movimiento después de una pausa
        });
    } else {
        // Si no se encontró una posición válida, intentar el movimiento con línea de vista
        std::cerr << "No se encontró una posición aleatoria válida. Intentando movimiento con línea de vista." << std::endl;
        continuarMovimiento();  //Continua con el movimiento por línea de vista si no hay nodo aleatorio
    }
}

// Función para continuar el movimiento sin pausa
void TanqueRojo::continuarMovimiento() {
    if (!avanzarLoMasLejosPosibleConLineaVista()) {
        finalizarMovimientoYTurno();  // Finaliza el turno si no puede avanzar más
    } else {
        QTimer::singleShot(100, this, [this]() {
            continuarMovimiento();  // Continua el ciclo de movimiento
        });
    }
}

// Función para avanzar lo más lejos posible utilizando línea de vista
bool TanqueRojo::avanzarLoMasLejosPosibleConLineaVista() {
    LineOfSight los(grafo);
    int siguienteNodo;

    // Verificar si el tanque ya ha alcanzado su objetivo
    if (nodoActual == nodoObjetivo) {
        std::cout << "El tanque ha llegado al nodo objetivo: " << nodoObjetivo << std::endl;
        finalizarMovimientoYTurno();  // Finaliza el turno cuando llegue al objetivo
        return false;  // No continua el movimiento
    }

    // Verifica si hay línea de vista hacia el nodo objetivo desde la posición actual
    if (los.tieneLineaVista(nodoActual, nodoObjetivo)) {
        std::cout << "Línea de vista despejada. Avanzando al nodo objetivo: " << nodoObjetivo << std::endl;
        nodoActual = nodoObjetivo;
        emit actualizarInterfaz();  // Actualiza la interfaz
        finalizarMovimientoYTurno();  // Finaliza el turno
        return false;  // Detiene el movimiento una vez que llega al objetivo
    } else {
        // Obtiene el siguiente nodo más cercano en la dirección hacia el objetivo
        siguienteNodo = los.obtenerSiguienteNodoEnLinea(nodoActual, nodoObjetivo);

        // Detección de colisión
        if (detectarColision(siguienteNodo)) {
            std::cout << "Movimiento detenido debido a un obstáculo. Finalizando turno..." << std::endl;
            finalizarMovimientoYTurno();  // Finaliza el turno
            return false;  // Rompe el ciclo
        }

        std::cout << "Avanzando al siguiente nodo: " << siguienteNodo << std::endl;
        nodoActual = siguienteNodo;
        emit actualizarInterfaz();  // Actualiza la interfaz


        if (nodoActual == siguienteNodo) {
            std::cerr << "Ciclo detectado. Finalizando el turno para evitar bucles infinitos." << std::endl;
            finalizarMovimientoYTurno();
            return false;
        }

        return true;  // Continua el movimiento
    }
}

// Función para detectar colisiones
bool TanqueRojo::detectarColision(int siguienteNodo) {
    if (grafo->esNodoBloqueado(siguienteNodo)) {
        std::cout << "Obstáculo encontrado en el nodo: " << siguienteNodo << ". Deteniéndose antes." << std::endl;
        return true;  // Se detectó una colisión
    }
    return false;  // No hay colisión
}

// Función para finalizar el movimiento y cambiar de turno
void TanqueRojo::finalizarMovimientoYTurno() {
    std::cout << "Finalizando el movimiento y cambiando turno..." << std::endl;
    emit actualizarInterfaz();  // Actualiza la interfaz
}

// Función para avanzar paso a paso en el camino
void TanqueRojo::avanzarCaminoPaso() {
    if (indiceCamino < longitudCamino) {
        nodoActual = camino[indiceCamino];  //avanza al siguiente nodo en el camino
        indiceCamino++;
    }
}

bool TanqueRojo::haTerminadoCamino() {
    return indiceCamino >= longitudCamino;
}

int TanqueRojo::getNodoSiguiente() {
    if (indiceCamino < longitudCamino) {
        return camino[indiceCamino];  // Devuelve el siguiente nodo en el camino
    }
    return -1;  // No hay más nodos en el camino
}
