#include <QMessageBox>

#include "REDonFDTD/utilities.hpp"

#include "optionwindow.h"
#include "ui_optionwindow.h"
#include "guiconfig.h"

optionwindow::optionwindow(QWidget *parent)
    : QDialog(parent)

, ui(new Ui::optionwindow)
{
    ui->setupUi(this);
    ui->xDimBox->setRange(0,100);
    ui->yDimBox->setRange(0,100);
    ui->zDimBox->setRange(0,100);
    ui->stepNumberBox->setRange(0,100);
    ui->timeStepBox->setRange(0,150);

    ui->xDimBox->setValue(51);
    ui->yDimBox->setValue(50);
    ui->zDimBox->setValue(50);
    ui->stepNumberBox->setValue(100);
    ui->timeStepBox->setValue(5.0);

    ui->speedLight->hide();
    ui->speedLight->setValue(2.99792458e8);

    ui->xpositionBox->setRange(0,51);
    ui->ypositionBox->setRange(0,50);
    ui->zpositionBox->setRange(0,50);

    ui->xvelocityBox->setRange(0,1.);
    ui->yvelocityBox->setRange(0,1.);
    ui->zvelocityBox->setRange(0,1.);

    ui->xpositionBox->setValue(25);
    ui->ypositionBox->setValue(25);
    ui->zpositionBox->setValue(25);

    ui->xvelocityBox->setValue(0.0);
    ui->yvelocityBox->setValue(0.5);
    ui->zvelocityBox->setValue(0.0);

    ui->ppwBox->setValue(15.0);

    ui->analyticRangeBox->setRange(0,9);
}

optionwindow::~optionwindow()
{
    delete ui;
}

void optionwindow::on_closeButton_clicked()
{
    std::array<double,3> vel = {ui->xvelocityBox->value(),ui->yvelocityBox->value(),ui->zvelocityBox->value()};
    if (REDonFDTD::util::magnitude(vel) > 1) {
        QMessageBox::information(this, "Velocity Error","Source cannot be faster than speed of light!\n");
        return;
    }
    this->close();
}

void optionwindow::gatherConfig(config::guiConfig MainConfig){
    std::array<double,3> vel = {ui->xvelocityBox->value(),ui->yvelocityBox->value(),ui->zvelocityBox->value()};
    if (REDonFDTD::util::magnitude(vel) > 1) {
        QMessageBox::information(this, "Velocity Error","Source cannot be faster than speed of light!\n");
        return;
    }

    MainConfig.sizeX = ui->xDimBox->value();
    MainConfig.sizeY = ui->yDimBox->value();
    MainConfig.sizeZ = ui->zDimBox->value();
    MainConfig.steps = ui->stepNumberBox->value();
    MainConfig.timeStep = static_cast<long double>(ui->timeStepBox->value()*pow(10,-10));

    MainConfig.position[0] = ui->xpositionBox->value()-0.25;
    MainConfig.position[1] = ui->ypositionBox->value()-0.25;
    MainConfig.position[2] = ui->zpositionBox->value()-0.25;

    MainConfig.velocity[0] = ui->xvelocityBox->value();
    MainConfig.velocity[1] = ui->yvelocityBox->value();
    MainConfig.velocity[2] = ui->zvelocityBox->value();

    MainConfig.source = static_cast<REDonFDTD::sourceType>(ui->SourceBox->currentIndex());

    MainConfig.ExB[0] = ui->ExBxSpinBox->value();
    MainConfig.ExB[1] = ui->ExBySpinBox->value();
    MainConfig.ExB[2] = ui->ExBzSpinBox->value();

    MainConfig.ppw = ui->ppwBox->value();

    MainConfig.analyticRange = ui->analyticRangeBox->value();

    emit changeConfig(MainConfig);
}


void optionwindow::on_xDimBox_valueChanged(int arg1)
{
    ui->xpositionBox->setRange(0,arg1);
}

void optionwindow::on_yDimBox_valueChanged(int arg1)
{
    ui->ypositionBox->setRange(0,arg1);
}

void optionwindow::on_zDimBox_valueChanged(int arg1)
{
    ui->zpositionBox->setRange(0,arg1);
}

void optionwindow::on_SourceBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == QString("Particle")) ui->ppwFrame->hide();
    else if (arg1 == QString("ricker")) ui->ppwFrame->show();
}
