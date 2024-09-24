// AStar.cpp
#include "AStar.h"
#include "Grafo.h"
#include <climits> // Para representar infinito
#include <iostream>
using namespace std;

void aEstrella(Grafo& grafo, int inicio, int objetivo) {
    int numNodos = grafo.getNumNodos();
    int* distancia = new int[numNodos];
    int* costoEstimado = new int[numNodos];
    bool* visitado = new bool[numNodos];

    // Inicializar distancias y costos estimados
    for (int i = 0; i < numNodos; ++i) {
        distancia[i] = INT_MAX;
        costoEstimado[i] = INT_MAX;
        visitado[i] = false;
    }

    distancia[inicio] = 0;
    costoEstimado[inicio] = grafo.heuristica(inicio, objetivo);

    // Repetir hasta encontrar el nodo objetivo
    for (int i = 0; i < numNodos - 1; ++i) {
        int minCosto = INT_MAX;
        int minNodo = -1;

        // Encontrar el nodo con el costo estimado más bajo
        for (int j = 0; j < numNodos; ++j) {
            if (!visitado[j] && costoEstimado[j] < minCosto) {
                minCosto = costoEstimado[j];
                minNodo = j;
            }
        }

        // Si llegamos al nodo objetivo, detener
        if (minNodo == objetivo) break;

        visitado[minNodo] = true;

        // Actualizar los costos de los nodos adyacentes
        for (int j = 0; j < numNodos; ++j) {
            int peso = grafo.obtenerPeso(minNodo, j);  // Usar obtenerPeso()
            if (!visitado[j] && peso > 0 && distancia[minNodo] != INT_MAX) {
                int nuevoCosto = distancia[minNodo] + peso;
                if (nuevoCosto < distancia[j]) {
                    distancia[j] = nuevoCosto;
                    costoEstimado[j] = nuevoCosto + grafo.heuristica(j, objetivo);
                }
            }
        }
    }

    // Imprimir el camino encontrado
    cout << "Distancia de " << inicio << " a " << objetivo << ": " << distancia[objetivo] << endl;

    // Liberar memoria
    delete[] distancia;
    delete[] costoEstimado;
    delete[] visitado;
}
