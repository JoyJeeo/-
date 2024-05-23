#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QWidget>
#include "registerwin.h"
#include "Windows\Control_Pager\controlwin.h"
#include "Tools/HoverableLabel/hoverablelabel.h"

namespace Ui {
class loginwin;
}

class loginwin : public QWidget
{
    Q_OBJECT

public:
    explicit loginwin(QWidget *parent = nullptr);
    ~loginwin();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_register_pbtn_clicked();
    void after_register_login();
    void after_control_win();
    void on_enter_watchEye();
    void on_leave_watchEye();

    void on_login_pbtn_clicked();

private:
    Ui::loginwin *ui;
    HoverableLabel *watchEye;
    registerwin re;
    controlwin control_win;
};

#endif // LOGINWIN_H
