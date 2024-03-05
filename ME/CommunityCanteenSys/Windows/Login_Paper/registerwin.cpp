#include "registerwin.h"
#include "ui_registerwin.h"

registerwin::registerwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerwin)
{
    ui->setupUi(this);
    this->setFixedSize(512,527);
}

registerwin::~registerwin()
{
    delete ui;
}

void registerwin::on_register_pbtn_3_clicked()
{
    // 判断注册是否成功

    // 成功
    this->hide();
    emit register_complete();

    // 不成功
}
