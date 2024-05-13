#ifndef DETAILBAR_H
#define DETAILBAR_H

#include <QWidget>
#include "Tools/OrderDetailTools/OrderDishShowBar/orderdishshowbar.h"

namespace Ui {
class DetailBar;
}

class DetailBar : public QWidget
{
    Q_OBJECT

public:
    explicit DetailBar(QString winTitle,
                       QString controlwin_username,QString takeOrderTime,
                       QWidget *parent = nullptr);
    ~DetailBar();

private slots:
    void on_ok_ptn_clicked();

private:
    void orderDishDetailDataInitACalFromDB();

    void detailShow();

private:
    Ui::DetailBar *ui;

    QString controlwin_username;
    QString takeOrderTime;

    QVector<OrderDishShowBar*> dishDetails;
};

#endif // DETAILBAR_H
