#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Grafo.h"  // Incluir el archivo de encabezado de Grafo

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Constructor que recibe el puntero a Grafo y un QWidget parent
    explicit MainWindow(Grafo* grafo, QWidget *parent = nullptr);
    ~MainWindow();

    // Método para mostrar resultados en la interfaz
    void mostrarResultado(const QString &resultado);

private:
    Ui::MainWindow *ui;  // Puntero a la interfaz de usuario
    Grafo* grafo;        // Puntero a la instancia de Grafo
};

#endif // MAINWINDOW_H
