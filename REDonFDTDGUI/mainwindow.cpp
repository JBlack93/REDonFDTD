#include <QMessageBox>

#include "mainwindow.h"
#include "optionwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

, ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i<100; ++i){
        ui->comboBox_3->addItem("Step "+ QString::number(i+1));
    }
    QString filename = "/home/black/projects/REDonFDTD/REDonFDTDGUI/gnuplot.png";

    QPixmap tmpmap (filename, 0, Qt::AutoColor);
    item = scene->addPixmap ( tmpmap.scaled (ui->graphicsView->width(), ui->graphicsView->height()) );
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    QString Message("This functionality is yet to be implemented\n");
    QString Option1(ui->comboBox->currentText());
    QString Option2(ui->comboBox_2->currentText());
    QString Option3(ui->comboBox_3->currentText());
    QString Option4(ui->comboBox_4->currentText());
    Message.append("\nComponent Requested: ");
    Message.append(Option1);
    Message.append("\nPlane Requested: ");
    Message.append(Option2);
    Message.append("\nTimestamp Requested: ");
    Message.append(Option3);
    Message.append("\nPlotting : ");
    Message.append(Option4);
    QMessageBox::information(this, "Title",Message);
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "Title","This functionality is yet to be implemented\n");
}

void MainWindow::on_toolButton_clicked()
{
    options = new optionwindow(this);
    options->show();
}
