#include "Tanque.h"
#include "Grafo.h"

Tanque::Tanque(Grafo* grafo, int nodoInicial)
    : grafo(grafo), nodoActual(nodoInicial), nodoObjetivo(-1), camino(nullptr), longitudCamino(0) {}

int Tanque::obtenerNodoActual() const {
    return nodoActual;
}

void Tanque::setNodoObjetivo(int nodoObjetivo) {
    this->nodoObjetivo = nodoObjetivo;
}

// Implementación de los nuevos métodos
int* Tanque::getCamino() const {
    return camino;  // Retorna el camino calculado
}

int Tanque::getLongitudCamino() const {
    return longitudCamino;  // Retorna la longitud del camino
}
