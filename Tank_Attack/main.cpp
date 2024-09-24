#include "mainwindow.h"
#include "Grafo.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Crear un grafo con 5 nodos
    Grafo* grafo = new Grafo(5);

    // Asignar posiciones a los nodos
    grafo->asignarPosicion(0, 50, 50);
    grafo->asignarPosicion(1, 150, 100);
    grafo->asignarPosicion(2, 250, 150);
    grafo->asignarPosicion(3, 350, 200);
    grafo->asignarPosicion(4, 450, 250);

    // Conectar los nodos (según tus conexiones)
    grafo->conectarNodos(0, 1, 1);
    grafo->conectarNodos(1, 2, 1);
    grafo->conectarNodos(2, 3, 1);
    grafo->conectarNodos(3, 4, 1);
    grafo->conectarNodos(0, 4, 1);

    // Crear la ventana principal pasando el grafo
    MainWindow w(grafo);
    w.show();

    return a.exec();
}

