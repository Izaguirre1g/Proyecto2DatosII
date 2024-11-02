#include "Tanque.h"
#include "Grafo.h"

Tanque::Tanque(Grafo* grafo, int nodoInicial)
    : grafo(grafo), nodoActual(nodoInicial), nodoObjetivo(-1), camino(nullptr), longitudCamino(0), vida(100) {}

int Tanque::obtenerNodoActual() const {
    return nodoActual;
}

void Tanque::setNodoObjetivo(int nodoObjetivo) {
    this->nodoObjetivo = nodoObjetivo;
}


int* Tanque::getCamino() const {
    return camino;  // Retorna el camino calculado
}

int Tanque::getLongitudCamino() const {
    return longitudCamino;  // Retorna la longitud del camino
}

void Tanque::limpiarCamino() {
    //Libera memoria del camino y reiniciar los parámetros
    if (camino) {
        delete[] camino;  // Liberar el arreglo de camino si existe
        camino = nullptr;
    }
    longitudCamino = 0;
    indiceCamino = 0;
    std::cout << "Camino limpiado para el tanque en nodo " << nodoActual << std::endl;
}

void Tanque::reducirVida(int cantidad) {
    // Lógica para reducir vida del tanque
    vida -= cantidad;
    if (vida <= 0) {
        std::cout << "El tanque ha sido destruido!" << std::endl;
        validaExistenciaTanque(-2);
    }
}

bool Tanque::validaExistenciaTanque(int resultado_existenciaTanque){
    if(resultado_existenciaTanque <= 0){
        return true;//Confirma la destrucción del tanque, logrando asi correctamente los turnos
    }
}
