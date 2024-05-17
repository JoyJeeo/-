#include "orderdetailwin.h"
#include "ui_orderdetailwin.h"
#include "Tools/tool_00_environment.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

orderdetailwin::orderdetailwin(QString control_username,
                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderdetailwin),
    control_username(control_username)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    this->setWindowTitle(control_username + "的订单详情");

    QImage *image = new QImage("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/OrderDetail_ICONs/oderDetailIcon.png");
    image = new QImage(image->scaled(61, 61, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->orderIcon_lab->setPixmap(QPixmap::fromImage(*image));

    dishDetailInitFromDB();
    showDishDetail();
}

orderdetailwin::~orderdetailwin()
{
    delete ui;
    for(int i = 0;i < orderDetails.size();i++)
    {
        if(orderDetails[i])
        {
            delete orderDetails[i];
            orderDetails[i] = nullptr;
        }
    }
}

void orderdetailwin::deleteDishDetail(OderDetailBar *t)
{
    QString orderDetailTable = control_username + "OrderDetail";

    for(int i = 0;i < orderDetails.size();i++)
    {
        if(orderDetails[i] == t)
        {
            QSqlQuery query(*DB);
            QString sql = QString("delete from %1 "
                                  "where TakeOrderTime = '%2';")
                    .arg(orderDetailTable)
                    .arg(t->getTakeOrderTime());

            if(!query.exec(sql)) // 重复删除不会报错！【不能产生多个窗口同时控制】
            {
                QMessageBox::critical(nullptr,"删除失败","删除订单详情失败");
                return;
            }

            if(orderDetails[i]) delete orderDetails[i];
            orderDetails.remove(i);
            showDishDetail();
            break;
        }
    }
}

void orderdetailwin::dishDetailInitFromDB()
{
    QString orderDetailTable = control_username + "OrderDetail";

    QSqlQuery query(*DB);
    QString sql = QString("select TakeOrderTime from %1 group by TakeOrderTime "
                          "order by TakeOrderTime desc;")
            .arg(orderDetailTable);

    query.exec(sql);

    while(query.next())
    {
        OderDetailBar *t = new OderDetailBar(control_username, query.value("TakeOrderTime").toString()
                                             , ui->scrollAreaContents);
        connect(t, &OderDetailBar::deleteOrder, this, &orderdetailwin::deleteDishDetail);
        orderDetails.push_back(t);
    }
}

void orderdetailwin::showDishDetail()
{
    int x = 0, y = 20;
    int dx = 0, dy = 60;

    for(int i = 0;i < orderDetails.size();i++)
    {
        orderDetails[i]->move(x + dx, y + dy * i);
    }

    // 重置content的高度，产生滚动条
    int realHeight = y + orderDetails.size() * dy;
    if(realHeight > ui->scrollAreaContents->height())
        ui->scrollAreaContents->setMinimumHeight(realHeight);
}








