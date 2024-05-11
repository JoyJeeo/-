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
    int t = arg1.toInt();

    buynum = t >= 1 ? t : buynum;

    ui->lineEdit->setText(QString::number(buynum));
}


void BuyNumBar::on_plus_ptn_clicked()
{
    buynum++;

    ui->lineEdit->setText(QString::number(buynum));
}

void BuyNumBar::on_minus_ptn_clicked()
{
    buynum = buynum > 1 ? buynum - 1 : 1;

    ui->lineEdit->setText(QString::number(buynum));
}
