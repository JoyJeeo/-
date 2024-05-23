#include "controlwin.h"
#include "ui_controlwin.h"
#include "Tools/DishShowBar/dishshowbar.h"
#include "Tools/UserIconLabel/usericonlabel.h"
#include "Tools/tool_00_environment.h"
#include <QSqlQuery>
#include "Windows/BuyCar_Pager/buycarwin.h"
#include "Windows/OrderDetail_Pager/orderdetailwin.h"
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include "Tools/MenuAlgorithm/menualgorithm.h"
#include <QPainter>

controlwin::controlwin(QWidget *parent) :
    QMainWindow(parent),
    user_name(nullptr),
    ui(new Ui::controlwin),
    carouselchart(nullptr),
    dishTurnPageBar(nullptr)
{
    ui->setupUi(this);
    ui->admin_btn->hide();

    QPixmap pixmap("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/Background_PICS/control.jpg");//设定图片

    /*设置添加图片的灰度值，将自定义的图片上灰度*/
//    QPainter p1(&pixmap);
//    p1.setCompositionMode(QPainter::CompositionMode_Source);
//    p1.drawPixmap(0, 0, pixmap);
//    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);

//    //根据QColor中第四个参数设置透明度，0～255
//    p1.fillRect(pixmap.rect(), QColor(179,179,164, 220));
//    p1.end();

    pixmap = MenuAlgorithm::PixmapToRound(pixmap,0,this->width(),this->height());
    QPalette palette;//创建一个调色板对象
    palette.setBrush(this->backgroundRole(),QBrush(pixmap));//用调色板的画笔把映射到pixmap上的图片画到            frame.backgroundRole()这个背景上
    this->setPalette(palette);//设置窗口调色板为palette，窗口和画笔相关联

    ui->Anno_Dishes_Area->setStyleSheet("QScrollArea {background-color:transparent;}");
    ui->Anno_Dishes_Area->viewport()->setStyleSheet("QScrollArea {background-color:transparent;}");

    // 设置垂直滚动条样式
    QString verticalScrollBarStyle =
        "QScrollBar:vertical {"
           "    border: none;"
           "    background: transparent;"
           "    width: 12px;"
           "    margin: 16px 0 16px 0;"
           "}"
           "QScrollBar:vertical:hover {"
           "    background: #b3d9ff;"
           "}"
           "QScrollBar::handle:vertical {"
           "    background: #5dade2;"
           "    border-radius: 6px;"
           "    min-height: 30px;"
           "}"
           "QScrollBar::handle:vertical:hover {"
           "    background: #2e86c1;"
           "}"
           "QScrollBar::add-line:vertical {"
           "    height: 16px;"
           "    subcontrol-position: bottom;"
           "    subcontrol-origin: margin;"
           "}"
           "QScrollBar::sub-line:vertical {"
           "    height: 16px;"
           "    subcontrol-position: top;"
           "    subcontrol-origin: margin;"
           "}";

    ui->Anno_Dishes_Area->verticalScrollBar()->setStyleSheet(verticalScrollBarStyle);

    // 设置水平滚动条样式
    QString horizontalScrollBarStyle =
        "QScrollBar:horizontal {"
           "    border: none;"
           "    background: transparent;"
           "    height: 12px;"
           "    margin: 0 16px 0 16px;"
           "}"
           "QScrollBar:horizontal:hover {"
           "    background: #b3d9ff;"
           "}"
           "QScrollBar::handle:horizontal {"
           "    background: #5dade2;"
           "    border-radius: 6px;"
           "    min-width: 30px;"
           "}"
           "QScrollBar::handle:horizontal:hover {"
           "    background: #2e86c1;"
           "}"
           "QScrollBar::add-line:horizontal {"
           "    width: 16px;"
           "    subcontrol-position: right;"
           "    subcontrol-origin: margin;"
           "}"
           "QScrollBar::sub-line:horizontal {"
           "    width: 16;"
           "    subcontrol-position: left;"
           "    subcontrol-origin: margin;"
           "}";

    ui->Anno_Dishes_Area->horizontalScrollBar()->setStyleSheet(horizontalScrollBarStyle);

    dishTurnPageBar = new DishTurnPageBar(&user_name,
                    ui->Anno_Dishes_Area, ui->Anno_Dishes_AreaContents); // ui必须先构造到窗口上
    dishTurnPageBar->dishInitfromDB();

    this->carouselchart = new CarouselChart(&user_name, ui->AnnoWin);

    this->setFixedSize(1000,700);
    connect(ui->userIcon_label,&UserIconLabel::back,this,&controlwin::setUserIcon);
}

controlwin::~controlwin()
{
    delete ui;
    if(user_name) {delete user_name; user_name = nullptr;}
    if(carouselchart) {delete carouselchart; carouselchart = nullptr;}
    if(dishTurnPageBar) {delete dishTurnPageBar; dishTurnPageBar = nullptr;}

}

void controlwin::on_back_login_btn_clicked()
{
    this->hide();
    emit back_login_paper();
}

void controlwin::on_admin_back()
{
    this->show();
}

void controlwin::on_admin_btn_clicked()
{
    adminwin *admin_win = new adminwin;
    admin_win->setAttribute(Qt::WA_DeleteOnClose);
    connect(admin_win,&adminwin::back,this,&controlwin::on_admin_back);
    this->hide();
    admin_win->triggered();
    admin_win->show();
}

void controlwin::triggered()
{
    ui->userIcon_label->clear();
    ui->userIcon_label->setText("请设置用户头像");

    *user_name == "admin" ? ui->admin_btn->show() : ui->admin_btn->hide();
    ui->username_label->setText(*user_name);

    dishTurnPageBar->setCurIndex(0);
    dishTurnPageBar->dishShow();
    this->setWindowTitle(*user_name);

    showUserIcon();
}

void controlwin::set_user_name(QString name)
{
    if(user_name) {delete user_name; user_name = nullptr;}
    user_name = new QString(name);
}

void controlwin::showUserIcon()
{
    QSqlQuery query(*DB);
    QString sql = QString("select * from userName_userIconPath "
                          "where username = '%1';"
                          ).arg(*user_name);
    query.exec(sql);

    QImage *userIcon = nullptr;
    if(query.next())
    {
        userIcon = new QImage(query.value("userIconPath").toString());
        userIcon = new QImage(userIcon->scaled(220, 220, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        ui->userIcon_label->setPixmap(QPixmap::fromImage(*userIcon));
    }
}

void controlwin::setUserIcon(QString userIconPath)
{
    QImage *userIcon = nullptr;
    userIcon = new QImage(userIconPath);
    userIcon = new QImage(userIcon->scaled(220, 220, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    // 加入变动
    QSqlQuery query(*DB);
    QString sql = QString("select * from userName_userIconPath "
                          "where username = '%1';"
                          ).arg(*user_name);
    query.exec(sql);

    bool flag = query.next() ? true : false;

    // 修改
    if(flag) sql = QString("update userName_userIconPath set "
                                            "userIconPath = '%1' "
                                            "where username = '%2';").arg(userIconPath).arg(*user_name);

    // 新增
    else sql = QString("insert into userName_userIconPath "
                                        "values('%1', '%2');").arg(*user_name).arg(userIconPath);

    query.exec(sql);

    showUserIcon();
}

void controlwin::on_buy_car_btn_clicked()
{
    QString buyCarTable = *user_name + "BuyCar";

    QSqlQuery query(*DB);
    QString sql = QString("create table if not exists %1 "
                          "(                                      "
                          "    DishName varchar(50),              "
                          "    DishMoney varchar(50),             "
                          "    DishBuyNum varchar(50),            "
                          "    DishImagePath varchar(1024),       "
                          "    DishIndex int                      "
                          ");")
            .arg(buyCarTable);

    query.exec(sql);

    buycarwin *buyCarWin = new buycarwin(*user_name);
    buyCarWin->setAttribute(Qt::WA_DeleteOnClose);
    buyCarWin->setWindowModality(Qt::ApplicationModal);
    buyCarWin->show();
}

void controlwin::on_order_details_btn_clicked()
{
    QString OrderDetailTable = *user_name + "OrderDetail";

    QSqlQuery query(*DB);
    QString sql = QString("create table if not exists %1    "
                          "(                                "
                          "    DishName varchar(50),        "
                          "    DishMoney varchar(50),       "
                          "    DishBuyNum varchar(50),      "
                          "    DishImagePath varchar(1024), "
                          "    TakeOrderTime datetime       "
                          ");")
            .arg(OrderDetailTable);

    query.exec(sql);

    orderdetailwin *orderDetailWin = new orderdetailwin(*user_name);
    orderDetailWin->setAttribute(Qt::WA_DeleteOnClose);
    orderDetailWin->setWindowModality(Qt::ApplicationModal);
    orderDetailWin->show();
}
