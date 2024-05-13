#include "controlwin.h"
#include "ui_controlwin.h"
#include "Tools/DishShowBar/dishshowbar.h"
#include "Tools/UserIconLabel/usericonlabel.h"
#include "Tools/tool_00_environment.h"
#include <QSqlQuery>
#include "Windows/BuyCar_Pager/buycarwin.h"
#include "Windows/OrderDetail_Pager/orderdetailwin.h"

controlwin::controlwin(QWidget *parent) :
    QMainWindow(parent),
    userIcon(nullptr),
    userIconPath(nullptr),
    ui(new Ui::controlwin),
    admin_win(new adminwin)
{
    ui->setupUi(this);
    ui->admin_btn->hide();

    this->carouselchart = new CarouselChart(ui->AnnoWin);
    this->carouselchart->setGeometry(0,0,ui->AnnoWin->width(),ui->AnnoWin->height());

    this->setFixedSize(1000,700);
    connect(admin_win,&adminwin::back,this,&controlwin::on_admin_back);
    connect(ui->userIcon_label,&UserIconLabel::back,this,&controlwin::setUserIcon);
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
    admin_win->triggered();
    admin_win->show();
}

void controlwin::triggered()
{
    ui->userIcon_label->clear();
    ui->userIcon_label->setText("请设置用户头像");

    if(*user_name == "admin")
        ui->admin_btn->show();
    else
        ui->admin_btn->hide();
    ui->username_label->setText(*user_name);

    if(dishTurnPageBar) {delete dishTurnPageBar;dishTurnPageBar = nullptr;}
    dishTurnPageBar = new DishTurnPageBar(user_name,
                                          ui->Anno_Dishes_Area, ui->Anno_Dishes_AreaContents);
    dishTurnPageBar->dishInitfromDB();
    dishTurnPageBar->dishShow();

    getUserIcon();
    showUserIcon();
}

void controlwin::set_user_name(QString name)
{
    user_name = new QString(name);
}

void controlwin::getUserIcon()
{
    QSqlQuery query(*DB);
    QString sql = QString("select * from userName_userIconPath "
                          "where username = '%1';"
                          ).arg(*user_name);
    query.exec(sql);

    if(query.next())
    {
        this->userIconPath = new QString(query.value("userIconPath").toString());
        this->userIcon = new QImage(*this->userIconPath);
        this->userIcon =
                new QImage(this->userIcon->scaled(220, 220, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    else userIcon = nullptr;
}

void controlwin::showUserIcon()
{
    if(this->userIcon) ui->userIcon_label->setPixmap(QPixmap::fromImage(*this->userIcon));
}

void controlwin::setUserIcon(QString userIconPath)
{
    this->userIconPath = new QString(userIconPath);
    this->userIcon = new QImage(*this->userIconPath);
    this->userIcon =
            new QImage(this->userIcon->scaled(220, 220, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

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
    else sql = QString("insert into userName_userIconPath(username,"
                                        "userIconPath) "
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

    buycarwin *buyCarWin = new buycarwin();
    buyCarWin->setAttribute(Qt::WA_DeleteOnClose);
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
    orderDetailWin->show();
}
