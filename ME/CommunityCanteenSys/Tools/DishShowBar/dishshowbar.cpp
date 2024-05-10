#include "dishshowbar.h"
#include "ui_dishshowbar.h"

DishShowBar::DishShowBar(QString DishPath,
                         QString DishName, QString DishMoney, QString DishNum,
                         QWidget *parent):
    QWidget(parent),
    ui(new Ui::DishShowBar),
    DishImage(new QImage(DishPath)),
    DishName(new QString(DishName)),DishMoney(new QString(DishMoney)),DishNum(new QString(DishNum))
{
    ui->setupUi(this);
    buynumbar = new BuyNumBar(this);
    buynumbar->move(0,ui->buyNow_ptn->y());

    this->DishImage = new QImage(this->DishImage->scaled(201, 141, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->DishShow_lab->setPixmap(QPixmap::fromImage(*this->DishImage));
    ui->Dish_lab->setText(*this->DishName);
    ui->money_lab->setText(*this->DishMoney);
    ui->num_lab->setText(*this->DishNum);

//    this->setStyleSheet("border: 1px solid red");
}

DishShowBar::~DishShowBar()
{
    delete ui;
}

QImage *DishShowBar::getDishImage()
{
    return DishImage;
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

void DishShowBar::setDishImage(QImage *t)
{
    DishImage = t;
}

void DishShowBar::setDishName(QString *t)
{
    DishName = t;
}

void DishShowBar::setDishMoney(QString *t)
{
    DishMoney = t;
}

void DishShowBar::setDishNum(QString *t)
{
    DishNum = t;
}

void DishShowBar::on_addBuyCar_ptn_clicked()
{
    // 加入购物车

    // 恢复购买数量
    this->buynumbar->resetBuyNum();
}

void DishShowBar::on_buyNow_ptn_clicked()
{
    // 处理购买

    // 恢复购买数量
    this->buynumbar->resetBuyNum();
}
