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
#include "guiconfig.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

, ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsRect->hide();

    this->scene->setSceneRect(ui->graphicsRect->rect());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    calc->moveToThread(calcThread);

    connect(this, SIGNAL(run()),
              calc, SLOT(runFDTDSim()));

    connect(this, SIGNAL(cancelRequest()),
              calc, SLOT(cancel()));

    connect(calc, SIGNAL(FDTDSimCancelled()),
              this, SLOT(cancelSuccessful()));

    connect(calc, SIGNAL(newPlotAvailable(int)),
              this, SLOT(updateGraphicsView(int)));

    connect(calc, SIGNAL(FDTDSimCompleted()),
              this, SLOT(simFinishedAlert()));

    connect(options, SIGNAL(changeConfig(config::guiConfig)),
            calc, SLOT(updateConfig(config::guiConfig)));

    connect(calc, SIGNAL(signalSlider(int)),
            this, SLOT(enableSlider(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cancelSuccessful(){
    QMessageBox::information(this, "FDTDSim","Simulation Stopped Successfully!\n");
}


void MainWindow::simFinishedAlert(){
    QMessageBox::information(this, "FDTDSim","Simulation Finished!\n");
}

void MainWindow::on_RunButton_clicked()
{
    if (ui->planeBox->currentIndex() != 0) {
        QMessageBox::information(this, "Plane Error", "Currently only XY plane can be outputted.");
        return;
    }
    config::guiConfig MainConfig;
    MainConfig.component = static_cast<config::Component>(ui->componentBox->currentIndex());
    MainConfig.plane = static_cast<config::Plane>(ui->planeBox->currentIndex());
    MainConfig.plot = static_cast<config::PlotType>(ui->plotBox->currentIndex());
    MainConfig.interpolate = (! ui->interpCheckBox->isChecked());
    options->gatherConfig(MainConfig);
    currentRunConfig = MainConfig;
    emit run();
}


void MainWindow::on_pauseButton_clicked()
{
    emit cancelRequest();
}

void MainWindow::on_OptionButton_clicked()
{
    options->show();
}

void MainWindow::updateGraphicsView(int step){
    QString component = QString::fromStdString(currentRunConfig.getComponent());
    QString plane = QString::fromStdString(currentRunConfig.getPlane());
    QString file = "output/"+component+plane+QString::number(step)+".png";
    QPixmap tmpmap (file, 0, Qt::AutoColor);
    ui->horizontalSlider->setSliderPosition(step);
    item = scene->addPixmap( tmpmap.scaled (ui->graphicsRect->width(), ui->graphicsRect->height()) );
    scene->update();
    QApplication::processEvents();
}

void MainWindow::enableSlider(int steps)
{
    ui->horizontalSlider->setEnabled(true);
    ui->horizontalSlider->setRange(0, steps);
    ui->MaxValueLabel->setText(QString::number(steps));
}

void MainWindow::on_horizontalSlider_valueChanged(int position)
{
    ui->StepValueLabel->setText(QString::number(position));
    updateGraphicsView(position);
}
