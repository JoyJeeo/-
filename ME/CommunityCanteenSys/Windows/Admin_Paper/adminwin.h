#ifndef ADMINWIN_H
#define ADMINWIN_H

#include <QWidget>

namespace Ui {
class adminwin;
}

class adminwin : public QWidget
{
    Q_OBJECT

public:
    explicit adminwin(QWidget *parent = nullptr);
    ~adminwin();

signals:
    void back();

private slots:
    void on_back_clicked();

private:
    Ui::adminwin *ui;
};

#endif // ADMINWIN_H
