#ifndef DISHSHOWBAR_H
#define DISHSHOWBAR_H

#include <QWidget>
#include "Tools/BuyNumBar/buynumbar.h"
#define _DELETE(ptr) if(ptr) {delete ptr;ptr = nullptr;}

namespace Ui {
class DishShowBar;
}

class DishShowBar : public QWidget
{
    Q_OBJECT

    friend class DishIconLabel;
public:
    explicit DishShowBar(QString **controlwin_username,QString DishImagePath,
                         QString DishName,QString DishMoney,QString DishNum,QString DishIndex,
                         QWidget *parent = nullptr);
    ~DishShowBar();

    QString *getDishImagePath();
    QString *getDishName();
    QString *getDishMoney();
    QString *getDishNum();
    QString *getDishIndex();

    void setDishImagePath(QString *t);
    void setDishName(QString *t);
    void setDishMoney(QString *t);
    void setDishNum(QString *t);
    void setDishIndex(QString *t);

signals:
    void addSuccess(DishShowBar *self);
    void deleteSuccess(DishShowBar *self);

private slots:
    void on_addBuyCar_ptn_clicked();

    void on_buyNow_ptn_clicked();
private:
    void writeDataToUserBuyCar(int buyNum);
    void writeDataToUserOrderDetail(int buyNum);

private:
    Ui::DishShowBar *ui;
    QString **controlwin_username;

    QImage *DishImage; QString *DishImagePath;
    QString *DishName;
    QString *DishMoney;
    QString *DishNum;
    QString *DishIndex; // fromDB

    BuyNumBar *buynumbar;
};

#endif // DISHSHOWBAR_H
