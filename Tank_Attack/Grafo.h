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

    // Métodos para asignar y conectar nodos
    void asignarPosicion(int nodo, int x, int y);
    void conectarNodos(int nodo1, int nodo2, int peso);
    //void conectarConDistancia(int nodo1, int nodo2);
    void generarMatriz(int ancho, int alto, int espaciado); // Generar los nodos como una matriz

    // Getters
    int getNumNodos() const;
    int getPosicionX(int nodo) const;
    int getPosicionY(int nodo) const;
    int obtenerPeso(int nodo1, int nodo2) const;

    // Heurística para A*
    int heuristica(int nodo1, int nodo2);

    // Mostrar la matriz de adyacencia (opcional)
    void mostrarMatriz();

    // Destructor
    ~Grafo();
};

#endif
