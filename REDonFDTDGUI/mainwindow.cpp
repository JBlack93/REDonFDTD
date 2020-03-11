#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QThread>
#include <iostream>

#include "mainwindow.h"
#include "optionwindow.h"
#include "ui_mainwindow.h"
#include "fdtdcalc.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

, ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i<100; ++i){
        ui->timeBox->addItem("Step "+ QString::number(i+1));
    }
    QString filename = "/home/black/projects/REDonFDTD/REDonFDTDGUI/Ex1.png";

    QPixmap tmpmap (filename, 0, Qt::AutoColor);
    this->item = scene->addPixmap ( tmpmap.scaled (ui->graphicsView->width(), ui->graphicsView->height()) );
    this->scene->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    QThread * calcThread = new QThread(this);
    calc->moveToThread(calcThread);

    connect(ui->RunButton, SIGNAL(clicked()),
              calc, SLOT(runFDTDSim()));

    connect(calc, SIGNAL(newPlotAvailable(int)),
              this, SLOT(updateGraphicsView(int)));

    connect(calc, SIGNAL(FDTDSimCompleted()),
              this, SLOT(simFinishedAlert()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::simFinishedAlert(){
    QMessageBox::information(this, "FDTDSim","Simulation Finished!\n");
}

void MainWindow::on_ChangeOutputButton_clicked()
{
    QMessageBox::information(this, "Title","This functionality is yet to be implemented\n");
}

void MainWindow::on_OptionButton_clicked()
{
    options = new optionwindow(this);
    options->show();
}

void MainWindow::updateGraphicsView(int step){
    QString file = "output/Ex"+QString::number(step)+".png";
    QPixmap tmpmap (file, 0, Qt::AutoColor);
    item = scene->addPixmap( tmpmap.scaled (ui->graphicsView->width(), ui->graphicsView->height()) );
    scene->update();
    QApplication::processEvents();
}

