#ifndef BUYCARDISHSHOWBAR_H
#define BUYCARDISHSHOWBAR_H

#include <QWidget>
#include <QCheckBox>

namespace Ui {
class BuyCarDishShowBar;
}

class BuyCarDishShowBar : public QWidget
{
    Q_OBJECT

public:
    explicit BuyCarDishShowBar(QString imagePath,
                               QString dishName,
                               QString dishMoney,
                               QString dishBuyNum,
                               QString allMoney,
                               QWidget *parent = nullptr);
    ~BuyCarDishShowBar();

    QString getImagePath();
    QString getDishName();
    QString getDishMoney();
    QString getDishBuyNum();
    QString getAllMoney();

    QCheckBox* getSelectCheckBox();

private:
    Ui::BuyCarDishShowBar *ui;

    QString imagePath;
    QString dishName;
    QString dishMoney;
    QString dishBuyNum;
    QString allMoney;
};

#endif // BUYCARDISHSHOWBAR_H
