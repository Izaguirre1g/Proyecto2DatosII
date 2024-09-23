// Dijkstra.cpp
#include "Dijkstra.h"
#include <climits> // Para representar infinito
#include <iostream>
using namespace std;

void dijkstra(Grafo& grafo, int inicio) {
    int numNodos = grafo.obtenerNumNodos();
    int* distancia = new int[numNodos];
    bool* visitado = new bool[numNodos];

    // Inicializar distancias y visitado
    for (int i = 0; i < numNodos; ++i) {
        distancia[i] = INT_MAX;
        visitado[i] = false;
    }
    distancia[inicio] = 0;

    // Algoritmo de Dijkstra
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

        // Marcar el nodo como visitado
        visitado[minNodo] = true;

        // Actualizar las distancias de los nodos adyacentes
        for (int j = 0; j < numNodos; ++j) {
            int peso = grafo.obtenerPeso(minNodo, j);  // Usar obtenerPeso()
            if (!visitado[j] && peso > 0 && distancia[minNodo] != INT_MAX
                && distancia[minNodo] + peso < distancia[j]) {
                distancia[j] = distancia[minNodo] + peso;
            }
        }
    }

    // Imprimir distancias
    cout << "Distancias desde el nodo " << inicio << ":\n";
    for (int i = 0; i < numNodos; ++i) {
        cout << "Nodo " << i << ": " << distancia[i] << endl;
    }

    // Liberar memoria
    delete[] distancia;
    delete[] visitado;
}
