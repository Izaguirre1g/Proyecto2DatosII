#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "Grafo.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Crear y configurar el grafo
    Grafo grafo(5);
    grafo.asignarPosicion(0, 0, 0);
    grafo.asignarPosicion(1, 2, 3);
    grafo.asignarPosicion(2, 5, 1);
    grafo.asignarPosicion(3, 6, 4);
    grafo.asignarPosicion(4, 8, 2);

    // Conectar nodos
    grafo.conectarNodos(0, 1, 10);
    grafo.conectarNodos(0, 2, 5);
    grafo.conectarNodos(1, 3, 2);
    grafo.conectarNodos(2, 3, 8);
    grafo.conectarNodos(3, 4, 6);

    // Mostrar matriz de adyacencia
    w.mostrarResultado("Matriz de adyacencia:\n");
    grafo.mostrarMatriz(w); // Necesitarás modificar esta función para que acepte un parámetro

    // Ejecutar Dijkstra
    QString dijkstraResult = "Ejecutando Dijkstra desde el nodo 0:\n";
    dijkstraResult += grafo.ejecutarDijkstra(0); // Método que deberías crear para obtener el resultado
    w.mostrarResultado(dijkstraResult);

    // Ejecutar A*
    QString aStarResult = "Ejecutando A* desde el nodo 0 al nodo 4:\n";
    aStarResult += grafo.ejecutarAStar(0, 4); // Método que deberías crear para obtener el resultado
    w.mostrarResultado(aStarResult);

    w.show();
    return a.exec();
}
