#include "optionwindow.h"
#include "ui_optionwindow.h"

optionwindow::optionwindow(QWidget *parent)
    : QDialog(parent)

, ui(new Ui::optionwindow)
{
    ui->setupUi(this);
}

optionwindow::~optionwindow()
{
    delete ui;
}

void optionwindow::on_buttonBox_accepted()
{
    this->close();
}

void optionwindow::on_buttonBox_rejected()
{
    this->close();
}
