#include "dishturnpagebar.h"
#include "ui_dishturnpagebar.h"

DishTurnPageBar::DishTurnPageBar(QWidget *parent) :
    QWidget(parent),
    parent(parent),
    ui(new Ui::DishTurnPageBar)
{
    ui->setupUi(this);
}

DishTurnPageBar::~DishTurnPageBar()
{
    delete ui;
}

void DishTurnPageBar::on_curIndex_lineEdit_textEdited(const QString &arg1)
{
    // 预判
//    curIndex = arg1.toInt();

    // 展示


    ui->pageIndex_lineEdit->setText(arg1);
}

void DishTurnPageBar::on_left_ptn_clicked()
{
    curIndex = curIndex > 1 ? curIndex - 1 : 1;

    // 展示


    ui->pageIndex_lineEdit->setText(QString::number(curIndex));
}

void DishTurnPageBar::on_right_ptn_clicked()
{
    // 预判
//    curIndex = curIndex <  ? curIndex - 1 : 1;

    // 展示

    ui->pageIndex_lineEdit->setText(QString::number(curIndex));

}
