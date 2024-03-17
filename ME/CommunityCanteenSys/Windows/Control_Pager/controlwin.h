#ifndef CONTROLWIN_H
#define CONTROLWIN_H

#include <QMainWindow>
#include "Windows\Admin_Paper\adminwin.h "

namespace Ui {
class controlwin;
}

class controlwin : public QMainWindow
{
    Q_OBJECT
    friend class loginwin;
public:
    explicit controlwin(QWidget *parent = nullptr);
    ~controlwin();

signals:
    void back_login_paper();

private slots:
    void on_back_login_btn_clicked();
    void on_admin_back();
    void on_admin_btn_clicked();

private:
    void triggered();
    void set_user_name(QString name);

private:
    QString user_name;

private:
    Ui::controlwin *ui;
    adminwin *admin_win;
};

#endif // CONTROLWIN_H
