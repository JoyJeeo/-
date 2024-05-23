#include "registerwin.h"
#include "ui_registerwin.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include "Tools/tool_00_environment.h"
#include "Tools/MenuAlgorithm/menualgorithm.h"

registerwin::registerwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerwin),
    watchEye(nullptr)
{
    ui->setupUi(this);

    QPixmap pixmap("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/Background_PICS/register.jpg");//设定图片
    pixmap = MenuAlgorithm::PixmapToRound(pixmap,0,this->width(),this->height());
    QPalette palette;//创建一个调色板对象
    palette.setBrush(this->backgroundRole(),QBrush(pixmap));//用调色板的画笔把映射到pixmap上的图片画到            frame.backgroundRole()这个背景上
    this->setPalette(palette);//设置窗口调色板为palette，窗口和画笔相关联

    watchEye = new HoverableLabel(this);
    QImage *image = new QImage("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/OrderDetail_ICONs/watchDetail.png");
    image = new QImage(image->scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    watchEye->setPixmap(QPixmap::fromImage(*image));
    watchEye->move(414, 277);
    watchEye->setMinimumSize(30,30);
    watchEye->setStyleSheet(
                "QLabel{background-color: rgb(178,180,164,40%);  border-radius: 15px;border: 1px;}"
                "QLabel:hover{background-color: gray; border-radius: 15px;border: 1px;}"
                           );

    this->setFixedSize(512,527);
    this->setWindowTitle("用户注册");
    connect(this->watchEye,&HoverableLabel::mouseEntered,this,&registerwin::on_enter_watchEye);
    connect(this->watchEye,&HoverableLabel::mouseLeft,this,&registerwin::on_leave_watchEye);
}

registerwin::~registerwin()
{
    delete ui;
    delete watchEye;
}

void registerwin::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        on_register_pbtn_clicked();
}

void registerwin::on_enter_watchEye()
{
    // 显示密码
    ui->pwd_lineEdit->setEchoMode(QLineEdit::Normal);
}

void registerwin::on_leave_watchEye()
{
    // 隐藏密码（显示为星号或点）
    ui->pwd_lineEdit->setEchoMode(QLineEdit::Password);
}

void registerwin::on_register_pbtn_clicked()
{
    // 判断注册是否成功
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
                              "where username = '%1';"
                              ).arg(username);

        query.exec(sql);

        if(query.next())
        {
            QMessageBox::warning(this,"警告","注册失败，该用户已存在，请更换用户名");
        }
        else
        {
            sql = QString("select * from logininfo order by curid desc;");
            query.exec(sql);
            query.next();

            int curid = query.size() == 0 ? 0 : query.value("curid").toInt() + 1;

            sql = QString("insert into logininfo values "
                          "('%1', '%2', '%3');"
                          ).arg(username).arg(pwd).arg(curid);

            if(query.exec(sql))
            {
                if(QMessageBox::information(this,"提示","注册成功！","返回登陆","继续注册",0,1) == 0)
                    on_pushButton_clicked();
            }
            else
            {
                QMessageBox::critical(this,"警告","数据插入失败！");
            }
        }
    }
    ui->username_lineEdit->clear();
    ui->pwd_lineEdit->clear();
}

void registerwin::on_pushButton_clicked()
{
    this->hide();
    emit register_complete();
}
