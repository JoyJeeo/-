#include "dishshowbar.h"
#include "ui_dishshowbar.h"
#include <QMessageBox>
#include <QDebug>
#include "Tools/MenuAlgorithm/menualgorithm.h"
#include "Tools/tool_00_environment.h"
#include <QSqlQuery>

DishShowBar::DishShowBar(QString *controlwin_username, QString DishImagePath,
                         QString DishName, QString DishMoney, QString DishNum,QString DishIndex,
                         QWidget *parent):
    QWidget(parent),
    ui(new Ui::DishShowBar),
    controlwin_username(controlwin_username),
    DishImagePath(new QString(DishImagePath)),
    DishName(new QString(DishName)),DishMoney(new QString(DishMoney)),DishNum(new QString(DishNum)),
    DishIndex(new QString(DishIndex))
{
    ui->setupUi(this);
    buynumbar = new BuyNumBar(this);
    buynumbar->move(0,ui->buyNow_ptn->y());

    if(DishImagePath.size() != 0)
    {
        DishImage = new QImage(DishImagePath);
        this->DishImage = new QImage(this->DishImage->scaled(201, 141, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        ui->DishShow_lab->setPixmap(QPixmap::fromImage(*this->DishImage));
    }
    ui->Dish_lab->setText(*this->DishName);
    ui->money_lab->setText(*this->DishMoney);
    ui->num_lab->setText(*this->DishNum);

    // 发送自己给上层
    connect(ui->DishShow_lab,&DishIconLabel::addSuccess,[=](){emit this->addSuccess(this);});
    connect(ui->DishShow_lab,&DishIconLabel::deleteSuccess,[=](){emit this->deleteSuccess(this);});

//    this->setStyleSheet("border: 1px solid red");
}

DishShowBar::~DishShowBar()
{
    delete ui;
}

QString *DishShowBar::getDishImagePath()
{
    return DishImagePath;
}

QString *DishShowBar::getDishName()
{
    return DishName;
}

QString *DishShowBar::getDishMoney()
{
    return DishMoney;
}

QString *DishShowBar::getDishNum()
{
    return DishNum;
}

QString *DishShowBar::getDishIndex()
{
    return DishIndex;
}

void DishShowBar::setDishImagePath(QString *t)
{
    DishImagePath = t;
    if(t->size() > 0)
    {
        DishImage = new QImage(*t);
        this->DishImage = new QImage(this->DishImage->scaled(201, 141, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        ui->DishShow_lab->setPixmap(QPixmap::fromImage(*this->DishImage));
    }
}

void DishShowBar::setDishName(QString *t)
{
    DishName = t;
    ui->Dish_lab->setText(*t);
}

void DishShowBar::setDishMoney(QString *t)
{
    DishMoney = t;
    ui->money_lab->setText(*t);
}

void DishShowBar::setDishNum(QString *t)
{
    DishNum = t;
    ui->num_lab->setText(*t);
}

void DishShowBar::setDishIndex(QString *t)
{
    DishIndex = t;
}

void DishShowBar::on_addBuyCar_ptn_clicked()
{
    if(*DishIndex == "-1") return; // 表示占位的DishBar

    int oldDishNum = MenuAlgorithm::GetQStringByFirstNum(*this->DishNum);
    int buyNum = this->buynumbar->getBuyNum();

    // 预判是否可以被购买
    if(oldDishNum < buyNum)
    {
        QMessageBox::warning(nullptr,"购买错误","购买数量大于库存数量");
    }
    else
    {
        // 判断是否需要购买
        QString text = "%1\n%2\n购买：%3份";
        text = text.arg(*DishName).arg(*DishMoney).arg(buyNum);
        int check = QMessageBox::information(nullptr,"确认菜品信息",text,QMessageBox::Ok | QMessageBox::Close);

        if(check == QMessageBox::Ok)
        {
            // 更改菜品数据库信息
            int newDishNum =  oldDishNum - buyNum;

            *DishNum = MenuAlgorithm::replaceQStringByFirstNum(*DishNum,newDishNum);
            ui->num_lab->setText(*DishNum);
            QSqlQuery query(*DB);
            QString sql = QString("update dishesInfo set DishNum = '%1' "
                                  "where DishName = '%2';")
                    .arg(*DishNum)
                    .arg(*DishName);
            if(!query.exec(sql))
            {
                *DishNum = MenuAlgorithm::replaceQStringByFirstNum(*DishNum,oldDishNum);
                ui->num_lab->setText(*DishNum);
                QMessageBox::critical(nullptr,"购买失败","数据库更新购买信息异常");
            }
            else
            {
                // 加入购物车
                // 购买信息写入用户购物车数据库中
                writeDataToUserBuyCar(buyNum);
            }
        }
    }

    // 恢复购买数量
    this->buynumbar->resetBuyNum();
}

void DishShowBar::on_buyNow_ptn_clicked()
{
    if(*DishIndex == "-1") return;

    int oldDishNum = MenuAlgorithm::GetQStringByFirstNum(*this->DishNum);
    int buyNum = this->buynumbar->getBuyNum();
    int dishMoney = MenuAlgorithm::GetQStringByFirstNum(*this->DishMoney);

    // 预判是否可以被购买
    if(oldDishNum < buyNum)
    {
        QMessageBox::warning(nullptr,"购买错误","购买数量大于库存数量");
    }
    else
    {
        // 立即购买 输出购买信息和付款方式
        QString text = "%1\n%2\n购买：%3份\n需支付：%4元";
        text = text.arg(*DishName).arg(*DishMoney).arg(buyNum).arg(dishMoney * buyNum);
        int check = QMessageBox::information(nullptr,"立即购买信息",text,QMessageBox::Ok | QMessageBox::Close);

        if(check == QMessageBox::Ok)
        {
            // 付款界面
            QImage *paypal = new QImage("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/PayPal/Paying.jpg");
            QDialog *w = new QDialog;
            QVBoxLayout *layout = new QVBoxLayout; // 在布局中添加控件，最后将布局添加到窗体中
            QLabel *label = new QLabel();
            label->setPixmap(QPixmap::fromImage(*paypal));
            layout->addWidget(label);
            w->setLayout(layout);
            w->move(0,0);
            w->exec();

            // 更改菜品数据库信息
            int newDishNum =  oldDishNum - buyNum;
            *DishNum = MenuAlgorithm::replaceQStringByFirstNum(*DishNum,newDishNum);
            ui->num_lab->setText(*DishNum);
            QSqlQuery query(*DB);
            QString sql = QString("update dishesInfo set DishNum = '%1' "
                                  "where DishName = '%2';")
                    .arg(*DishNum)
                    .arg(*DishName);
            if(!query.exec(sql))
            {
                *DishNum = MenuAlgorithm::replaceQStringByFirstNum(*DishNum,oldDishNum);
                ui->num_lab->setText(*DishNum);
                QMessageBox::critical(nullptr,"购买失败","数据库更新购买信息异常");
            }
            else
            {
                // 加入订单详情中
                writeDataToUserOrderDetail(buyNum);

            }

        }
    }

    // 恢复购买数量
    this->buynumbar->resetBuyNum();
}

void DishShowBar::writeDataToUserBuyCar(int buyNum)
{
    QString buyCarTable = *controlwin_username + "BuyCar";

    QSqlQuery query(*DB);
    QString sql = QString("create table if not exists %1 "
                          "(                                      "
                          "    DishName varchar(50),              "
                          "    DishMoney varchar(50),             "
                          "    DishBuyNum varchar(50),            "
                          "    DishImagePath varchar(1024),       "
                          "    DishIndex int                      "
                          ");")
            .arg(buyCarTable);

    query.exec(sql);

    sql = QString("select * from %1 where DishName = '%2'")
            .arg(buyCarTable)
            .arg(*this->DishName);
    query.exec(sql);

    // 购物车中第一次添加该菜品
    if(!query.next())
    {
        int selfDishIndex = -1;
        sql = QString("select * from %1 order by DishIndex desc")
                .arg(buyCarTable);
        query.exec(sql);
        query.next();

        selfDishIndex = query.value("DishIndex").toInt() + 1;

        sql = QString("insert into %1 values"
                      "('%2','%3','%4','%5','%6')")
                .arg(buyCarTable)
                .arg(*this->DishName)
                .arg(*this->DishMoney)
                .arg("购买：" + QString::number(buyNum) + "份")
                .arg(*this->DishImagePath)
                .arg(selfDishIndex);

        if(!query.exec(sql))
        {
            QMessageBox::critical(nullptr,"加入购物车失败","数据写入用户购物车表失败");
        }
    }
    else
    {
        int oldBuyNum = MenuAlgorithm::GetQStringByFirstNum(query.value("DishBuyNum").toString());
        int newBuyNum = oldBuyNum + buyNum;
        int curDishIndex = query.value("DishIndex").toInt();

        sql = QString("update %1 set "
                      "DishName = '%2', DishMoney = '%3', DishBuyNum = '%4', "
                      "DishImagePath = '%5' where DishIndex = %6;")
                .arg(buyCarTable)
                .arg(*this->DishName)
                .arg(*this->DishMoney)
                .arg("购买：" + QString::number(newBuyNum) + "份")
                .arg(*this->DishImagePath)
                .arg(curDishIndex);

        if(!query.exec(sql))
        {
            QMessageBox::critical(nullptr,"加入购物车失败","更新数据到用户购物车表失败");
        }
    }
}

void DishShowBar::writeDataToUserOrderDetail(int buyNum)
{
    QString OrderDetailTable = *controlwin_username + "OrderDetail";

    QSqlQuery query(*DB);
    QString sql = QString("create table if not exists %1    "
                          "(                                "
                          "    DishName varchar(50),        "
                          "    DishMoney varchar(50),       "
                          "    DishBuyNum varchar(50),      "
                          "    DishImagePath varchar(1024), "
                          "    TakeOrderTime datetime       "
                          ");")
            .arg(OrderDetailTable);

    query.exec(sql);

    // 获取订单创建时间
    sql = QString("select now();");
    query.exec(sql);
    query.next();
    QString nowTime = query.value(0).toString();

    sql = QString("insert into %1 values"
                  "('%2','%3','%4','%5','%6')")
            .arg(OrderDetailTable)
            .arg(*this->DishName)
            .arg(*this->DishMoney)
            .arg("购买：" + QString::number(buyNum) + "份")
            .arg(*this->DishImagePath)
            .arg(nowTime);

    if(!query.exec(sql))
    {
        QMessageBox::critical(nullptr,"订单创建失败","数据写入用户订单表失败");
    }
    else
    {
        QMessageBox::information(nullptr,"购买成功","购买成功！");
    }

}














