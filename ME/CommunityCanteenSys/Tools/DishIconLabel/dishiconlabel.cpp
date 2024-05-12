#include "dishiconlabel.h"
#include "Tools/DishInfoBar/dishinfobar.h"
#include <QMouseEvent>
#include <QDebug>

DishIconLabel::DishIconLabel(QWidget *parent) :
    QLabel(parent),
    dishShowBar((DishShowBar*)parent) // 固定调用，则其父窗体就是赋予的父窗体
{

}

void DishIconLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        if(*dishShowBar->controlwin_username == "admin")
        {
            DishInfoBar *dishInfo = new DishInfoBar(dishShowBar);
            dishInfo->setAttribute(Qt::WA_DeleteOnClose);
            dishInfo->show();
        }
    }
}
