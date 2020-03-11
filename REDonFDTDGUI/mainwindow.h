#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QThread>
#include <QGraphicsPixmapItem>
#include "optionwindow.h"
#include "REDonFDTD/mesh.hpp"
#include "fdtdcalc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ChangeOutputButton_clicked();
    void updateGraphicsView(int step);
    void simFinishedAlert();

    void on_OptionButton_clicked();

private:
    Ui::MainWindow *ui;
    optionwindow * options;
    QGraphicsScene * scene = new QGraphicsScene();
//    QGraphicsView* graphicsView = new QGraphicsView();
    QGraphicsPixmapItem* item;
    FDTDCalc * calc = new FDTDCalc(this);
};
#endif // MAINWINDOW_H
