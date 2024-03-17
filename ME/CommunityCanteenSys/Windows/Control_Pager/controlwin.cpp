#include "controlwin.h"
#include "ui_controlwin.h"

controlwin::controlwin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::controlwin),
    admin_win(new adminwin)
{
    ui->setupUi(this);
    ui->admin_btn->hide();

    this->setFixedSize(1000,700);
    connect(admin_win,&adminwin::back,this,&controlwin::on_admin_back);
}

controlwin::~controlwin()
{
    delete ui;
}

void controlwin::on_back_login_btn_clicked()
{
    this->hide();
    emit back_login_paper();
}

void controlwin::on_admin_back()
{
    admin_win->hide();
    this->show();
}

void controlwin::on_admin_btn_clicked()
{
    this->hide();
    admin_win->show();
}

void controlwin::triggered()
{
    if(user_name == "admin")
        ui->admin_btn->show();
    ui->username_label->setText(user_name);
}

void controlwin::set_user_name(QString name)
{
    user_name = name;
}
