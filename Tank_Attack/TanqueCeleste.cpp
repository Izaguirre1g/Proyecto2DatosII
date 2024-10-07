#include "TanqueCeleste.h"
#include "BFS.h"
#include <cstdlib>  // Para rand()
#include <iostream>

TanqueCeleste::TanqueCeleste(Grafo* grafo, int nodoInicial) : Tanque(grafo, nodoInicial) {}

void TanqueCeleste::mover() {
    if (rand() % 2 == 0) {
        std::cout << "Movimiento aleatorio de celeste" << std::endl;
        // Movimiento aleatorio (50% de probabilidad)
        int numNodos = grafo->obtenerNumNodos();
        int nodoAleatorio = rand() % numNodos;  // Seleccionar nodo aleatorio

        // Definir el camino simple
        camino = new int[2];
        camino[0] = nodoActual;
        camino[1] = nodoAleatorio;
        longitudCamino = 2;

        nodoActual = nodoAleatorio;  // Moverse al nodo aleatorio
    } else {
        std::cout << "Movimiento mediante BFS de celeste" << std::endl;
        // Movimiento mediante BFS (50% de probabilidad)
        if (nodoObjetivo != -1) {
            camino = new int[grafo->obtenerNumNodos()];
            longitudCamino = 0;
            bfs(*grafo, nodoActual, nodoObjetivo, camino, longitudCamino);
            nodoActual = nodoObjetivo;  // El tanque llega al objetivo
        }
    }
}
