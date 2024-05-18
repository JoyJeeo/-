#include "carouselchartbar.h"
#include <QFileDialog>
#include <QMouseEvent>
#include "Tools/tool_00_environment.h"
#include <QSqlQuery>
#include <QDebug>

CarouselChartBar::CarouselChartBar(QString **control_name,
                                   QString annoImagePath,
                                   QString annoIndex,
                                   QWidget *parent)
    : QLabel(parent),
      control_name(control_name),
      annoImagePath(annoImagePath),
      annoIndex(annoIndex)
{
    if(annoImagePath.size() != 0) this->setPixmap(QPixmap(annoImagePath)); // label添加图片
    this->setScaledContents(true); // 设置标签为可扩展内容，才能够设置标签的大小可变
    this->resize(parent->size()); // 设置label的大小与widget一样
    this->hide();
}

CarouselChartBar::~CarouselChartBar()
{

}

void CarouselChartBar::mousePressEvent(QMouseEvent *ev)
{
    if(**control_name != "admin") return;
    if(ev->button() == Qt::LeftButton)
    {
        emit selectStart();

        QString picPath = QFileDialog::getOpenFileName(Q_NULLPTR,
                                                       QObject::tr("Select Set CarouselImage"),
                                                       QObject::tr("../"),
                                                       QObject::tr("File(*.jpg);;File(*.png);;File(*.ico);;"
                                                                   "All(*.*)"));
        if(picPath.size() != 0)
        {
            annoImagePath = picPath;
            this->setPixmap(QPixmap(annoImagePath));
            this->setScaledContents(true);
            this->resize(this->size());

            QSqlQuery query(*DB);
            QString sql = QString("update AnnoInfo set AnnoImagePath = '%1'"
                                  "where AnnoIndex = %2;")
                    .arg(annoImagePath)
                    .arg(annoIndex);

            query.exec(sql);
        }


        emit selectEnd();
    }
}
