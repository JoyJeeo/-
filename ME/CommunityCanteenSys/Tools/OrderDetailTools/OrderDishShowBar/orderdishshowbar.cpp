#include "orderdishshowbar.h"
#include "ui_orderdishshowbar.h"

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
        DishImage = new QImage(DishImage->scaled(201, 141, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        ui->DishShow_lab->setPixmap(QPixmap::fromImage(*DishImage));
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
