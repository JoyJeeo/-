#include "detailbar.h"
#include "ui_detailbar.h"
#include "Tools/tool_00_environment.h"
#include <QSqlQuery>
#include "Tools/MenuAlgorithm/menualgorithm.h"
#include <QDebug>

DetailBar::DetailBar(QString winTitle,
                     QString controlwin_username,QString takeOrderTime,
                     QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailBar),
    controlwin_username(controlwin_username),
    takeOrderTime(takeOrderTime)
{
    ui->setupUi(this);

    this->setWindowTitle(controlwin_username + "的" + winTitle);
    ui->winTitle->setText(winTitle);

    orderDishDetailDataInitACalFromDB();
    detailShow();
}

DetailBar::~DetailBar()
{
    delete ui;
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
    int x = 20,y = 10;
    int dx = 240, dy = 300;

    for(int i = 0;i < dishDetails.size();i++)
    {
        dishDetails[i]->move(x + dx * (i % 3), y + dy * (i / 3));
    }

    // 重置content的高度，产生滚动条
    int realHeight = y + (dishDetails.size() / 3 + 1) * dy;
    if(realHeight > ui->scrollAreaContents->height())
        ui->scrollAreaContents->setMinimumHeight(realHeight);
}










