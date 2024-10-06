#include "mainwindow.h"
#include "GrafoWidget.h"
#include <cmath>
#include <QTimer>  // Incluir QTimer
#include <iostream>  // Para imprimir en consola

MainWindow::MainWindow(Grafo* grafo, QWidget *parent)
    : QMainWindow(parent), grafo(grafo) {

    GrafoWidget* grafoWidget = new GrafoWidget(this);
    grafoWidget->setGrafo(grafo);

    // Definir las posiciones visuales iniciales de los tanques
    int posAmarilloX = 150;
    int posAmarilloY = 150;
    int posAzulX = 150;
    int posAzulY = 450;
    int posCelesteX = 350;
    int posCelesteY = 150;
    int posRojoX = 350;
    int posRojoY = 450;

    // Encontrar los nodos más cercanos a estas posiciones
    int nodoAmarillo = grafo->encontrarNodoCercano(posAmarilloX, posAmarilloY);
    int nodoAzul = grafo->encontrarNodoCercano(posAzulX, posAzulY);
    int nodoCeleste = grafo->encontrarNodoCercano(posCelesteX, posCelesteY);
    int nodoRojo = grafo->encontrarNodoCercano(posRojoX, posRojoY);

    // Crear los tanques y asignarles sus posiciones iniciales (nodos correspondientes)
    TanqueAmarillo* tanqueAmarillo = new TanqueAmarillo(grafo, nodoAmarillo);
    TanqueAzul* tanqueAzul = new TanqueAzul(grafo, nodoAzul);
    TanqueCeleste* tanqueCeleste = new TanqueCeleste(grafo, nodoCeleste);
    TanqueRojo* tanqueRojo = new TanqueRojo(grafo, nodoRojo);

    // Pasar los tanques al GrafoWidget
    grafoWidget->setTanques(tanqueAmarillo, tanqueAzul, tanqueCeleste, tanqueRojo);

    // Establecer el tamaño de la ventana
    setFixedSize(1050, 720);
    setCentralWidget(grafoWidget);

    // Iniciar el temporizador
    timer = new QTimer(this);  // Crear el temporizador
    connect(timer, &QTimer::timeout, this, &MainWindow::finalizarJuego);  // Conectar el temporizador con el slot
    timer->start(300000);  // Establecer que se ejecute en 5 minutos (300,000 ms)
}

MainWindow::~MainWindow() {
    // Liberar memoria si es necesario
}

void MainWindow::finalizarJuego() {
    // Detener el temporizador
    timer->stop();

    // Imprimir el mensaje en consola
    std::cout << "Juego finalizado" << std::endl;

    // Cerrar la ventana
    close();
}
