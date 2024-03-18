#include "adminwin.h"
#include "ui_adminwin.h"
#include <QSqlQuery>
#include "Tools/tool_00_environment.h"
#include <QDebug>

adminwin::adminwin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminwin)
{
    this->setFixedSize(1081,661);
    ui->setupUi(this);
    ui->detailsTable->setAlternatingRowColors(true);
}

adminwin::~adminwin()
{
    delete ui;
}

void adminwin::on_back_btn_clicked()
{
    this->hide();
    emit back();
}

void adminwin::triggered()
{
    on_clear_btn_clicked();
    on_load_login_btn_clicked();

}

void adminwin::on_load_login_btn_clicked()
{
    ui->detailsTable->setColumnCount(2);
    ui->detailsTable->setHorizontalHeaderLabels({"username","pwd"});

    QSqlQuery query(*DB);

    query.prepare("select username,"
                  "pwd "
                  "from logininfo order by curid;");
    query.exec();

    int row = query.size();
    int column = ui->detailsTable->columnCount();

    if(row > 0)
    {
        ui->progress_Bar->setMaximum(row - 1);
        ui->progress_Bar->setValue(0);
        ui->process_Details->setText(QString("任务执行中..."));

        for (int i = 0;i < row; i++)
        {
            ui->progress_Bar->setValue(i);
            query.next();
            for (int j = 0; j < column; j++)
            {
                ui->detailsTable->setRowCount(i + 1);
                ui->detailsTable->setItem(i,j,new QTableWidgetItem(query.value(j).toString()));
                ui->detailsTable->item(i,j)->setTextAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
            }
        }

        ui->process_Details->setText(QString("完成"));
    }
    ui->detailsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->detailsTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void adminwin::on_clear_btn_clicked()
{
    ui->detailsTable->clearContents();
    ui->detailsTable->setRowCount(0);
    ui->detailsTable->setColumnCount(0);
}

void adminwin::on_save_all_btn_clicked()
{
    int row = ui->detailsTable->rowCount();
    QString order = "";
    QSqlQuery query(*DB);

    if(row > 0)
    {
        ui->progress_Bar->setMaximum(row - 1);
        ui->progress_Bar->setValue(0);
        ui->process_Details->setText(QString("任务执行中..."));

        for (int i = 0; i < row; i++)
        {
            ui->progress_Bar->setValue(i);
            order = QString("update logininfo set username = '%1', "
                                    "pwd = '%2' "
                                    "where curid = '%3';")
                    .arg(ui->detailsTable->item(i,0)->text())
                    .arg(ui->detailsTable->item(i,1)->text())
                    .arg(i + 1);
            query.exec(order);
        }

        ui->process_Details->setText(QString("完成"));
    }
}
