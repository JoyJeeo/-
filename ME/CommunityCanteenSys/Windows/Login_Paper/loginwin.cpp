#include "loginwin.h"
#include "ui_loginwin.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include "Tools/tool_00_environment.h"
#include "Tools/MenuAlgorithm/menualgorithm.h"


loginwin::loginwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginwin)
{
    ui->setupUi(this);

    QPixmap pixmap("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/Background_PICS/login.jpg");//设定图片
    pixmap = MenuAlgorithm::PixmapToRound(pixmap,0,this->width(),this->height());
    QPalette palette;//创建一个调色板对象
    palette.setBrush(this->backgroundRole(),QBrush(pixmap));//用调色板的画笔把映射到pixmap上的图片画到            frame.backgroundRole()这个背景上
    this->setPalette(palette);//设置窗口调色板为palette，窗口和画笔相关联

    this->setFixedSize(512,527);
    this->setWindowTitle("用户登录");

    connect(&re,&registerwin::register_complete,this,&loginwin::after_register_login);
    connect(&control_win,&controlwin::back_login_paper,this,&loginwin::after_control_win);
}

loginwin::~loginwin()
{
    delete ui;
}

void loginwin::keyPressEvent(QKeyEvent *event)
{
    /*
     * 事件处理，优先于信号槽处理，且事件处理方式为，从被触发处开始进行链式向上父组件传递的处理方式进行处理
     * 这里由于lineEdit捕捉了字符的事件处理，因此无法被上层窗体的事件处理处理，而enter和return不被lineEdit捕捉
     * 传递到父组件这里被处理
     */
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        on_login_pbtn_clicked();
}

void loginwin::on_register_pbtn_clicked()
{
    this->hide();
    re.show();
}

void loginwin::after_register_login()
{
    re.hide();
    this->show();
}

void loginwin::after_control_win()
{
    control_win.hide();
    this->show();
}

void loginwin::on_login_pbtn_clicked()
{
    /*
     * 连接数据库，登录正确和错误提示
     */
    QString username = ui->username_lineEdit->text();
    QString pwd = ui->pwd_lineEdit->text();

    int next_flage = 1;

    if(username == "" || pwd == "")
    {
        QMessageBox::warning(this,"警告","账号或密码不能为空!");
        next_flage = 0;
    }

    if(next_flage == 1)
    {
        QSqlQuery query(*DB);
        QString sql = QString("select * from logininfo "
                              "where username = '%1' and pwd = '%2';"
                              ).arg(username).arg(pwd);

        /*
         * query执行select都返回true，不存在false【只有update，insert这些可能false】
         */
        query.exec(sql);
        /*
         * while(query.next()) // query的结果初始为head空数据，next后才有第一个有效数据
         * qDebug() << "databse: " << query.value(0).toString() << " " << query.value(1).toString();
         * qDebug() << "size: " << query.size(); // query查询没有数据时，数值为-1，否则为查询到的数据条目数
         */
        if(query.next())
        {
            QMessageBox::information(this,"提示","登录成功！");
            // 打开主用户窗体
            control_win.set_user_name(username);
            control_win.triggered();
            control_win.show();

            this->hide();
            next_flage = 0;
        }

        if(next_flage == 1)
        {
            sql = QString("select * from logininfo "
                          "where username = '%1';"
                          ).arg(username);
            query.exec(sql);
            if(query.next())
                QMessageBox::warning(this,"警告","密码输入错误");
            else
                QMessageBox::critical(this,"错误","登陆失败，请先注册后再登录!");
        }
    }

    ui->username_lineEdit->clear();
    ui->pwd_lineEdit->clear();
}









