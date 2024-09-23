// Dijkstra.cpp
#include "Dijkstra.h"
#include <climits> // Para representar infinito
#include <iostream>
#include <vector>  // Para usar std::vector
#include <algorithm> // Para std::reverse

using namespace std;

void dijkstra(Grafo& grafo, int inicio) {
    int numNodos = grafo.obtenerNumNodos();
    vector<int> distancia(numNodos, INT_MAX);
    vector<int> predecesores(numNodos, -1); // Para reconstruir el camino
    vector<bool> visitado(numNodos, false);

    // Inicializar distancias y predecesores
    distancia[inicio] = 0;

    for (int i = 0; i < numNodos - 1; ++i) {
        int minDist = INT_MAX;
        int minNodo = -1;

        // Encontrar el nodo no visitado con la distancia mínima
        for (int j = 0; j < numNodos; ++j) {
            if (!visitado[j] && distancia[j] < minDist) {
                minDist = distancia[j];
                minNodo = j;
            }
        }

        if (minNodo == -1) break; // Todos los nodos están visitados

        // Marcar el nodo como visitado
        visitado[minNodo] = true;

        // Actualizar las distancias de los nodos adyacentes
        for (int j = 0; j < numNodos; ++j) {
            int peso = grafo.obtenerPeso(minNodo, j);  // Usar obtenerPeso()
            if (!visitado[j] && peso > 0 && distancia[minNodo] != INT_MAX
                && distancia[minNodo] + peso < distancia[j]) {
                distancia[j] = distancia[minNodo] + peso;
                predecesores[j] = minNodo; // Registrar el predecesor
            }
        }
    }

    // Imprimir distancias
    cout << "Distancias desde el nodo " << inicio << ":\n";
    for (int i = 0; i < numNodos; ++i) {
        cout << "Nodo " << i << ": " << (distancia[i] == INT_MAX ? "Infinito" : to_string(distancia[i])) << endl;
    }

    // Imprimir el camino más corto desde el nodo inicial a todos los nodos
    for (int destino = 0; destino < numNodos; ++destino) {
        if (distancia[destino] < INT_MAX) {
            cout << "Camino más corto al nodo " << destino << ":\n";
            vector<int> camino;
            for (int v = destino; v != -1; v = predecesores[v]) {
                camino.push_back(v);
            }
            reverse(camino.begin(), camino.end());
            for (int nodo : camino) {
                cout << nodo << " ";
            }
            cout << "\n";
        }
    }
}
