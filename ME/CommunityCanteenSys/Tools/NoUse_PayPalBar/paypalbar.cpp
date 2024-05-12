#include "paypalbar.h"
#include "ui_paypalbar.h"

PayPalBar::PayPalBar(QWidget *parent,QString title,QString text) :
    QWidget(parent),
    ui(new Ui::PayPalBar)
{
    ui->setupUi(this);

    this->setWindowTitle(title);
    ui->text_label->setText(text);
    QImage *paypal_image = new QImage(paypalPath);
    paypal_image = new QImage(paypal_image->scaled(ui->paypal_label->width(),ui->paypal_label->height()));
    ui->paypal_label->setPixmap(QPixmap::fromImage(*paypal_image));
}

PayPalBar::~PayPalBar()
{
    delete ui;
}

void PayPalBar::on_ok_ptn_clicked()
{
    emit back(PayPalBar::OK);
    this->close();
}

void PayPalBar::on_no_ptn_clicked()
{
    emit back(PayPalBar::NO);
    this->close();
}
