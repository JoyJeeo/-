#include "registerwin.h"
#include "ui_registerwin.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include "Tools/tool_00_environment.h"

registerwin::registerwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerwin)
{
    ui->setupUi(this);
    this->setFixedSize(512,527);
    this->setWindowTitle("USER REGISTER");
}

registerwin::~registerwin()
{
    DELETE(ui);
}

void registerwin::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        on_register_pbtn_clicked();
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
            sql = QString("insert into logininfo values "
                          "('%1', '%2');"
                          ).arg(username).arg(pwd);

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
