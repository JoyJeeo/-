#include "adminwin.h"
#include "ui_adminwin.h"
#include <QSqlQuery>
#include "Tools/tool_00_environment.h"
#include <QDebug>
#include <QMessageBox>

/*
 * 对于空行的处理【现在的功能支持非空行的保存】
 * admin需要清楚，保存的用户名中不能有重名，且不能使用空行
*/
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

void adminwin::move_curRow_base(int curRow, int step) // step可正可负
{
    QSqlQuery query(*DB);
    query.exec("select * "
               "from logininfo order by curid;");

    int base_rowCnt = query.size();
    vector<int> biggers;
    for(int i = 0;i < base_rowCnt;i++)
    {
        query.next();
        if(query.value(2).toInt() > curRow)
        {
            biggers.push_back(query.value(2).toInt());
        }
    }

    int biggers_size = biggers.size();

    /*
     * 向大更新，必须从大到小更新
     * 向小更新，必须从小到大更新
     * 【就像推积木一样】【数据库会将所有符合where条件的数据一起进行更新】
     * 【因此，在这种条件下的移动数据和合并数据有了新的算法】
    */
    if(step < 0)
    {
        for(int i = 0;i < biggers_size;i++)
        {
            query.exec(QString("update logininfo set curid = '%1' "
                               "where curid = '%2';")
                      .arg(biggers[i] + step)
                      .arg(biggers[i]));
        }
    }
    else
    {
        for(int i = biggers_size - 1;i >= 0 ;i--)
        {
            query.exec(QString("update logininfo set curid = '%1' "
                               "where curid = '%2';")
                      .arg(biggers[i] + step)
                      .arg(biggers[i]));
        }
    }
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
        /*
         * Bar进度条的进度条规则为{0起始}[1,len]为有效进度长度
        */
        ui->progress_Bar->setMaximum(row);
        ui->progress_Bar->setValue(0);
        ui->process_Details->setText(QString("任务执行中..."));

        for (int i = 0;i < row; i++)
        {
            ui->progress_Bar->setValue(i + 1);
            query.next();
            ui->detailsTable->insertRow(i);
            for (int j = 0; j < column; j++)
            {
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
        ui->progress_Bar->setMaximum(row);
        ui->progress_Bar->setValue(0);
        ui->process_Details->setText(QString("任务执行中..."));

        for (int i = 0; i < row; i++)
        {
            ui->progress_Bar->setValue(i + 1);
            order = QString("update logininfo set username = '%1', "
                                    "pwd = '%2' "
                                    "where curid = '%3';")
                    .arg(ui->detailsTable->item(i,0)->text())
                    .arg(ui->detailsTable->item(i,1)->text())
                    .arg(i);
            query.exec(order);
        }

        ui->process_Details->setText(QString("完成"));
    }
}

void adminwin::on_update_status_btn_clicked()
{
    on_clear_btn_clicked();
    on_load_login_btn_clicked();
}

void adminwin::on_save_btn_clicked()
{
    ui->progress_Bar->setMaximum(3);
    ui->progress_Bar->setValue(0);
    ui->process_Details->setText(QString("任务执行中..."));
    int curRow = 0;
    /*
     * curRow = valid[0,...] invalid[-1]
     * 数据库的curid从1开始
    */
    curRow = ui->detailsTable->currentRow();
    //qDebug() << curRow;

    if(curRow != -1)
    {
        if(ui->detailsTable->item(curRow,0)->text() == "" || ui->detailsTable->item(curRow,1)->text() == "")
        {
            ui->progress_Bar->setValue(0);
            ui->process_Details->setText(QString("Error:添加失败，当前行存在空数据..."));
            return;
        }

        QSqlQuery query(*DB);
        ui->progress_Bar->setValue(1);

        QString order = QString("update logininfo set username = '%1', "
                                "pwd = '%2' "
                                "where curid = '%3';")
                .arg(ui->detailsTable->item(curRow,0)->text())
                .arg(ui->detailsTable->item(curRow,1)->text())
                .arg(curRow);
        ui->progress_Bar->setValue(2);

        if(query.exec(order))
        {
            ui->progress_Bar->setValue(3);
            ui->process_Details->setText(QString("更新成功..."));
        }
        else
        {
            ui->progress_Bar->setValue(3);
            ui->process_Details->setText(QString("更新失败..."));
        }

    }
    else
    {
        ui->progress_Bar->setValue(0);
        ui->process_Details->setText(QString("Warning:请选中要修改的条目..."));
    }

}

void adminwin::on_add_btn_clicked()
{
    ui->progress_Bar->setMaximum(3);
    ui->progress_Bar->setValue(0);
    ui->process_Details->setText(QString("任务执行中..."));
    int rowCnt = ui->detailsTable->rowCount();

    if(rowCnt != 0)
    {
        QSqlQuery query(*DB);
        QString order = QString("insert into logininfo(username,"
                                "pwd,curid) "
                                "values('%1', '%2', '%3');")
                            .arg("")
                            .arg("")
                            .arg(rowCnt);
        ui->progress_Bar->setValue(1);

        bool ok = query.exec(order);
        ui->progress_Bar->setValue(2);
        ui->detailsTable->insertRow(rowCnt);

        if(ok)
        {
            ui->progress_Bar->setValue(3);
            ui->process_Details->setText(QString("加入新行成功..."));
        }
        else
        {
            ui->progress_Bar->setValue(0);
            ui->process_Details->setText(QString("加入新行失败..."));
        }
    }
    else
    {
        ui->progress_Bar->setValue(0);
        ui->process_Details->setText(QString("Warning:当前记录为空，请先加载数据..."));
    }

}

void adminwin::on_insert_btn_clicked()
{
    ui->progress_Bar->setMaximum(3);
    ui->progress_Bar->setValue(0);
    ui->process_Details->setText(QString("任务执行中..."));
    int curRow = ui->detailsTable->currentRow();

    if(curRow != -1)
    {
        move_curRow_base(curRow - 1, 1);
        ui->progress_Bar->setValue(1);

        QSqlQuery query(*DB);
        QString order = QString("insert into logininfo(username,"
                                "pwd,curid) "
                                "values('%1', '%2', '%3');")
                            .arg("")
                            .arg("")
                            .arg(curRow);

        bool ok = query.exec(order);
        ui->progress_Bar->setValue(2);
        ui->detailsTable->insertRow(curRow);

        if(ok)
        {
            ui->progress_Bar->setValue(3);
            ui->process_Details->setText(QString("插入成功..."));
        }
        else
        {
            ui->progress_Bar->setValue(0);
            ui->process_Details->setText(QString("插入失败..."));
        }
    }
    else
    {
        ui->progress_Bar->setValue(0);
        ui->process_Details->setText(QString("Warning:当前记录为空，请先加载数据..."));
    }
}

void adminwin::on_delete_btn_clicked()
{
    // insert行和blank的插入数据
    ui->progress_Bar->setMaximum(5);
    ui->progress_Bar->setValue(0);
    ui->process_Details->setText(QString("任务执行中..."));

    int curRow = ui->detailsTable->currentRow();
    ui->progress_Bar->setValue(1);

    if(curRow != -1)
    {
        QSqlQuery query(*DB);
        bool del_ok = query.exec(QString("delete from logininfo "
                                         "where curid = '%1';")
                                .arg(curRow));

        ui->progress_Bar->setValue(2);

        if(del_ok)
        {
            ui->progress_Bar->setValue(3);
            move_curRow_base(curRow,-1);
            ui->progress_Bar->setValue(4);

            ui->detailsTable->removeRow(curRow);
            ui->progress_Bar->setValue(5);
            ui->process_Details->setText(QString("删除成功..."));
        }
        else
        {
            ui->progress_Bar->setValue(0);
            ui->process_Details->setText(QString("删除失败..."));
        }
    }
    else
    {
        ui->progress_Bar->setValue(0);
        ui->process_Details->setText(QString("Warning:当前记录为空,请先加载数据..."));
    }
}

















