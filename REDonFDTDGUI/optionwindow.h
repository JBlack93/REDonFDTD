#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class optionwindow; }
QT_END_NAMESPACE

class optionwindow : public QMainWindow
{
    Q_OBJECT

public:
    optionwindow(QWidget *parent = nullptr);
    ~optionwindow();


private:
    Ui::optionwindow *ui;
};

#endif // OPTIONWINDOW_H
