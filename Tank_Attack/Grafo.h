#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <cmath> // Para calcular distancias entre puntos

class Grafo {
private:
    int** matrizAdyacencia;  // Matriz de adyacencia para las conexiones entre nodos
    int numNodos;            // Número de nodos en el grafo
    int* posicionesX;        // Coordenadas X de los nodos
    int* posicionesY;        // Coordenadas Y de los nodos

public:
    // Constructor
    Grafo(int n);

    // Métodos para asignar y conectar nodos
    void asignarPosicion(int nodo, int x, int y);
    void conectarNodos(int nodo1, int nodo2, int peso);
    void conectarConDistancia(int nodo1, int nodo2);
    void generarMatriz(int ancho, int alto, int espaciado); // Generar nodos en una matriz con espaciado
    void asignarObstaculosAleatorios(int numObstaculos);
    bool esNodoBloqueado(int nodo) const;

    // Mostrar la matriz de adyacencia
    void mostrarMatriz();
    int encontrarNodoCercano(int nodo1, int nodo2);

    // Heurística para A* o cálculos de distancia
    int heuristica(int nodo1, int nodo2);

    // Métodos para obtener información
    int obtenerNumNodos() const;
    int obtenerPeso(int nodo1, int nodo2) const;
    int getNumNodos() const;          // Alias de obtenerNumNodos (opcional)
    int obtenerPosX(int nodo) const;
    int obtenerPosY(int nodo) const;
    int getPosicionX(int nodo) const; // Alias de obtenerPosX (opcional)
    int getPosicionY(int nodo) const; // Alias de obtenerPosY (opcional)
    bool* nodosBloqueados;  // Arreglo que indica si un nodo está bloqueado por un obstáculo
    void bloquearNodosIntermedios(int nodo);


    // Destructor
    ~Grafo();
};

#endif
