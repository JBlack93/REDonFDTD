#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include <QDialog>

#include "REDonFDTD/config.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class optionwindow; }
QT_END_NAMESPACE

class optionwindow : public QDialog
{
    Q_OBJECT

public:
    optionwindow(QWidget *parent = nullptr);
    ~optionwindow();

signals:
    void changeConfig(REDonFDTD::config tempConfig);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_xDimBox_valueChanged(int arg1);
    void on_yDimBox_valueChanged(int arg1);
    void on_zDimBox_valueChanged(int arg1);

private:
    Ui::optionwindow *ui;
};

#endif // OPTIONWINDOW_H
