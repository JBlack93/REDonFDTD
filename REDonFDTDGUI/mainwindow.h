#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QThread>
#include <QGraphicsPixmapItem>

#include "REDonFDTD/mesh.hpp"

#include "optionwindow.h"
#include "fdtdcalc.h"
#include "guiconfig.h"

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
    void on_RunButton_clicked();
    void on_pauseButton_clicked();
    void updateGraphicsView(int step);
    void simFinishedAlert();
    void on_OptionButton_clicked();
    void enableSlider(int steps);
    void on_horizontalSlider_valueChanged(int position);

signals:
    void run();

private:
    Ui::MainWindow *ui;
    optionwindow * options = new optionwindow(this);
    QGraphicsScene * scene = new QGraphicsScene();
    QGraphicsPixmapItem* item;
    FDTDCalc * calc = new FDTDCalc(this);
};
#endif // MAINWINDOW_H
