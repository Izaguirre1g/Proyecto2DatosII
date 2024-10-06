#include "TanqueRojo.h"
#include "Dijkstra.h"
#include <cstdlib> // Para rand()

TanqueRojo::TanqueRojo(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {}

void TanqueRojo::mover() {
    if (rand() % 5 < 4) {
        std::cout << "Movimiento mediante Dijkstra de rojo" << std::endl;
        // Movimiento mediante Dijkstra (80% de probabilidad)
        if (nodoObjetivo != -1) {
            // Reservar espacio para almacenar el camino y calcularlo usando Dijkstra
            camino = new int[grafo->obtenerNumNodos()];
            longitudCamino = 0;  // Reiniciar la longitud del camino
            dijkstra(*grafo, nodoActual, nodoObjetivo, camino, longitudCamino);
            nodoActual = nodoObjetivo; // El tanque llega al nodo objetivo
        }
    } else {
        std::cout << "Movimiento aleatorio de rojo" << std::endl;
        // Movimiento aleatorio (20% de probabilidad)
        int numNodos = grafo->obtenerNumNodos();
        nodoActual = rand() % numNodos;
        camino = nullptr;  // No hay camino en el movimiento aleatorio
        longitudCamino = 0;  // No hay longitud de camino en este caso
    }
}
