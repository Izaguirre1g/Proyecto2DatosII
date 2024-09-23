#include "TanqueRojo.h"
#include "Dijkstra.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

TanqueRojo::TanqueRojo(Grafo& grafo) : Tanque(ColorTanque::Rojo, grafo) {
    std::srand(std::time(nullptr)); // Inicializar semilla para generación aleatoria
}

void TanqueRojo::comportamientoEspecial() const {
    //80% probabilidad para Dijkstra, 20% para movimiento aleatorio
    if (std::rand() % 100 < 80) {
        //moverConDijkstra();
    } else {
        //moverAleatoriamente();
    }
}

void TanqueRojo::moverConDijkstra() {
    std::cout << "El tanque amarillo se mueve usando Dijkstra." << std::endl;

    // Definir el nodo de destino (puedes definirlo de manera específica)
    int destino = 3; // Cambia esto según la lógica del juego

    // Aquí puedes usar una instancia del grafo
    Grafo& grafo = obtenerGrafo(); // Suponiendo que `obtenerGrafo` es un método de `Tanque`

    // Llamar a la función de Dijkstra
    dijkstra(grafo, obtenerPosicionActual()); // Suponiendo que `obtenerPosicionActual` devuelve el nodo actual
}

void TanqueRojo::moverAleatoriamente() {
    std::cout << "El tanque amarillo se mueve aleatoriamente." << std::endl;

    Grafo& grafo = obtenerGrafo(); // Suponiendo que `obtenerGrafo` es un método de `Tanque`
    int nodoActual = obtenerPosicionActual(); // Suponiendo que `obtenerPosicionActual` devuelve el nodo actual

    std::vector<int> vecinos;
    for (int vecino = 0; vecino < grafo.obtenerNumNodos(); ++vecino) {
        if (grafo.obtenerPeso(nodoActual, vecino) > 0) {
            vecinos.push_back(vecino);
        }
    }

    if (!vecinos.empty()) {
        int nuevoNodo = vecinos[std::rand() % vecinos.size()];
        std::cout << "Moviéndose al nodo " << nuevoNodo << std::endl;
        // Actualiza la posición del tanque aquí
    } else {
        std::cout << "No hay nodos vecinos para moverse." << std::endl;
    }
}
