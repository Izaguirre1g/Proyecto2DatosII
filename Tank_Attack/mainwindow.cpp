#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::mostrarResultado(const QString &resultado) {
    ui->textEdit->append(resultado); // Asegúrate de que 'textEdit' es el nombre correcto del widget
}

MainWindow::~MainWindow()
{
    delete ui;
}
