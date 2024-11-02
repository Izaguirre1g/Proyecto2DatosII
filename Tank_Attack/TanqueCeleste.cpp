#include "TanqueCeleste.h"
#include "LineOfSight.h"
#include <cstdlib>  // Para rand()
#include "BFS.h"
#include <QTimer>

TanqueCeleste::TanqueCeleste(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {
    srand(time(nullptr));  // Inicializar el generador de números aleatorios
}

// Método principal para mover el tanque
void TanqueCeleste::mover() {
    // Determinar si el movimiento será con BFS o aleatorio basado en el power-up de precisión
    bool usarBFS = (precisionDeMovimientoActivado) ? (rand() % 10 < 9) : (rand() % 2 == 0);

    if (precisionDeMovimientoActivado) {
        //std::cout << "Power-up de precisión activado: Probabilidad aumentada de usar BFS" << std::endl;
    }


    if (usarBFS) {  // Movimiento con BFS
        std::cout << "Movimiento mediante BFS de celeste" << std::endl;
        if (nodoObjetivo != -1) {
            // Verificar si el nodo objetivo está bloqueado
            if (grafo->nodosBloqueados[nodoObjetivo]) {
                std::cerr << "El nodo objetivo está bloqueado. No se puede mover el tanque celeste." << std::endl;
                return;
            }
            camino = new int[grafo->obtenerNumNodos()];
            longitudCamino = 0;
            bfs(*grafo, nodoActual, nodoObjetivo, camino, longitudCamino);
            indiceCamino = 0;  // Reiniciar el índice del camino
        }
    } else {  // Movimiento aleatorio
        std::cout << "Movimiento aleatorio de celeste" << std::endl;
        moverAleatoriamenteConValidacion();  // Mover de forma aleatoria con validaciones
    }

    // Desactivar el power-up de precisión de movimiento después de usarlo en el turno
    precisionDeMovimientoActivado = false;
}


// Función que selecciona una posición aleatoria dentro de un radio definido
int TanqueCeleste::obtenerPosicionAleatoriaEnRadio(int radio) {
    int nodoAleatorio;
    int intentos = 0;
    do {
        // Generar una posición aleatoria dentro del radio
        int xAleatorio = grafo->getPosicionX(nodoActual) + (rand() % (radio * 2 + 1)) - radio;
        int yAleatorio = grafo->getPosicionY(nodoActual) + (rand() % (radio * 2 + 1)) - radio;
        nodoAleatorio = grafo->encontrarNodoCercano(xAleatorio, yAleatorio);

        // Si no se encuentra una posición válida después de varios intentos, retorna -1
        if (intentos++ > 10 || nodoAleatorio == nodoActual) {
            return -1;
        }
    } while (grafo->esNodoBloqueado(nodoAleatorio));  // Asegurarse de que el nodo no esté bloqueado

    return nodoAleatorio;
}

// Mueve el tanque aleatoriamente con validaciones y luego continúa el movimiento con línea de vista
void TanqueCeleste::moverAleatoriamenteConValidacion() {
    int radioMovimiento = 150;  // Radio para el movimiento aleatorio
    int nuevoNodo = obtenerPosicionAleatoriaEnRadio(radioMovimiento);

    if (nuevoNodo != -1 && nodoActual != nuevoNodo) {
        std::cout << "Posición aleatoria encontrada. Nodo: " << nuevoNodo << std::endl;
        nodoActual = nuevoNodo;  // Actualizar la posición del tanque
        emit actualizarInterfaz();  // Forzar la actualización de la interfaz

        // Pausar brevemente para permitir que el movimiento aleatorio sea visible
        QTimer::singleShot(200, this, [this]() {
            continuarMovimiento();  // Continuar el movimiento después de una pausa
        });
    } else {
        // Si no se encontró una posición válida, intentar el movimiento con línea de vista
        std::cerr << "No se encontró una posición aleatoria válida. Intentando movimiento con línea de vista." << std::endl;
        continuarMovimiento();  // Continuar con el movimiento por línea de vista si no hay nodo aleatorio
    }
}

// Función para continuar el movimiento sin pausa
void TanqueCeleste::continuarMovimiento() {
    if (!avanzarLoMasLejosPosibleConLineaVista()) {
        finalizarMovimientoYTurno();  // Finalizar el turno si no puede avanzar más
    } else {
        QTimer::singleShot(100, this, [this]() {
            continuarMovimiento();  // Continuar el ciclo de movimiento
        });
    }
}

// Función para avanzar lo más lejos posible utilizando línea de vista
bool TanqueCeleste::avanzarLoMasLejosPosibleConLineaVista() {
    LineOfSight los(grafo);
    int siguienteNodo;

    // Verificar si el tanque ya ha alcanzado su objetivo
    if (nodoActual == nodoObjetivo) {
        std::cout << "El tanque ha llegado al nodo objetivo: " << nodoObjetivo << std::endl;
        finalizarMovimientoYTurno();  // Finalizar el turno cuando llegue al objetivo
        return false;  // No continuar el movimiento
    }

    // Verificar si hay línea de vista hacia el nodo objetivo desde la posición actual
    if (los.tieneLineaVista(nodoActual, nodoObjetivo)) {
        std::cout << "Línea de vista despejada. Avanzando al nodo objetivo: " << nodoObjetivo << std::endl;
        nodoActual = nodoObjetivo;
        emit actualizarInterfaz();  // Actualizar la interfaz
        finalizarMovimientoYTurno();  // Finalizar el turno
        return false;  // Detener el movimiento una vez que llega al objetivo
    } else {
        // Obtener el siguiente nodo más cercano en la dirección hacia el objetivo
        siguienteNodo = los.obtenerSiguienteNodoEnLinea(nodoActual, nodoObjetivo);

        // Detección de colisión
        if (detectarColision(siguienteNodo)) {
            std::cout << "Movimiento detenido debido a un obstáculo. Finalizando turno..." << std::endl;
            finalizarMovimientoYTurno();  // Finalizar el turno
            return false;  // Romper el ciclo
        }

        std::cout << "Avanzando al siguiente nodo: " << siguienteNodo << std::endl;
        nodoActual = siguienteNodo;
        emit actualizarInterfaz();  // Actualizar la interfaz

        // Agregar lógica para evitar ciclos infinitos
        if (nodoActual == siguienteNodo) {
            std::cerr << "Ciclo detectado. Finalizando el turno para evitar bucles infinitos." << std::endl;
            finalizarMovimientoYTurno();
            return false;
        }

        return true;  // Continuar el movimiento
    }
}

// Función para detectar colisiones
bool TanqueCeleste::detectarColision(int siguienteNodo) {
    if (grafo->esNodoBloqueado(siguienteNodo)) {
        std::cout << "Obstáculo encontrado en el nodo: " << siguienteNodo << ". Deteniéndose antes." << std::endl;
        return true;  // Se detectó una colisión
    }
    return false;  // No hay colisión
}

// Función para finalizar el movimiento y cambiar de turno
void TanqueCeleste::finalizarMovimientoYTurno() {
    std::cout << "Finalizando el movimiento y cambiando turno..." << std::endl;
    emit actualizarInterfaz();  // Actualizar la interfaz
}

// Función para avanzar paso a paso en el camino
void TanqueCeleste::avanzarCaminoPaso() {
    if (indiceCamino < longitudCamino) {
        nodoActual = camino[indiceCamino];  // Mover al siguiente nodo en el camino
        indiceCamino++;
    }
}

bool TanqueCeleste::haTerminadoCamino() {
    return indiceCamino >= longitudCamino;
}

int TanqueCeleste::getNodoSiguiente() {
    if (indiceCamino < longitudCamino) {
        return camino[indiceCamino];  // Devolver el siguiente nodo en el camino
    }
    return -1;  // No hay más nodos en el camino
}
