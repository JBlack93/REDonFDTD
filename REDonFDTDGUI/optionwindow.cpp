#include "optionwindow.h"
#include "ui_optionwindow.h"

optionwindow::optionwindow(QWidget *parent)
    : QMainWindow(parent)

, ui(new Ui::optionwindow)
{
    ui->setupUi(this);
}

optionwindow::~optionwindow()
{
    delete ui;
}
