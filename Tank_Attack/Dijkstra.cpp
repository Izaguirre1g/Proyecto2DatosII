#include "Dijkstra.h"
#include <climits>  // Para representar infinito
#include <iostream>
using namespace std;

int* dijkstra(Grafo& grafo, int inicio, int fin, int& longitudCamino) {
    int numNodos = grafo.getNumNodos();
    int* distancia = new int[numNodos];
    bool* visitado = new bool[numNodos];
    int* anterior = new int[numNodos];  // Para almacenar el nodo anterior en el camino

    for (int i = 0; i < numNodos; ++i) {
        distancia[i] = INT_MAX;
        visitado[i] = false;
        anterior[i] = -1;
    }
    distancia[inicio] = 0;

    for (int i = 0; i < numNodos - 1; ++i) {
        int minDist = INT_MAX;
        int minNodo = -1;

        for (int j = 0; j < numNodos; ++j) {
            if (!visitado[j] && distancia[j] < minDist) {
                minDist = distancia[j];
                minNodo = j;
            }
        }

        if (minNodo == -1) break;
        visitado[minNodo] = true;

        for (int j = 0; j < numNodos; ++j) {
            int peso = grafo.obtenerPeso(minNodo, j);
            if (!visitado[j] && peso > 0 && distancia[minNodo] != INT_MAX
                && distancia[minNodo] + peso < distancia[j]) {
                distancia[j] = distancia[minNodo] + peso;
                anterior[j] = minNodo;
            }
        }
    }

    // Reconstruir el camino
    int* caminoTemp = new int[numNodos];
    int contador = 0;

    for (int at = fin; at != -1; at = anterior[at]) {
        caminoTemp[contador++] = at;
    }

    if (caminoTemp[contador - 1] != inicio) {
        delete[] caminoTemp;
        longitudCamino = 0;
        return nullptr;
    }

    int* camino = new int[contador];
    for (int i = 0; i < contador; ++i) {
        camino[i] = caminoTemp[contador - 1 - i];
    }

    // Limpiar memoria
    delete[] distancia;
    delete[] visitado;
    delete[] anterior;
    delete[] caminoTemp;

    longitudCamino = contador;
    return camino;
}


