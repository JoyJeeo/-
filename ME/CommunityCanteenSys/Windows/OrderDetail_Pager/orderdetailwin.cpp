#include "orderdetailwin.h"
#include "ui_orderdetailwin.h"
#include "Tools/tool_00_environment.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include "Tools/MenuAlgorithm/menualgorithm.h"
#include <QScrollBar>

orderdetailwin::orderdetailwin(QString control_username,
                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orderdetailwin),
    control_username(control_username)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    QPixmap pixmap("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/Background_PICS/orderDetail.png");//设定图片

//    QPainter p1(&pixmap);
//    p1.setCompositionMode(QPainter::CompositionMode_Source);
//    p1.drawPixmap(0, 0, pixmap);
//    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);

//    //根据QColor中第四个参数设置透明度，0～255
//    p1.fillRect(pixmap.rect(), QColor(179,179,164, 220));
//    p1.end();

    pixmap = MenuAlgorithm::PixmapToRound(pixmap,0,this->width(),this->height());
    QPalette palette;//创建一个调色板对象
    palette.setBrush(this->backgroundRole(),QBrush(pixmap));//用调色板的画笔把映射到pixmap上的图片画到            frame.backgroundRole()这个背景上
    this->setPalette(palette);//设置窗口调色板为palette，窗口和画笔相关联

    ui->scrollArea->setStyleSheet("QScrollArea {background-color:transparent;}");
    ui->scrollArea->viewport()->setStyleSheet("QScrollArea {background-color:transparent;}");

    // 设置垂直滚动条样式
    QString verticalScrollBarStyle =
        "QScrollBar:vertical {"
           "    border: none;"
           "    background: transparent;"
           "    width: 12px;"
           "    margin: 16px 0 16px 0;"
           "}"
           "QScrollBar:vertical:hover {"
           "    background: #b3d9ff;"
           "}"
           "QScrollBar::handle:vertical {"
           "    background: #5dade2;"
           "    border-radius: 6px;"
           "    min-height: 30px;"
           "}"
           "QScrollBar::handle:vertical:hover {"
           "    background: #2e86c1;"
           "}"
           "QScrollBar::add-line:vertical {"
           "    height: 16px;"
           "    subcontrol-position: bottom;"
           "    subcontrol-origin: margin;"
           "}"
           "QScrollBar::sub-line:vertical {"
           "    height: 16px;"
           "    subcontrol-position: top;"
           "    subcontrol-origin: margin;"
           "}";

    ui->scrollArea->verticalScrollBar()->setStyleSheet(verticalScrollBarStyle);

    // 设置水平滚动条样式
    QString horizontalScrollBarStyle =
        "QScrollBar:horizontal {"
           "    border: none;"
           "    background: transparent;"
           "    height: 12px;"
           "    margin: 0 16px 0 16px;"
           "}"
           "QScrollBar:horizontal:hover {"
           "    background: #b3d9ff;"
           "}"
           "QScrollBar::handle:horizontal {"
           "    background: #5dade2;"
           "    border-radius: 6px;"
           "    min-width: 30px;"
           "}"
           "QScrollBar::handle:horizontal:hover {"
           "    background: #2e86c1;"
           "}"
           "QScrollBar::add-line:horizontal {"
           "    width: 16px;"
           "    subcontrol-position: right;"
           "    subcontrol-origin: margin;"
           "}"
           "QScrollBar::sub-line:horizontal {"
           "    width: 16;"
           "    subcontrol-position: left;"
           "    subcontrol-origin: margin;"
           "}";

    ui->scrollArea->horizontalScrollBar()->setStyleSheet(horizontalScrollBarStyle);

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








