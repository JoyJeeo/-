#include "orderdishshowbar.h"
#include "ui_orderdishshowbar.h"
#include "Tools/MenuAlgorithm/menualgorithm.h"

OrderDishShowBar::OrderDishShowBar(QString imagePath,
                                   QString dishName,
                                   QString dishMoney,
                                   QString dishBuyNum,
                                   QString allMoney,
                                   QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderDishShowBar)
{
    ui->setupUi(this);

    if(imagePath.size() != 0)
    {
        QImage *DishImage = new QImage(imagePath);
        QPixmap t = QPixmap::fromImage(*DishImage);
        t = MenuAlgorithm::PixmapToRound(t, 5, 129, 99);
        ui->DishShow_lab->setPixmap(t);
    }

    ui->DishName_lab->setText(dishName);
    ui->Dishmoney_lab->setText(dishMoney);
    ui->DishBuyNum_lab->setText(dishBuyNum);
    ui->allMoney_lab->setText(allMoney);
}

OrderDishShowBar::~OrderDishShowBar()
{
    delete ui;
}
