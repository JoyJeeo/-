#include "adminwin.h"
#include "ui_adminwin.h"

adminwin::adminwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminwin)
{
    this->setFixedSize(1050,646);

    ui->setupUi(this);
}

adminwin::~adminwin()
{
    delete ui;
}

void adminwin::on_back_clicked()
{
    this->hide();
    emit back();
}
