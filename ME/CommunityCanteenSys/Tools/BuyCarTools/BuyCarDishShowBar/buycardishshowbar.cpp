#include "buycardishshowbar.h"
#include "ui_buycardishshowbar.h"
#include "Tools/MenuAlgorithm/menualgorithm.h"

BuyCarDishShowBar::BuyCarDishShowBar(QString imagePath,
                                     QString dishName,
                                     QString dishMoney,
                                     QString dishBuyNum,
                                     QString allMoney,
                                     QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuyCarDishShowBar),
    imagePath(imagePath),
    dishName(dishName),
    dishMoney(dishMoney),
    dishBuyNum(dishBuyNum),
    allMoney(allMoney)
{
    ui->setupUi(this);

    if(imagePath.size() != 0)
    {
        QImage *DishImage = new QImage(imagePath);
        QPixmap t = QPixmap::fromImage(*DishImage);
        t = MenuAlgorithm::PixmapToRound(t, 5, 169, 108);
        ui->DishShow_lab->setPixmap(t);
    }

    ui->DishName_lab->setText(dishName);
    ui->Dishmoney_lab->setText(dishMoney);
    ui->DishBuyNum_lab->setText(dishBuyNum);
    ui->allMoney_lab->setText(allMoney);

    ui->select_chkbox->setTristate(false);
    ui->select_chkbox->setCheckState(Qt::Unchecked);
}

BuyCarDishShowBar::~BuyCarDishShowBar()
{
    delete ui;
}

QString BuyCarDishShowBar::getImagePath()
{
    return imagePath;
}

QString BuyCarDishShowBar::getDishName()
{
    return dishName;
}

QString BuyCarDishShowBar::getDishMoney()
{
    return dishMoney;
}

QString BuyCarDishShowBar::getDishBuyNum()
{
    return dishBuyNum;
}

QString BuyCarDishShowBar::getAllMoney()
{
    return allMoney;
}

QCheckBox *BuyCarDishShowBar::getSelectCheckBox()
{
    return ui->select_chkbox;
}
