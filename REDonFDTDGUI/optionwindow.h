#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include <QDialog>

#include "guiconfig.h"

QT_BEGIN_NAMESPACE
namespace Ui { class optionwindow; }
QT_END_NAMESPACE

class optionwindow : public QDialog
{
    Q_OBJECT

public:
    optionwindow(QWidget *parent = nullptr);
    ~optionwindow();

    void gatherConfig(config::guiConfig MainConfig);

signals:
    void changeConfig(config::guiConfig tempConfig);

private slots:
    void on_xDimBox_valueChanged(int arg1);
    void on_yDimBox_valueChanged(int arg1);
    void on_zDimBox_valueChanged(int arg1);
    void on_SourceBox_currentTextChanged(const QString &arg1);
    void on_closeButton_clicked();

private:
    Ui::optionwindow *ui;
};

#endif // OPTIONWINDOW_H
