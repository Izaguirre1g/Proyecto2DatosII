#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include "Grafo.h"
#include "TanqueAzul.h"
#include "TanqueCeleste.h"
#include "TanqueAmarillo.h"
#include "TanqueRojo.h"

int main() {
    srand(static_cast<unsigned>(time(0))); // Inicializar el generador de números aleatorios

    // Crear un grafo de ejemplo con 5 nodos
    Grafo grafo(5);
    grafo.asignarPosicion(0, 0, 0);
    grafo.asignarPosicion(1, 1, 0);
    grafo.asignarPosicion(2, 1, 1);
    grafo.asignarPosicion(3, 0, 1);
    grafo.asignarPosicion(4, 2, 2);

    // Conectar nodos con distancias
    grafo.conectarConDistancia(0, 1);
    grafo.conectarConDistancia(1, 2);
    grafo.conectarConDistancia(2, 3);
    grafo.conectarConDistancia(3, 0);
    grafo.conectarConDistancia(1, 4);
    grafo.conectarConDistancia(4, 2);

    // Crear tanques
    TanqueAzul tanqueAzul(&grafo, 0);
    TanqueCeleste tanqueCeleste(&grafo, 1);
    TanqueAmarillo tanqueAmarillo(&grafo, 2);
    TanqueRojo tanqueRojo(&grafo, 3);

    // Establecer el nodo objetivo para todos los tanques
    int nodoObjetivo = 4; // Por ejemplo, el nodo 4 como objetivo para todos
    tanqueAzul.setNodoObjetivo(nodoObjetivo);
    tanqueCeleste.setNodoObjetivo(nodoObjetivo);
    tanqueAmarillo.setNodoObjetivo(nodoObjetivo);
    tanqueRojo.setNodoObjetivo(nodoObjetivo);

    // Función para mostrar la posición actual del tanque
    auto mostrarPosicion = [](const Tanque& tanque, const std::string& nombre) {
        std::cout << nombre << " está en el nodo " << tanque.obtenerNodoActual() << std::endl;
    };

    // Mostrar posiciones antes de mover
    std::cout << "Antes de mover:" << std::endl;
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
    std::cout << "\nDespués de mover:" << std::endl;
    mostrarPosicion(tanqueAzul, "Tanque Azul");
    mostrarPosicion(tanqueCeleste, "Tanque Celeste");
    mostrarPosicion(tanqueAmarillo, "Tanque Amarillo");
    mostrarPosicion(tanqueRojo, "Tanque Rojo");

    return 0;
}



/*
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
    grafo.mostrarMatriz(); // Necesitarás modificar esta función para que acepte un parámetro

    // Ejecutar Dijkstra
    QString dijkstraResult = "Ejecutando Dijkstra desde el nodo 0:\n";
    //dijkstraResult += grafo.ejecutarDijkstra(0); // Método que deberías crear para obtener el resultado
    w.mostrarResultado(dijkstraResult);

    // Ejecutar A*
    QString aStarResult = "Ejecutando A* desde el nodo 0 al nodo 4:\n";
    //aStarResult += grafo.ejecutarAStar(0, 4); // Método que deberías crear para obtener el resultado
    w.mostrarResultado(aStarResult);

    w.show();
    return a.exec();
}
*/


/*
#include <iostream>
#include "Grafo.h"
#include "TanqueAzul.h"
#include "TanqueRojo.h"

int main() {
    // Crear un grafo con 5 nodos
    Grafo grafo(5);

    // Asignar posiciones a los nodos
    grafo.asignarPosicion(0, 0, 0);
    grafo.asignarPosicion(1, 10, 0);
    grafo.asignarPosicion(2, 10, 10);
    grafo.asignarPosicion(3, 0, 10);
    grafo.asignarPosicion(4, 5, 5);

    // Conectar nodos con distancias
    grafo.conectarConDistancia(0, 1);
    grafo.conectarConDistancia(1, 2);
    grafo.conectarConDistancia(2, 3);
    grafo.conectarConDistancia(3, 0);
    grafo.conectarConDistancia(4, 0);
    grafo.conectarConDistancia(4, 1);
    grafo.conectarConDistancia(4, 2);
    grafo.conectarConDistancia(4, 3);

    // Crear instancias de tanques
    TanqueAzul tanqueAzul(grafo);
    TanqueRojo tanqueRojo(grafo);

    // Asignar posiciones iniciales a los tanques
    tanqueAzul.mover(10, 10);
    tanqueRojo.mover(3, 3);

    // Imprimir información sobre los tanques
    std::cout << tanqueAzul.obtenerDescripcion() << std::endl;
    std::cout << "Posición actual del tanque azul: (" << tanqueAzul.obtenerPosX() << ", " << tanqueAzul.obtenerPosY() << ")" << std::endl;
    std::cout << "Nodo más cercano al tanque azul: " << tanqueAzul.obtenerPosicionActual() << std::endl;

    std::cout << tanqueRojo.obtenerDescripcion() << std::endl;
    std::cout << "Posición actual del tanque rojo: (" << tanqueRojo.obtenerPosX() << ", " << tanqueRojo.obtenerPosY() << ")" << std::endl;
    std::cout << "Nodo más cercano al tanque rojo: " << tanqueRojo.obtenerPosicionActual() << std::endl;

    return 0;
}
*/
