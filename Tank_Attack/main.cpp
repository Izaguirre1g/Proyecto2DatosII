#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include "mainwindow.h"
#include "Grafo.h"
#include "TanqueAzul.h"
#include "TanqueCeleste.h"
#include "TanqueAmarillo.h"
#include "TanqueRojo.h"
#include <QApplication>
using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Inicializar el generador de números aleatorios
    srand(static_cast<unsigned>(time(0)));

    // Calcular la cantidad de nodos que caben en un área de 1050x720 con espaciado de 30
    int ancho = 1075;
    int alto = 580;
    int espaciado = 22;
    int numNodos = (ancho / espaciado) * (alto / espaciado);  // Número total de nodos

    // Crear un grafo con el número calculado de nodos
    Grafo* grafo = new Grafo(numNodos);

    // Generar la matriz de nodos en el espacio
    grafo->generarMatriz(ancho, alto, espaciado);

    // Crear la ventana principal y pasarle el grafo
    MainWindow w(grafo);
    w.show();
/*
    // Simulación de los tanques
    TanqueAzul tanqueAzul(grafo, 0);
    TanqueCeleste tanqueCeleste(grafo, 1);
    TanqueAmarillo tanqueAmarillo(grafo, 2);
    TanqueRojo tanqueRojo(grafo, 3);

    // Establecer el nodo objetivo para todos los tanques
    int nodoObjetivo = 100; // Nodo como objetivo para todos
    tanqueAzul.setNodoObjetivo(nodoObjetivo);
    tanqueCeleste.setNodoObjetivo(nodoObjetivo);
    tanqueAmarillo.setNodoObjetivo(nodoObjetivo);
    tanqueRojo.setNodoObjetivo(nodoObjetivo);

    // Función para mostrar la posición actual del tanque
    auto mostrarPosicion = [](const Tanque& tanque, const std::string& nombre) {
        cout << nombre << " está en el nodo " << tanque.obtenerNodoActual() << endl;
    };

    // Mostrar posiciones antes de mover
    cout << "Antes de mover:" << std::endl;
    mostrarPosicion(tanqueAzul, "Tanque Azul");
    mostrarPosicion(tanqueCeleste, "Tanque Celeste");
    mostrarPosicion(tanqueAmarillo, "Tanque Amarillo");
    mostrarPosicion(tanqueRojo, "Tanque Rojo");

    // Realizar movimientos
    tanqueAzul.mover();
    tanqueCeleste.mover();
    tanqueAmarillo.mover();
    tanqueRojo.mover();

    // Mostrar posiciones después de mover
    cout << "\nDespués de mover:" << endl;
    mostrarPosicion(tanqueAzul, "Tanque Azul");
    mostrarPosicion(tanqueCeleste, "Tanque Celeste");
    mostrarPosicion(tanqueAmarillo, "Tanque Amarillo");
    mostrarPosicion(tanqueRojo, "Tanque Rojo");
*/
    // Ejecutar la aplicación Qt
    return a.exec();
}

