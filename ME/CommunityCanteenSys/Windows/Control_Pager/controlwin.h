#ifndef CONTROLWIN_H
#define CONTROLWIN_H

#include <QMainWindow>

namespace Ui {
class controlwin;
}

class controlwin : public QMainWindow
{
    Q_OBJECT

public:
    explicit controlwin(QWidget *parent = nullptr);
    ~controlwin();

private:
    Ui::controlwin *ui;
};

#endif // CONTROLWIN_H
