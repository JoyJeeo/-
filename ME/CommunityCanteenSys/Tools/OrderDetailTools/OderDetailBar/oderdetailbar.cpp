#include "oderdetailbar.h"
#include "ui_oderdetailbar.h"
#include "Tools/OrderDetailTools/DetailBar/detailbar.h"
#include <QDebug>

OderDetailBar::OderDetailBar(QString controlwin_username, QString takeOrderTime, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OderDetailBar),
    controlwin_username(controlwin_username),
    takeOrderTime(takeOrderTime)
{
    ui->setupUi(this);

    ui->orderTime_lab->setText("订单时间：" + this->takeOrderTime);

    if(ui->detail_ptn) delete ui->detail_ptn;
    QIcon detailIcon("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/OrderDetail_ICONs/watchDetail.png");
    ui->detail_ptn = new QPushButton(detailIcon, "", this);
    ui->detail_ptn->move(740, 0);
    ui->detail_ptn->setMinimumSize(50,50);
    ui->detail_ptn->setStyleSheet(
                "QPushButton{background-color: rgb(178,180,164,40%);  border-radius: 25px;border: 1px;}"
                "QPushButton:hover{background-color: gray; border-radius: 25px;border: 1px;}"
                "QPushButton:pressed{background-color: rgb(255,255,255); border-radius: 25px;border: 1px;}"
                           );

    if(ui->delete_ptn) delete ui->delete_ptn;
    QIcon deleteIcon("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/OrderDetail_ICONs/deleteDetail.png");
    ui->delete_ptn = new QPushButton(deleteIcon, "", this);
    ui->delete_ptn->move(10, 0);
    ui->delete_ptn->setMinimumSize(80,50);
    ui->delete_ptn->setStyleSheet(
                "QPushButton{background-color: rgb(255,235,205,90%);  border-radius: 10px;border: 1px;}"
                "QPushButton:hover{background-color: yellow; border-radius: 10px;border: 1px;}"
                "QPushButton:pressed{background-color: rgb(255,255,255); border-radius: 10px;border: 1px;}"
                           );

    // ui中delete的控件的信号槽也被删除，需要重新链接
    connect(ui->detail_ptn,&QPushButton::clicked,this,&OderDetailBar::on_detail_ptn_clicked);
    connect(ui->delete_ptn,&QPushButton::clicked,this,&OderDetailBar::on_delete_ptn_clicked);

}

OderDetailBar::~OderDetailBar()
{
    delete ui;
}

QString OderDetailBar::getTakeOrderTime()
{
    return takeOrderTime;
}

void OderDetailBar::on_delete_ptn_clicked()
{
    emit deleteOrder(this); // 交给上层释放
}

void OderDetailBar::on_detail_ptn_clicked()
{
    DetailBar *detailBar = new DetailBar(ui->orderTime_lab->text()
                                         ,controlwin_username,takeOrderTime);
    detailBar->setAttribute(Qt::WA_DeleteOnClose);
    detailBar->show();

}
