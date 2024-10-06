// DijkstraFusionado.cpp
#include "Dijkstra.h"
#include <climits> // Para representar infinito
#include <iostream>

#define MAX_NODOS 1000 // Número máximo de nodos permitidos en el grafo

using namespace std;

class Matriz {
public:
    int matrizAdyacencia[MAX_NODOS][MAX_NODOS]; // Matriz de adyacencia
    int numNodos;

    Matriz(int nodos) : numNodos(nodos) {
        // Inicializar todas las conexiones como 0 (sin aristas)
        for (int i = 0; i < numNodos; ++i) {
            for (int j = 0; j < numNodos; ++j) {
                matrizAdyacencia[i][j] = 0;
            }
        }
    }

    void agregarArista(int origen, int destino, int peso) {
        matrizAdyacencia[origen][destino] = peso;
        matrizAdyacencia[destino][origen] = peso; // Si el grafo es no dirigido
    }

    int obtenerPeso(int origen, int destino) {
        return matrizAdyacencia[origen][destino];
    }

    int obtenerNumNodos() {
        return numNodos;
    }
};

void dijkstra(Grafo& grafo, int inicio) {
    int numNodos = grafo.obtenerNumNodos();
    int* distancia = new int[numNodos];  // Distancias mínimas
    int* predecesores = new int[numNodos]; // Para reconstruir el camino
    bool* visitado = new bool[numNodos]; // Si el nodo ha sido visitado

    // Inicializar distancias, predecesores y visitados
    for (int i = 0; i < numNodos; ++i) {
        distancia[i] = INT_MAX; // Infinito
        predecesores[i] = -1;   // Ningún predecesor al inicio
        visitado[i] = false;    // Ningún nodo visitado al inicio
    }
    distancia[inicio] = 0; // La distancia al nodo inicial es 0

    // Ciclo principal de Dijkstra
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

        if (minNodo == -1) {
            std::cerr << "Error: No se puede continuar, no hay nodos accesibles.\n";
            break;  // Todos los nodos accesibles ya están procesados
        }

        // Marcar el nodo como visitado
        visitado[minNodo] = true;

        // Actualizar las distancias de los nodos adyacentes
        for (int j = 0; j < numNodos; ++j) {
            int peso = grafo.obtenerPeso(minNodo, j);
            if (!visitado[j] && peso > 0 && distancia[minNodo] != INT_MAX
                && distancia[minNodo] + peso < distancia[j]) {
                distancia[j] = distancia[minNodo] + peso;
                predecesores[j] = minNodo; // Registrar el predecesor
            }
        }
    }

    // Imprimir distancias desde el nodo inicial
    std::cout << "Distancias desde el nodo " << inicio << ":\n";
    for (int i = 0; i < numNodos; ++i) {
        std::cout << "Nodo " << i << ": " << (distancia[i] == INT_MAX ? "Infinito" : std::to_string(distancia[i])) << std::endl;
    }

    // Imprimir el camino más corto desde el nodo inicial a todos los nodos
    for (int destino = 0; destino < numNodos; ++destino) {
        if (distancia[destino] < INT_MAX) {
            std::cout << "Camino más corto al nodo " << destino << ":\n";
            int* camino = new int[numNodos]; // Usar memoria dinámica para el camino
            int indice = 0;

            // Reconstruir el camino
            for (int v = destino; v != -1; v = predecesores[v]) {
                camino[indice++] = v;
            }

            // Imprimir el camino en orden inverso
            for (int i = indice - 1; i >= 0; --i) {
                std::cout << camino[i] << " ";
            }
            std::cout << "\n";

            delete[] camino; // Liberar la memoria del camino
        }
    }

    // Liberar memoria
    delete[] distancia;
    delete[] predecesores;
    delete[] visitado;
}

