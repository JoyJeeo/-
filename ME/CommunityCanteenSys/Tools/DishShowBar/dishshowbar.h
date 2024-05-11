#ifndef DISHSHOWBAR_H
#define DISHSHOWBAR_H

#include <QWidget>
#include "Tools/BuyNumBar/buynumbar.h"

namespace Ui {
class DishShowBar;
}

class DishShowBar : public QWidget
{
    Q_OBJECT

public:
    explicit DishShowBar(QString DishImagePath,
                         QString DishName,QString DishMoney,QString DishNum,
                         QWidget *parent = nullptr);
    ~DishShowBar();

    QImage *getDishImage();
    QString *getDishName();
    QString *getDishMoney();
    QString *getDishNum();

    void setDishImage(QImage *t);
    void setDishName(QString *t);
    void setDishMoney(QString *t);
    void setDishNum(QString *t);

private slots:
    void on_addBuyCar_ptn_clicked();

    void on_buyNow_ptn_clicked();

private:
    Ui::DishShowBar *ui;

    QImage *DishImage;
    QString *DishName;
    QString *DishMoney;
    QString *DishNum;

    BuyNumBar *buynumbar;
};

#endif // DISHSHOWBAR_H
