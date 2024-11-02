#include "AStar.h"
#include "Grafo.h"
#include <climits> // Para representar infinito
#include <iostream>
using namespace std;

int* aEstrella(Grafo& grafo, int inicio, int objetivo, int& longitudCamino) {
    int numNodos = grafo.obtenerNumNodos();

    // Arrays dinámicos para gestionar los datos de cada nodo
    int* distancia = new int[numNodos];
    int* costoEstimado = new int[numNodos];
    bool* visitado = new bool[numNodos];
    int* predecesor = new int[numNodos];

    // Inicializar distancias, costos estimados, visitado y predecesores
    for (int i = 0; i < numNodos; ++i) {
        distancia[i] = INT_MAX;
        costoEstimado[i] = INT_MAX;
        visitado[i] = false;
        predecesor[i] = -1;
    }

    distancia[inicio] = 0;
    costoEstimado[inicio] = grafo.heuristica(inicio, objetivo);  // f(n) = h(n)

    // Bucle principal del algoritmo A*
    for (int i = 0; i < numNodos - 1; ++i) {
        int minCosto = INT_MAX;
        int minNodo = -1;

        // Encontrar el nodo con el menor costo estimado que no haya sido visitado
        for (int j = 0; j < numNodos; ++j) {
            if (!visitado[j] && costoEstimado[j] < minCosto) {
                minCosto = costoEstimado[j];
                minNodo = j;
            }
        }

        if (minNodo == -1 || minNodo == objetivo) break;

        visitado[minNodo] = true;

        for (int j = 0; j < numNodos; ++j) {
            if (grafo.esNodoBloqueado(j) || visitado[j]) continue;

            int peso = grafo.obtenerPeso(minNodo, j);
            if (peso > 0 && distancia[minNodo] != INT_MAX) {
                int nuevoCosto = distancia[minNodo] + peso;
                if (nuevoCosto < distancia[j]) {
                    distancia[j] = nuevoCosto;
                    costoEstimado[j] = nuevoCosto + grafo.heuristica(j, objetivo);
                    predecesor[j] = minNodo;
                }
            }
        }
    }

    // Si no hay camino al objetivo
    if (distancia[objetivo] == INT_MAX) {
        cout << "No hay camino disponible de " << inicio << " a " << objetivo << "." << endl;
        longitudCamino = 0;
        delete[] distancia;
        delete[] costoEstimado;
        delete[] visitado;
        delete[] predecesor;
        return nullptr;
    }

    // Reconstruir el camino desde el objetivo al inicio
    int* camino = new int[numNodos];
    int index = 0;
    for (int nodo = objetivo; nodo != -1; nodo = predecesor[nodo]) {
        camino[index++] = nodo;
    }

    // Ajustar la longitud del camino
    longitudCamino = index;

    // Invertir el camino para que sea de inicio a fin
    for (int i = 0; i < longitudCamino / 2; ++i) {
        std::swap(camino[i], camino[longitudCamino - 1 - i]);
    }

    // Liberar memoria dinámica
    delete[] distancia;
    delete[] costoEstimado;
    delete[] visitado;
    delete[] predecesor;

    return camino;
}

