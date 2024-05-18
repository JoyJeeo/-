#include "buycarwin.h"
#include "ui_buycarwin.h"
#include "Tools/tool_00_environment.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include "Tools/MenuAlgorithm/menualgorithm.h"
#include <QCheckBox>
#include <QVBoxLayout>

buycarwin::buycarwin(QString control_username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::buycarwin),
    control_username(control_username)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    this->setWindowTitle(control_username + "的购物车");

    QImage *image = new QImage("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/BuyCar_ICONs/BuyCarIcon.png");
    image = new QImage(image->scaled(81, 81, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->buyCarIcon_lab->setPixmap(QPixmap::fromImage(*image));

    ui->allPay_lab->setText("总计金额：0元");
    ui->allSelect_ckbox->setTristate(true);
    ui->allSelect_ckbox->setCheckState(Qt::Unchecked);

    buyCarDishInitFromDB();
    showBuyCarDish();
}

buycarwin::~buycarwin()
{
    delete ui;
    for(int i = 0;i < buyCarDishes.size();i++)
    {
        if(buyCarDishes[i])
        {
            delete buyCarDishes[i];
            buyCarDishes[i] = nullptr;
        }
    }
}

void buycarwin::buyCarDishInitFromDB()
{
    QString buyCarTable = control_username + "BuyCar";

    QSqlQuery query(*DB);
    QString sql = QString("select * from %1 order by DishIndex desc;")
            .arg(buyCarTable);

    query.exec(sql);

    while(query.next())
    {
        QString DishName = query.value("DishName").toString();
        QString DishMoney = query.value("DishMoney").toString();
        QString DishBuyNum = query.value("DishBuyNum").toString();
        QString DishImagePath = query.value("DishImagePath").toString();

        int money = MenuAlgorithm::GetQStringByFirstNum(DishMoney);
        int buyNum = MenuAlgorithm::GetQStringByFirstNum(DishBuyNum);
        int dishPay = money * buyNum;

        BuyCarDishShowBar *t = new BuyCarDishShowBar(DishImagePath,DishName,DishMoney,DishBuyNum,
                                                   "总额：" + QString::number(dishPay) + "元"
                                                   ,ui->scrollAreaContents);

        connect(t->getSelectCheckBox(),&QCheckBox::clicked,this,&buycarwin::refreshAllSelect_Allpay);
        buyCarDishes.push_back(t);
    }

}

void buycarwin::showBuyCarDish()
{
    int x = 30,y = 20;
    int dx = 220, dy = 250;

    for(int i = 0;i < buyCarDishes.size();i++)
    {
        buyCarDishes[i]->move(x + dx * (i % 4), y + dy * (i / 4));
    }

    // 重置content的高度，产生滚动条
    int realHeight = y + (buyCarDishes.size() / 4 + 1) * dy;
    if(realHeight > ui->scrollAreaContents->height())
        ui->scrollAreaContents->setMinimumHeight(realHeight);
}

void buycarwin::refreshAllSelect_Allpay()
{
    int allPay = 0;
    bool checkedFlag = false;
    bool uncheckedFlag = false;

    for(int i = 0;i < buyCarDishes.size();i++)
    {
        if(buyCarDishes[i]->getSelectCheckBox()->isChecked())
        {
            checkedFlag = true;
            allPay += MenuAlgorithm::GetQStringByFirstNum(buyCarDishes[i]->getAllMoney());
        }
        else uncheckedFlag = true;
    }

    // 设置allPay
    ui->allPay_lab->setText("总计金额：" + QString::number(allPay) + "元");

    // 设置allSelect
    ui->allSelect_ckbox->setTristate(true);
    if(checkedFlag && uncheckedFlag) ui->allSelect_ckbox->setCheckState(Qt::PartiallyChecked);
    else if(checkedFlag && !uncheckedFlag) ui->allSelect_ckbox->setCheckState(Qt::Checked);
    else ui->allSelect_ckbox->setCheckState(Qt::Unchecked);
}

void buycarwin::on_allSelect_ckbox_clicked()
{
    int allPay = 0;
    ui->allSelect_ckbox->setTristate(false);

    Qt::CheckState checkStatus = ui->allSelect_ckbox->checkState();

    for(int i = 0;i < buyCarDishes.size();i++)
    {
        buyCarDishes[i]->getSelectCheckBox()->setCheckState(checkStatus);
        if(checkStatus == Qt::Checked)
            allPay += MenuAlgorithm::GetQStringByFirstNum(buyCarDishes[i]->getAllMoney());
    }

    // 设置allPay
    ui->allPay_lab->setText("总计金额：" + QString::number(allPay) + "元");
}

void buycarwin::on_deleteSelect_ptn_clicked()
{
    bool flag = false;
    QString buyCarTable = control_username + "BuyCar";

    for(int i = 0;i < buyCarDishes.size();)
    {
        if(buyCarDishes[i]->getSelectCheckBox()->isChecked())
        {
            // DB删除
            QSqlQuery query(*DB);
            QString sql = QString("delete from %1 where DishName = '%2';")
                    .arg(buyCarTable)
                    .arg(buyCarDishes[i]->getDishName());

            query.exec(sql);

            if(!flag) flag = true;
            delete buyCarDishes[i];
            buyCarDishes.remove(i);
        }
        else i++;
    }

    if(flag)
    {
        ui->allPay_lab->setText("总计金额：0元");
        ui->allSelect_ckbox->setCheckState(Qt::Unchecked);

        showBuyCarDish();
    }
}

void buycarwin::on_cancel_ptn_clicked()
{
    this->close();
}

void buycarwin::on_buy_ptn_clicked()
{
    if(buyCarDishes.size() == 0)
    {
        QMessageBox::warning(nullptr,"购买警告","请先向购物车中添加菜品，再进行购买！");
        return;
    }

    QString text = "确认购买，%1";
    text = text.arg(ui->allPay_lab->text());
    int check = QMessageBox::information(nullptr,"购物车购买信息",text,QMessageBox::Ok | QMessageBox::Close);

    if(check == QMessageBox::Ok)
    {
        // 付款界面
        QImage *paypal = new QImage("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/PayPal/Paying.jpg");
        QDialog *w = new QDialog;
        QVBoxLayout *layout = new QVBoxLayout; // 在布局中添加控件，最后将布局添加到窗体中
        QLabel *label = new QLabel();
        label->setPixmap(QPixmap::fromImage(*paypal));
        layout->addWidget(label);
        w->setLayout(layout);
        w->move(0,0);
        w->exec();

        QString orderDetailTable = control_username + "OrderDetail";

        QSqlQuery query(*DB);
        // 获取订单创建时间
        QString sql = QString("select now();");
        query.exec(sql);
        query.next();
        QString nowTime = query.value(0).toString();

        for(int i = 0;i < buyCarDishes.size();i++)
        {
            if(buyCarDishes[i]->getSelectCheckBox()->isChecked())
            {
                sql = QString("insert into %1 values"
                              "('%2','%3','%4','%5','%6')")
                        .arg(orderDetailTable)
                        .arg(buyCarDishes[i]->getDishName())
                        .arg(buyCarDishes[i]->getDishMoney())
                        .arg(buyCarDishes[i]->getDishBuyNum())
                        .arg(buyCarDishes[i]->getImagePath())
                        .arg(nowTime);
                query.exec(sql);
            }
        }

        on_deleteSelect_ptn_clicked();
        QMessageBox::information(nullptr,"购买成功","购买成功！");
    }
}














