#include "dishinfobar.h"
#include "ui_dishinfobar.h"
#include <QFileDialog>
#include "Tools/tool_00_environment.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include "Tools/MenuAlgorithm/menualgorithm.h"

DishInfoBar::DishInfoBar(DishShowBar *t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DishInfoBar),
    selfDishShowBar(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle(ui->Title_label->text());
    this->setFixedSize(430,447);

    if(t)
    {
        selfDishShowBar = t;
        ui->setDishImagePathSelect_lineEdit->setText(*this->selfDishShowBar->getDishImagePath());
        ui->setDishName_lineEdit->setText(*this->selfDishShowBar->getDishName());
        ui->setDishMoney_lineEdit->setText(*this->selfDishShowBar->getDishMoney());
        ui->setDishNum_lineEdit->setText(*this->selfDishShowBar->getDishNum());
    }

    QPixmap pixmap("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/Background_PICS/dishInfo.jpg");//设定图片

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
}

DishInfoBar::~DishInfoBar()
{
    delete ui;
}

void DishInfoBar::on_dishImagePathSelect_ptn_clicked()
{
    ui->setDishImagePathSelect_lineEdit->setText(
                QFileDialog::getOpenFileName(Q_NULLPTR,
                                         QObject::tr("Select Set DishImage"),
                                         QObject::tr("../"),
                                         QObject::tr("File(*.jpg);;File(*.png);;File(*.ico);;"
                                                     "All(*.*)")));
}

void DishInfoBar::on_commit_ptn_clicked()
{
    if(!this->selfDishShowBar)
    {
        QMessageBox::critical(nullptr,"选项卡错误","选项卡地址为空");
        return;
    }

    // 获取info的修改信息
    this->dishImagePath = ui->setDishImagePathSelect_lineEdit->text();
    this->dishName = ui->setDishName_lineEdit->text();
    this->dishMoney = ui->setDishMoney_lineEdit->text();
    this->dishNum = ui->setDishNum_lineEdit->text();

    if(*this->selfDishShowBar->getDishIndex() == "-1")
    {
        QSqlQuery query(*DB);
        QString sql = QString("select * from dishesInfo order by DishIndex desc");

        query.exec(sql);
        query.next();
        int index = query.value("DishIndex").toInt() + 1;

        // 写给数据库
        sql = QString("insert into dishesInfo "
                          "values('%1','%2','%3','%4','%5');"
                          )
                .arg(this->dishName)
                .arg(this->dishMoney)
                .arg(this->dishNum)
                .arg(this->dishImagePath)
                .arg(index);

        if(!query.exec(sql))
        {
            // 加入失败
            QMessageBox::critical(nullptr,"菜品选项卡错误","加入数据到数据库失败");
        }
        else
        {
            // 写给上层
            // 加入成功
            this->selfDishShowBar->setDishImagePath(new QString(this->dishImagePath));
            this->selfDishShowBar->setDishName(new QString(this->dishName));
            this->selfDishShowBar->setDishMoney(new QString(this->dishMoney));
            this->selfDishShowBar->setDishNum(new QString(this->dishNum));
            this->selfDishShowBar->setDishIndex(new QString(QString::number(index)));

            // 上层发送新增成功信号
            emit addSuccess();

            // 添加成功
            QMessageBox::information(nullptr,"菜品选项卡信息","添加菜品信息成功");
        }

    }
    else
    {
        // 写给数据库
        // 修改菜品信息
        QSqlQuery query(*DB);
        QString sql = QString("update dishesInfo set "
                          "DishName = '%1', DishMoney = '%2', DishNum = '%3', "
                          "DishImagePath = '%4' "
                          "where DishIndex = '%5';")
                    .arg(this->dishName)
                    .arg(this->dishMoney)
                    .arg(this->dishNum)
                    .arg(this->dishImagePath)
                    .arg(*this->selfDishShowBar->getDishIndex());
        if(!query.exec(sql))
        {
            // 加入失败
            QMessageBox::critical(nullptr,"菜品选项卡错误","修改数据到数据库失败");
        }
        else
        {
            // 写给上层
            // 加入成功
            this->selfDishShowBar->setDishImagePath(new QString(this->dishImagePath));
            this->selfDishShowBar->setDishName(new QString(this->dishName));
            this->selfDishShowBar->setDishMoney(new QString(this->dishMoney));
            this->selfDishShowBar->setDishNum(new QString(this->dishNum));

            // 上层发送新增成功信号
            emit addSuccess();

            // 修改成功
            QMessageBox::information(nullptr,"菜品选项卡信息","修改菜品信息成功");
        }

    }

    this->close();

}

void DishInfoBar::on_cancel_ptn_clicked()
{
    this->close();
}

void DishInfoBar::on_deleteDish_ptn_clicked()
{
    if(*this->selfDishShowBar->getDishIndex() == "-1") return;
    if(!this->selfDishShowBar)
    {
        QMessageBox::critical(nullptr,"选项卡错误","选项卡地址为空");
        return;
    }

    // 删除数据库中数据
    QSqlQuery query(*DB);
    QString sql = QString("delete from dishesInfo "
                          "where DishIndex = '%1';"
                          ).arg(*this->selfDishShowBar->getDishIndex());
    if(!query.exec(sql))
    {
        // 元素不存在，删除不存在元素
        QMessageBox::critical(nullptr,"菜品选项卡错误","删除了在数据库中不存在的数据，删除失败");
    }
    else
    {
        // 删除数据库中元素成功，交给上层删除程序中数据
        emit deleteSuccess();

        QMessageBox::information(nullptr,"菜品选项卡信息","删除菜品信息成功");
    }

    this->close();
}

