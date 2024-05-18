#ifndef DISHICONLABEL_H
#define DISHICONLABEL_H

#include <QLabel>
#include "Tools/DishShowBar/dishshowbar.h"


class DishIconLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DishIconLabel(QWidget *parent = nullptr);
    ~DishIconLabel();

    void setDishShowBar(DishShowBar *t); // 由于topWin，

signals:
    void addSuccess();
    void deleteSuccess();

protected:
    void mousePressEvent(QMouseEvent *ev) override;


private:
    DishShowBar *dishShowBar;

};

#endif // DISHICONLABEL_H
