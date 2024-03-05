#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QWidget>
#include "registerwin.h"

namespace Ui {
class loginwin;
}

class loginwin : public QWidget
{
    Q_OBJECT

public:
    explicit loginwin(QWidget *parent = nullptr);
    ~loginwin();

private slots:
    void on_register_pbtn_clicked();
    void after_register_login();

    void on_login_pbtn_clicked();

private:
    Ui::loginwin *ui;
    registerwin *re;
};

#endif // LOGINWIN_H
