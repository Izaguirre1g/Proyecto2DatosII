#include "mainwindow.h"
#include "GrafoWidget.h"
#include <cmath>
#include <QTimer>
#include <QMessageBox>  // Incluir para mostrar el mensaje
#include <iostream>

MainWindow::MainWindow(Grafo* grafo, QWidget *parent)
    : QMainWindow(parent), grafo(grafo) {

    GrafoWidget* grafoWidget = new GrafoWidget(this);
    grafoWidget->setGrafo(grafo);

    // Conectar la señal juegoFinalizado de GrafoWidget con la función finalizarJuego de MainWindow
    connect(grafoWidget, &GrafoWidget::juegoFinalizado, this, &MainWindow::mostrarMensajeYSalir); //BORRAR /////////////////////

    int posiciones[8][2] = {
        {100, 100}, {600, 100},  // Amarillo 1 y 2
        {600, 650}, {100, 650},  // Azul 1 y 2
        {350, 100}, {900, 100},  // Celeste 1 y 2
        {900, 650}, {350, 650}   // Rojo 1 y 2
    };
    TanqueAmarillo* tanqueAmarillo1 = new TanqueAmarillo(grafo, grafo->encontrarNodoCercano(posiciones[0][0], posiciones[0][1]));
    TanqueAmarillo* tanqueAmarillo2 = new TanqueAmarillo(grafo, grafo->encontrarNodoCercano(posiciones[1][0], posiciones[1][1]));
    TanqueAzul* tanqueAzul1 = new TanqueAzul(grafo, grafo->encontrarNodoCercano(posiciones[2][0], posiciones[2][1]));
    TanqueAzul* tanqueAzul2 = new TanqueAzul(grafo, grafo->encontrarNodoCercano(posiciones[3][0], posiciones[3][1]));
    TanqueCeleste* tanqueCeleste1 = new TanqueCeleste(grafo, grafo->encontrarNodoCercano(posiciones[4][0], posiciones[4][1]));
    TanqueCeleste* tanqueCeleste2 = new TanqueCeleste(grafo, grafo->encontrarNodoCercano(posiciones[5][0], posiciones[5][1]));
    TanqueRojo* tanqueRojo1 = new TanqueRojo(grafo, grafo->encontrarNodoCercano(posiciones[6][0], posiciones[6][1]));
    TanqueRojo* tanqueRojo2 = new TanqueRojo(grafo, grafo->encontrarNodoCercano(posiciones[7][0], posiciones[7][1]));

    grafoWidget->setTanques(tanqueAmarillo1, tanqueAmarillo2, tanqueAzul1, tanqueAzul2, tanqueCeleste1, tanqueCeleste2, tanqueRojo1, tanqueRojo2);

    setFixedSize(1050, 720);
    setCentralWidget(grafoWidget);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::finalizarJuego);
    timer->start(300000);  // 5 minutos
}

MainWindow::~MainWindow() {}

void MainWindow::mostrarMensajeYSalir(const QString &ganador) { //BORRAR /////////////////////////
    QMessageBox::information(this, "Juego Finalizado", "El ganador es: " + ganador);  // Mostrar mensaje
    close();  // Cerrar la ventana principal
}

void MainWindow::finalizarJuego() {
    timer->stop();
    GrafoWidget* grafoWidget = qobject_cast<GrafoWidget*>(centralWidget());

    if (grafoWidget) {
        QString ganador = grafoWidget->determinarGanador();  // Obtener el nombre del ganador
        QMessageBox::information(this, "Juego Finalizado", "El ganador es: " + ganador);  // Mostrar mensaje
        close();
    }
}
