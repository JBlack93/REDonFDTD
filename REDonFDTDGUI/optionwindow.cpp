#include "optionwindow.h"
#include "ui_optionwindow.h"

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

    ui->xDimBox->setValue(50);
    ui->yDimBox->setValue(50);
    ui->zDimBox->setValue(50);
    ui->stepNumberBox->setValue(50);
    ui->timeStepBox->setValue(50);
}

optionwindow::~optionwindow()
{
    delete ui;
}

void optionwindow::on_buttonBox_accepted()
{
    REDonFDTD::config tempConfig;
    tempConfig.sizeX = ui->xDimBox->value();
    tempConfig.sizeY = ui->yDimBox->value();
    tempConfig.sizeZ = ui->zDimBox->value();
    tempConfig.steps = ui->stepNumberBox->value();
    tempConfig.timeStep = static_cast<long double>(ui->timeStepBox->value()*pow(10,-10));
    emit changeConfig(tempConfig);
    this->close();
}

void optionwindow::on_buttonBox_rejected()
{
    this->close();
}
