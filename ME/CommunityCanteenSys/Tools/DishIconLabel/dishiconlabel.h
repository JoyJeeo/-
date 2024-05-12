#ifndef DISHICONLABEL_H
#define DISHICONLABEL_H

#include <QLabel>
#include "Tools/DishShowBar/dishshowbar.h"


class DishIconLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DishIconLabel(QWidget *parent = nullptr);

signals:

protected:
    void mousePressEvent(QMouseEvent *ev) override;


private:
    DishShowBar *dishShowBar;

};

#endif // DISHICONLABEL_H
