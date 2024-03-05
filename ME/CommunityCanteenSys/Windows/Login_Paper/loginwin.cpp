#include "loginwin.h"
#include "ui_loginwin.h"

loginwin::loginwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginwin),
    re(new registerwin)
{
    ui->setupUi(this);
    this->setFixedSize(512,527);

    connect(re,&registerwin::register_complete,this,&loginwin::after_register_login);
}

loginwin::~loginwin()
{
    delete ui;
}

void loginwin::on_register_pbtn_clicked()
{
    this->hide();
    re->show();
}

void loginwin::after_register_login()
{
    re->hide();
    this->show();
}

void loginwin::on_login_pbtn_clicked()
{
    // 连接数据库，登录正确和错误提示
}
