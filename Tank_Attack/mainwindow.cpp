#include "mainwindow.h"
#include "ui_mainwindow.h"  // Asegúrate de tener este include

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)  // Inicializa el puntero 'ui'
{
    ui->setupUi(this);  // Configurar la interfaz de usuario
}

MainWindow::~MainWindow()
{
    delete ui;  // Liberar la memoria asignada para 'ui'
}
