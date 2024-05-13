#ifndef ORDERDETAILWIN_H
#define ORDERDETAILWIN_H

#include <QWidget>
#include "Tools/OrderDetailTools/OderDetailBar/oderdetailbar.h"

namespace Ui {
class orderdetailwin;
}

class orderdetailwin : public QWidget
{
    Q_OBJECT

public:
    explicit orderdetailwin(QString control_username, QWidget *parent = nullptr);
    ~orderdetailwin();

private slots:
    void deleteDishDetail(OderDetailBar *t);

private:
    void dishDetailInitFromDB();

    void showDishDetail();

private:
    Ui::orderdetailwin *ui;

    QString control_username;
    QVector<OderDetailBar*> orderDetails;
};

#endif // ORDERDETAILWIN_H
