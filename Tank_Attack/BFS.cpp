#include "BFS.h"

#include "BFS.h"
#include "Grafo.h"
#include <iostream>

#define MAX_NODOS 1000

class Cola {
private:
    int arr[MAX_NODOS];
    int frente;
    int final;
    int size;

public:
    Cola() : frente(0), final(-1), size(0) {}

    void push(int valor) {
        if (size == MAX_NODOS) {
            std::cerr << "Cola llena, no se puede agregar más elementos\n";
            return;
        }
        final = (final + 1) % MAX_NODOS;
        arr[final] = valor;
        size++;
    }

    void pop() {
        if (size == 0) {
            std::cerr << "Cola vacía, no se puede eliminar\n";
            return;
        }
        frente = (frente + 1) % MAX_NODOS;
        size--;
    }

    int front() const {
        if (size == 0) {
            std::cerr << "Cola vacía, no hay elementos\n";
            return -1;
        }
        return arr[frente];
    }

    bool empty() const {
        return size == 0;
    }
};

void bfs(const Grafo& grafo, int startNode, int destinationNode) {
    int numNodos = grafo.getNumNodos();
    int distancias[MAX_NODOS];  // Arreglo para las distancias
    int predecesores[MAX_NODOS];  // Arreglo para los predecesores

    std::fill(distancias, distancias + numNodos, -1);
    std::fill(predecesores, predecesores + numNodos, -1);

    Cola cola;
    cola.push(startNode);
    distancias[startNode] = 0;

    while (!cola.empty()) {
        int nodoActual = cola.front();
        cola.pop();

        std::cout << "Nodo actual: " << nodoActual << " (Distancia: " << distancias[nodoActual] << ")\n";

        if (nodoActual == destinationNode) {
            break;
        }

        for (int vecino = 0; vecino < numNodos; ++vecino) {
            if (grafo.obtenerPeso(nodoActual, vecino) > 0 && distancias[vecino] == -1) {  // Verifica si hay conexión
                cola.push(vecino);
                distancias[vecino] = distancias[nodoActual] + 1;
                predecesores[vecino] = nodoActual;
            }
        }
    }

    // Imprimir el camino al nodo de destino
    if (distancias[destinationNode] != -1) {
        std::cout << "Camino al nodo " << destinationNode << ":\n";
        int camino[MAX_NODOS];
        int indice = 0;

        for (int v = destinationNode; v != -1; v = predecesores[v]) {
            camino[indice++] = v;
        }

        for (int i = indice - 1; i >= 0; --i) {
            std::cout << camino[i] << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No se puede alcanzar el nodo " << destinationNode << " desde el nodo " << startNode << ".\n";
    }
}
