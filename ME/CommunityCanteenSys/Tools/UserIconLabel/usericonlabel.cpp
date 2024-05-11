#include "usericonlabel.h"
#include <QFileDialog>
#include <QMouseEvent>

UserIconLabel::UserIconLabel(QWidget *parent) : QLabel(parent)
{

}

void UserIconLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        QString userIconPath = QFileDialog::getOpenFileName(Q_NULLPTR,
                                                       QObject::tr("Select UserIcon"),
                                                       QObject::tr("../"),
                                                       QObject::tr("File(*.jpg);;File(*.png);;File(*.ico);;"
                                                                   "All(*.*)"));
        if(userIconPath.size() > 0) emit back(userIconPath);
    }

}
