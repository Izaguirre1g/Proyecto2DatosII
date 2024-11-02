#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>  // Incluir la clase QTimer
#include "Grafo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Grafo* grafo, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void finalizarJuego();  // Slot que cierra la ventana y muestra el mensaje
    void mostrarMensajeYSalir(const QString &ganador);

private:
    Ui::MainWindow *ui;
    Grafo* grafo;  // Puntero al grafo
    QTimer* timer;  // Puntero al temporizador
};

#endif // MAINWINDOW_H
