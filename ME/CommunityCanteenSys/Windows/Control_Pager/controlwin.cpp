#include "controlwin.h"
#include "ui_controlwin.h"
#include "Tools/DishShowBar/dishshowbar.h"
#include "Tools/tool_00_environment.h"
#include "Tools/UserIconLabel/usericonlabel.h"
#include <QSqlQuery>

controlwin::controlwin(QWidget *parent) :
    QMainWindow(parent),
    userIcon(nullptr),
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

    dishTurnPageBar = new DishTurnPageBar(ui->Anno_Dishes_Area, ui->Anno_Dishes_AreaContents);

    dishTurnPageBar->addDish(new DishShowBar(":/new/prefix1/Image/Dish_ICON/MaPoDouFu.jpg",
                        "菜名：麻婆豆腐","价格：15元","剩余：100份",ui->Anno_Dishes_AreaContents));

    dishTurnPageBar->addDish(new DishShowBar(":/new/prefix1/Image/Dish_ICON/GanBianDaXia.jpg",
                        "菜名：干煸大虾","价格：30元","剩余：15份",ui->Anno_Dishes_AreaContents));

    dishTurnPageBar->addDish(new DishShowBar(":/new/prefix1/Image/Dish_ICON/TangCuLiJi.jpg",
                        "菜名：糖醋里脊","价格：25元","剩余：50份",ui->Anno_Dishes_AreaContents));

    dishTurnPageBar->addDish(new DishShowBar(":/new/prefix1/Image/Dish_ICON/EGanChaoFan.jpg",
                        "菜名：鹅肝炒饭","价格：11元","剩余：51份",ui->Anno_Dishes_AreaContents));

    dishTurnPageBar->addDish(new DishShowBar(":/new/prefix1/Image/Dish_ICON/MaoCai.jpg",
                        "菜名：冒菜","价格：14元","剩余：63份",ui->Anno_Dishes_AreaContents));

    dishTurnPageBar->addDish(new DishShowBar(":/new/prefix1/Image/Dish_ICON/TangCuLiYu.jpg",
                        "菜名：糖醋鲤鱼","价格：45元","剩余：42份",ui->Anno_Dishes_AreaContents));

    dishTurnPageBar->addDish(new DishShowBar(":/new/prefix1/Image/Dish_ICON/TangCuSongShuYu.jpg",
                        "菜名：糖醋松鼠鱼","价格：65元","剩余：23份",ui->Anno_Dishes_AreaContents));

    dishTurnPageBar->dishShow();

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

    if(user_name == "admin")
        ui->admin_btn->show();
    else
        ui->admin_btn->hide();
    ui->username_label->setText(user_name);

    getUserIcon();
    showUserIcon();
}

void controlwin::set_user_name(QString name)
{
    user_name = name;
}

void controlwin::getUserIcon()
{
    QSqlQuery query(*DB);
    QString sql = QString("select * from userName_userIconPath "
                          "where username = '%1';"
                          ).arg(user_name);
    query.exec(sql);

    if(query.next())
    {
        this->userIcon = new QImage(query.value("userIconPath").toString());
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
    this->userIcon = new QImage(userIconPath);
    this->userIcon =
            new QImage(this->userIcon->scaled(220, 220, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    // 加入变动
    QSqlQuery query(*DB);
    QString sql = QString("select * from userName_userIconPath "
                          "where username = '%1';"
                          ).arg(user_name);
    query.exec(sql);

    bool flag = query.next() ? true : false;

    // 修改
    if(flag) sql = QString("update userName_userIconPath set "
                                            "userIconPath = '%1' "
                                            "where username = '%2';").arg(userIconPath).arg(user_name);

    // 新增
    else sql = QString("insert into userName_userIconPath(username,"
                                        "userIconPath) "
                                        "values('%1', '%2');").arg(user_name).arg(userIconPath);

    query.exec(sql);

    showUserIcon();
}
