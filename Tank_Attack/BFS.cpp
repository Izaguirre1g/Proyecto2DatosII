#include "BFS.h"
#include "Grafo.h"
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

void bfs(const Grafo& grafo, int startNode, int destinationNode) {
    int numNodos = grafo.obtenerNumNodos();
    std::vector<int> distancias(numNodos, -1); // -1 indica que el nodo no ha sido visitado
    std::vector<int> predecesores(numNodos, -1);

    std::queue<int> cola;
    cola.push(startNode);
    distancias[startNode] = 0;

    while (!cola.empty()) {
        int nodoActual = cola.front();
        cola.pop();

        // Muestra el nodo actual y su distancia
        std::cout << "Nodo actual: " << nodoActual << " (Distancia: " << distancias[nodoActual] << ")\n";

        if (nodoActual == destinationNode) {
            break;
        }

        for (int vecino = 0; vecino < numNodos; ++vecino) {
            if (grafo.obtenerPeso(nodoActual, vecino) > 0 && distancias[vecino] == -1) { // Verifica si hay una conexión
                cola.push(vecino);
                distancias[vecino] = distancias[nodoActual] + 1;
                predecesores[vecino] = nodoActual;
            }
        }
    }

    // Imprimir el camino al nodo de destino
    if (distancias[destinationNode] != -1) {
        std::cout << "Camino al nodo " << destinationNode << ":\n";
        std::vector<int> camino;
        for (int v = destinationNode; v != -1; v = predecesores[v]) {
            camino.push_back(v);
        }
        std::reverse(camino.begin(), camino.end());
        for (int nodo : camino) {
            std::cout << nodo << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No se puede alcanzar el nodo " << destinationNode << " desde el nodo " << startNode << ".\n";
    }
}
