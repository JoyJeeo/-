#include "buycarwin.h"
#include "ui_buycarwin.h"

buycarwin::buycarwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::buycarwin)
{
    ui->setupUi(this);
}

buycarwin::~buycarwin()
{
    delete ui;
}
