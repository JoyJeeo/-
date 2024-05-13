#ifndef ORDERDISHSHOWBAR_H
#define ORDERDISHSHOWBAR_H

#include <QWidget>

namespace Ui {
class OrderDishShowBar;
}

class OrderDishShowBar : public QWidget
{
    Q_OBJECT

public:
    explicit OrderDishShowBar(QString imagePath,
                              QString dishName,
                              QString dishMoney,
                              QString dishBuyNum,
                              QString allMoney,
                              QWidget *parent = nullptr);
    ~OrderDishShowBar();

private:
    Ui::OrderDishShowBar *ui;
};

#endif // ORDERDISHSHOWBAR_H
