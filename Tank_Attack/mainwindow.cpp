#include "mainwindow.h"
#include "GrafoWidget.h"

MainWindow::MainWindow(Grafo* grafo, QWidget *parent)
    : QMainWindow(parent), grafo(grafo) {  // Inicializamos el puntero a Grafo

    // Crear el widget de grafo
    GrafoWidget* grafoWidget = new GrafoWidget(this);

    // Asignar el grafo al widget para que lo dibuje
    grafoWidget->setGrafo(grafo);

    // Establecer el tamaño de la ventana para que sea más grande que el widget
    setFixedSize(1050, 720);  // Ajusta el tamaño según sea necesario

    // Establecer el widget como el widget central de la ventana
    setCentralWidget(grafoWidget);
}

MainWindow::~MainWindow() {
    // No es necesario eliminar el grafo aquí, porque no lo creamos en MainWindow.
    // Si lo creaste en otra parte, puedes eliminarlo ahí.
}
