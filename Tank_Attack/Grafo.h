#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <cmath> // Para calcular distancias entre puntos

class Grafo {
private:
    int** matrizAdyacencia;
    int numNodos;
    int* posicionesX;  // Coordenadas X de los nodos
    int* posicionesY;  // Coordenadas Y de los nodos

public:
    Grafo(int n);

    void asignarPosicion(int nodo, int x, int y);
    void conectarNodos(int nodo1, int nodo2, int peso);
    void conectarConDistancia(int nodo1, int nodo2);
    void mostrarMatriz();
    int obtenerNumNodos() const;
    int obtenerPeso(int nodo1, int nodo2) const;
    int heuristica(int nodo1, int nodo2);

    // Métodos para obtener las coordenadas
    int obtenerPosX(int nodo) const;
    int obtenerPosY(int nodo) const;

    ~Grafo();
};

#endif
