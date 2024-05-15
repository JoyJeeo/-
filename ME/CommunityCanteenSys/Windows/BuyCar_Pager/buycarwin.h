#ifndef BUYCARWIN_H
#define BUYCARWIN_H

#include <QWidget>
#include "Tools/BuyCarTools/BuyCarDishShowBar/buycardishshowbar.h"

namespace Ui {
class buycarwin;
}

class buycarwin : public QWidget
{
    Q_OBJECT

public:
    explicit buycarwin(QString control_username,QWidget *parent = nullptr);
    ~buycarwin();

private slots:
    void refreshAllSelect_Allpay();

    void on_allSelect_ckbox_clicked();

    void on_deleteSelect_ptn_clicked();

    void on_cancel_ptn_clicked();

    void on_buy_ptn_clicked();

private:
    void buyCarDishInitFromDB();

    void showBuyCarDish();

private:
    Ui::buycarwin *ui;

    QString control_username;
    QVector<BuyCarDishShowBar*> buyCarDishes;
};

#endif // BUYCARWIN_H
