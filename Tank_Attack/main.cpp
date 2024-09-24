#include "mainwindow.h"
#include "Grafo.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

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

    return a.exec();
}

