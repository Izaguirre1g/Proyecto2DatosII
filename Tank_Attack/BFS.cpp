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

// Modificar para devolver el camino y su longitud
void bfs(const Grafo& grafo, int startNode, int destinationNode, int* camino, int& longitudCamino) {
    int numNodos = grafo.obtenerNumNodos();
    int distancias[MAX_NODOS];  // Arreglo para las distancias
    int predecesores[MAX_NODOS];  // Arreglo para los predecesores

    std::fill(distancias, distancias + numNodos, -1);  // Inicializar distancias con -1 (inaccesible)
    std::fill(predecesores, predecesores + numNodos, -1);  // Inicializar predecesores con -1

    Cola cola;
    cola.push(startNode);
    distancias[startNode] = 0;  // Distancia al nodo inicial es 0

    while (!cola.empty()) {
        int nodoActual = cola.front();
        cola.pop();

        std::cout << "Nodo actual: " << nodoActual << " (Distancia: " << distancias[nodoActual] << ")\n";

        if (nodoActual == destinationNode) {
            std::cout << "Destino alcanzado en BFS\n";
            break;
        }

        // Explorar todos los vecinos del nodo actual
        for (int vecino = 0; vecino < numNodos; ++vecino) {
            if (grafo.obtenerPeso(nodoActual, vecino) > 0  // Verificar si hay conexión
                && distancias[vecino] == -1  // Aún no visitado
                && !grafo.esNodoBloqueado(vecino)) {  // Asegurarse de que no esté bloqueado
                cola.push(vecino);
                distancias[vecino] = distancias[nodoActual] + 1;
                predecesores[vecino] = nodoActual;
            }
        }
    }

    // Verificar si alcanzamos el destino
    if (distancias[destinationNode] == -1) {
        std::cerr << "No se pudo alcanzar el nodo destino desde el nodo inicial.\n";
        longitudCamino = 0;  // No se encontró camino
    } else {
        std::cout << "Camino al nodo " << destinationNode << ":\n";
        int indice = 0;

        // Reconstruir el camino desde el destino al nodo inicial
        for (int v = destinationNode; v != -1; v = predecesores[v]) {
            camino[indice++] = v;
        }

        // Invertir el camino para que vaya desde el inicio hasta el destino
        for (int i = 0; i < indice / 2; ++i) {
            std::swap(camino[i], camino[indice - 1 - i]);
        }

        // Actualizar la longitud del camino
        longitudCamino = indice;

        // Imprimir el camino
        for (int i = 0; i < indice; ++i) {
            std::cout << camino[i] << " ";
        }
        std::cout << "\n";
    }
}
