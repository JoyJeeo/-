#include "controlwin.h"
#include "ui_controlwin.h"

controlwin::controlwin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::controlwin)
{
    ui->setupUi(this);
    this->setFixedSize(1000,700);
}

controlwin::~controlwin()
{
    delete ui;
}
