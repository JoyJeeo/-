#include "buynumbar.h"
#include "ui_buynumbar.h"

BuyNumBar::BuyNumBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuyNumBar)
{
    ui->setupUi(this);
}

BuyNumBar::~BuyNumBar()
{
    delete ui;
}

int BuyNumBar::getBuyNum()
{
    return buynum;
}

void BuyNumBar::resetBuyNum()
{
    buynum = 1;
    ui->lineEdit->setText(QString::number(buynum));
}

void BuyNumBar::on_lineEdit_textEdited(const QString &arg1)
{
    buynum = arg1.toInt();
}


void BuyNumBar::on_plus_ptn_clicked()
{
    buynum++;
    ui->lineEdit->setText(QString::number(buynum));
}

void BuyNumBar::on_minus_ptn_clicked()
{
    buynum--;
    ui->lineEdit->setText(QString::number(buynum));
}
