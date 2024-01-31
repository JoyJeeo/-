#ifndef CONTROLWIN_H
#define CONTROLWIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class controlwin; }
QT_END_NAMESPACE

class controlwin : public QMainWindow
{
    Q_OBJECT

public:
    controlwin(QWidget *parent = nullptr);
    ~controlwin();

private:
    Ui::controlwin *ui;
};
#endif // CONTROLWIN_H
