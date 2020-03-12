#include <QMessageBox>

#include "optionwindow.h"
#include "ui_optionwindow.h"
#include "REDonFDTD/utilities.hpp"

optionwindow::optionwindow(QWidget *parent)
    : QDialog(parent)

, ui(new Ui::optionwindow)
{
    ui->setupUi(this);
    ui->xDimBox->setRange(0,99);
    ui->yDimBox->setRange(0,99);
    ui->zDimBox->setRange(0,99);
    ui->stepNumberBox->setRange(0,99);
    ui->timeStepBox->setRange(0,99);

    ui->xDimBox->setValue(51);
    ui->yDimBox->setValue(50);
    ui->zDimBox->setValue(50);
    ui->stepNumberBox->setValue(50);
    ui->timeStepBox->setValue(5.0);

    ui->speedLight->hide();
    ui->speedLight->setValue(2.99792458e8);

    ui->xpositionBox->setRange(0,50);
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
}

optionwindow::~optionwindow()
{
    delete ui;
}

void optionwindow::on_buttonBox_accepted()
{
    std::array<double,3> vel = {ui->xvelocityBox->value(),ui->yvelocityBox->value(),ui->zvelocityBox->value()};
    if (REDonFDTD::util::magnitude(vel) > 1) {
        QMessageBox::information(this, "Velocity Error","Source cannot be faster than speed of light!\n");
        return;
    }

    REDonFDTD::config tempConfig;
    tempConfig.sizeX = ui->xDimBox->value();
    tempConfig.sizeY = ui->yDimBox->value();
    tempConfig.sizeZ = ui->zDimBox->value();
    tempConfig.steps = ui->stepNumberBox->value();
    tempConfig.timeStep = static_cast<long double>(ui->timeStepBox->value()*pow(10,-10));

    tempConfig.position[0] = ui->xpositionBox->value();
    tempConfig.position[1] = ui->ypositionBox->value();
    tempConfig.position[2] = ui->zpositionBox->value();

    tempConfig.velocity[0] = ui->xvelocityBox->value();
    tempConfig.velocity[1] = ui->yvelocityBox->value();
    tempConfig.velocity[2] = ui->zvelocityBox->value();
    emit changeConfig(tempConfig);
    this->close();
}

void optionwindow::on_buttonBox_rejected()
{
    this->close();
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
