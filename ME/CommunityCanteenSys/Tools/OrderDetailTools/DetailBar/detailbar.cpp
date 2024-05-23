#include "detailbar.h"
#include "ui_detailbar.h"
#include "Tools/tool_00_environment.h"
#include <QSqlQuery>
#include "Tools/MenuAlgorithm/menualgorithm.h"
#include <QDebug>
#include <QScrollBar>

DetailBar::DetailBar(QString winTitle,
                     QString controlwin_username,QString takeOrderTime,
                     QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailBar),
    controlwin_username(controlwin_username),
    takeOrderTime(takeOrderTime)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    QPixmap pixmap("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/Background_PICS/orderDetailBar.jpg");//设定图片

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

    this->setWindowTitle(controlwin_username + "的" + winTitle);
    ui->winTitle->setText(winTitle);

    orderDishDetailDataInitACalFromDB();
    detailShow();
}

DetailBar::~DetailBar()
{
    delete ui;
    for(int i = 0;i < dishDetails.size();i++)
    {
        if(dishDetails[i])
        {
            delete dishDetails[i];
            dishDetails[i] = nullptr;
        }
    }
}

void DetailBar::on_ok_ptn_clicked()
{
    this->close();
}

void DetailBar::orderDishDetailDataInitACalFromDB()
{
    int allPay = 0;
    QString orderDetailTable = controlwin_username + "OrderDetail";

    QSqlQuery query(*DB);
    QString sql = QString("select * from %1 where TakeOrderTime = '%2';")
            .arg(orderDetailTable)
            .arg(takeOrderTime);
    query.exec(sql);

    while(query.next())
    {
        QString DishName = query.value("DishName").toString();
        QString DishMoney = query.value("DishMoney").toString();
        QString DishBuyNum = query.value("DishBuyNum").toString();
        QString DishImagePath = query.value("DishImagePath").toString();

        int money = MenuAlgorithm::GetQStringByFirstNum(DishMoney);
        int buyNum = MenuAlgorithm::GetQStringByFirstNum(DishBuyNum);
        int dishPay = money * buyNum;

        OrderDishShowBar *t = new OrderDishShowBar(DishImagePath,DishName,DishMoney,DishBuyNum,
                                                   "总额：" + QString::number(dishPay) + "元"
                                                   ,ui->scrollAreaContents);

        // 菜品order加入容器
        dishDetails.push_back(t);
        // 统计所有菜品总额
        allPay += dishPay;
    }

    // 将总额上传上层
    ui->allPay_lab->setText("总计金额：" + QString::number(allPay) + "元");
}

void DetailBar::detailShow()
{
    int x = 30,y = 10;
    int dx = 170, dy = 200;

    for(int i = 0;i < dishDetails.size();i++)
    {
        dishDetails[i]->move(x + dx * (i % 4), y + dy * (i / 4));
    }

    // 重置content的高度，产生滚动条
    int realHeight = y + (dishDetails.size() / 4 + 1) * dy;
    if(realHeight > ui->scrollAreaContents->height())
        ui->scrollAreaContents->setMinimumHeight(realHeight);
}










