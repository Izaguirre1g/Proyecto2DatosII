#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Grafo.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Grafo* grafo, QWidget *parent = nullptr);  // Constructor que recibe el puntero a Grafo
    ~MainWindow();

private:
    Grafo* grafo;  // Guardamos una referencia al grafo
};

#endif // MAINWINDOW_H
