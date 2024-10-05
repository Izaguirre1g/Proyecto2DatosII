#include "mainwindow.h"
#include "GrafoWidget.h"
#include <cmath>

MainWindow::MainWindow(Grafo* grafo, QWidget *parent)
    : QMainWindow(parent), grafo(grafo) {

    GrafoWidget* grafoWidget = new GrafoWidget(this);
    grafoWidget->setGrafo(grafo);

    // Calcular el centro del grafo en términos de coordenadas de pantalla
    int centroX = width() / 2;
    int centroY = height() / 2;

    // Encontrar el nodo más cercano al centro
    int nodoCercanoAlCentro = -1;
    double distanciaMinima = std::numeric_limits<double>::max();
    int numNodos = grafo->getNumNodos();

    for (int i = 0; i < numNodos; ++i) {
        int x = grafo->getPosicionX(i);
        int y = grafo->getPosicionY(i);
        double distancia = std::sqrt(std::pow(x - centroX, 2) + std::pow(y - centroY, 2));

        if (distancia < distanciaMinima) {
            distanciaMinima = distancia;
            nodoCercanoAlCentro = i;
        }
    }

    // Crear los tanques y hacer que todos empiecen en el nodo más cercano al centro
    TanqueAmarillo* tanqueAmarillo = new TanqueAmarillo(grafo, nodoCercanoAlCentro);
    TanqueAzul* tanqueAzul = new TanqueAzul(grafo, nodoCercanoAlCentro);
    TanqueCeleste* tanqueCeleste = new TanqueCeleste(grafo, nodoCercanoAlCentro);
    TanqueRojo* tanqueRojo = new TanqueRojo(grafo, nodoCercanoAlCentro);

    // Pasar los tanques al GrafoWidget
    grafoWidget->setTanques(tanqueAmarillo, tanqueAzul, tanqueCeleste, tanqueRojo);

    // Establecer el tamaño de la ventana
    setFixedSize(1050, 720);
    setCentralWidget(grafoWidget);
}

MainWindow::~MainWindow() {
    // Liberar memoria si es necesario
}
