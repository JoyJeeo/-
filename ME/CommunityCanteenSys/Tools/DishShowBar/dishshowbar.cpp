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
        QImage *paypal = new QImage("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/PayPal/Paying.jpg");
        QWidget *w = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout; // 在布局中添加控件，最后将布局添加到窗体中
        QLabel *label = new QLabel();
        label->setPixmap(QPixmap::fromImage(*paypal));
        layout->addWidget(label);
        w->setLayout(layout);
        w->move(0,0);
        w->show();
        int check = QMessageBox::information(nullptr,"立即购买信息",text,QMessageBox::Ok | QMessageBox::Close);

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
                // 加入订单详情中
                writeDataToUserOrderDetail(buyNum, dishMoney * buyNum);

            }

        }
    }

    // 恢复购买数量
    this->buynumbar->resetBuyNum();
}

void DishShowBar::writeDataToUserBuyCar(int buyNum)
{

}

void DishShowBar::writeDataToUserOrderDetail(int buyNum, int allPay)
{

}
