#ifndef CONTROLWIN_H
#define CONTROLWIN_H

#include <QMainWindow>
#include "Windows\Admin_Paper\adminwin.h "
#include "Tools/CarouselChart/carouselchart.h"
#include "Tools/DishTurnPageBar/dishturnpagebar.h"

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
    void showUserIcon();
private slots:
    void setUserIcon(QString userIconPath);

    void on_buy_car_btn_clicked();

    void on_order_details_btn_clicked();

private:
    QString *user_name;

private:
    Ui::controlwin *ui;
    CarouselChart *carouselchart;
    DishTurnPageBar *dishTurnPageBar;
};

#endif // CONTROLWIN_H
