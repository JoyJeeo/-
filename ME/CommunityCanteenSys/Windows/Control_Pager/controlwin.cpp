#include "controlwin.h"
#include "ui_controlwin.h"
#include "Tools/DishShowBar/dishshowbar.h"

controlwin::controlwin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::controlwin),
    admin_win(new adminwin)
{
    ui->setupUi(this);
    ui->admin_btn->hide();

    QVector<QString> pic_paths = {
        ":/new/prefix1/Image/AnnoWin_ICON/01.jpg",
        ":/new/prefix1/Image/AnnoWin_ICON/03.jpg",
        ":/new/prefix1/Image/AnnoWin_ICON/06.jpg"
                                 };
    this->carouselchart = new CarouselChart(pic_paths,ui->AnnoWin);
    this->carouselchart->setGeometry(0,0,ui->AnnoWin->width(),ui->AnnoWin->height());

    DishShowBar *dish01 = new DishShowBar(":/new/prefix1/Image/Dish_ICON/MaPoDouFu.jpg",
                        "菜名：麻婆豆腐","价格：15元","剩余：100份",ui->Anno_Dishes_AreaContents);

    dish01->move(10,200);

    DishShowBar *dish02 = new DishShowBar(":/new/prefix1/Image/Dish_ICON/GanBianDaXia.jpg",
                        "菜名：干煸大虾","价格：30元","剩余：15份",ui->Anno_Dishes_AreaContents);

    dish02->move(230,200);

    DishShowBar *dish03 = new DishShowBar(":/new/prefix1/Image/Dish_ICON/TangCuLiJi.jpg",
                        "菜名：糖醋里脊","价格：25元","剩余：50份",ui->Anno_Dishes_AreaContents);

    dish03->move(450,200);

    DishShowBar *dish04 = new DishShowBar(":/new/prefix1/Image/Dish_ICON/EGanChaoFan.jpg",
                        "菜名：鹅肝炒饭","价格：11元","剩余：51份",ui->Anno_Dishes_AreaContents);

    dish04->move(10,490);

    DishShowBar *dish05 = new DishShowBar(":/new/prefix1/Image/Dish_ICON/MaoCai.jpg",
                        "菜名：冒菜","价格：14元","剩余：63份",ui->Anno_Dishes_AreaContents);

    dish05->move(230,490);

    DishShowBar *dish06 = new DishShowBar(":/new/prefix1/Image/Dish_ICON/TangCuLiYu.jpg",
                        "菜名：糖醋鲤鱼","价格：45元","剩余：42份",ui->Anno_Dishes_AreaContents);

    dish06->move(450,490);


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
    admin_win->triggered();
    admin_win->show();
}

void controlwin::triggered()
{
    if(user_name == "admin")
        ui->admin_btn->show();
    else
        ui->admin_btn->hide();
    ui->username_label->setText(user_name);
}

void controlwin::set_user_name(QString name)
{
    user_name = name;
}
