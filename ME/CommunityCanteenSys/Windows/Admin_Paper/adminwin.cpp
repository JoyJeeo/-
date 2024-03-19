#include "adminwin.h"
#include "ui_adminwin.h"
#include <QSqlQuery>
#include "Tools/tool_00_environment.h"
#include <QDebug>
#include <QMessageBox>

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

bool adminwin::is_insert(int index)
{
    bool flage = false;

    for(auto dex : insert_indexs)
    {
        if(dex == index)
        {
            flage = true;
            break;
        }
    }

    return flage;
}

void adminwin::erase_insert(int index)
{
    insert_indexs.remove(index);
}

void adminwin::insert_insert(int index)
{
    for(auto pi = insert_indexs.begin();pi != insert_indexs.end();pi++)
    {
        if(*pi > index) *pi++;
    }
    insert_indexs.push_back(index);
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
        // 修改save all ，table_rowCnt和base_rowCnt之间最小的内部做update，table到base做delete，base到table做insert
        // 每次执行完，将insert_indexs全部清空

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

void adminwin::on_update_status_btn_clicked()
{
    on_clear_btn_clicked();
    on_load_login_btn_clicked();
}

void adminwin::on_save_btn_clicked()
{
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
            QSqlQuery query(*DB);
            query.exec("select username,"
                       "pwd "
                       "from logininfo order by curid;");
            int base_rowCnt = query.size();

            ui->progress_Bar->setMaximum(base_rowCnt - row);
            ui->progress_Bar->setValue(0);
            ui->process_Details->setText(QString("任务执行中..."));

            for(int i = row;i < base_rowCnt;i++)
            {
                ui->progress_Bar->setValue(i - row);
                query.exec(QString("update logininfo set curid = '%1', "
                                   "where curid = '%2';")
                          .arg(i + 2)
                          .arg(i + 1));
            }

            insert_index = row;
            ui->detailsTable->insertRow(row);
            ui->process_Details->setText(QString("完成"));

            // 需要空行的计数，delete后没事，不空后保存成功没事，空着行保存则报错，delete空行时再将下面的数据base上移
            QMessageBox::critical(this, "提示", "添加失败，当前行存在空数据！");
            return;
        }

        QSqlQuery query(*DB);
        query.exec("select username,"
                   "pwd "
                   "from logininfo order by curid;");
        int base_rowCnt = query.size();

        if(curRow + 1 <= base_rowCnt)
        {
            QString order = QString("update logininfo set username = '%1', "
                                    "pwd = '%2' "
                                    "where curid = '%3';")
                    .arg(ui->detailsTable->item(curRow,0)->text())
                    .arg(ui->detailsTable->item(curRow,1)->text())
                    .arg(curRow + 1);
            if(query.exec(order))
                ui->process_Details->setText(QString("更新成功..."));
            else
                ui->process_Details->setText(QString("更新失败..."));
        }
        else
        {
            QString insetOrder = QString("insert into logininfo(username,"
                                         "pwd,curid) "
                                         "values('%1', '%2', '%3');")
                    .arg(ui->detailsTable->item(curRow,0)->text())
                    .arg(ui->detailsTable->item(curRow,1)->text())
                    .arg(curRow + 1);

            if(query.exec(insetOrder))
                ui->process_Details->setText(QString("添加成功..."));
            else
                ui->process_Details->setText(QString("添加失败..."));
        }

    }
    else
        QMessageBox::warning(this, "提示", "请选中要修改的条目！");

}

void adminwin::on_add_btn_clicked()
{
    int rowCnt = ui->detailsTable->rowCount();
    //qDebug() << rowCnt;

    if(rowCnt != 0)
    {
        ui->detailsTable->insertRow(rowCnt);
        insert_indexs.push_back(rowCnt);
    }

    else
        QMessageBox::warning(this, "提示", "当前记录为空，请先加载数据！");

}

void adminwin::on_insert_btn_clicked()
{
    int row = 0;
    row = ui->detailsTable->currentRow();
    //qDebug() << row;

    if(row != -1)
    {
        QSqlQuery query(*DB);
        query.exec("select username,"
                   "pwd "
                   "from logininfo order by curid;");
        int base_rowCnt = query.size();

        ui->progress_Bar->setMaximum(base_rowCnt - row);
        ui->progress_Bar->setValue(0);
        ui->process_Details->setText(QString("任务执行中..."));

        for(int i = row;i < base_rowCnt;i++)
        {
            ui->progress_Bar->setValue(i - row);
            query.exec(QString("update logininfo set curid = '%1', "
                               "where curid = '%2';")
                      .arg(i + 2)
                      .arg(i + 1));
        }

        insert_insert(row); // 每次插入还要更新它后面的dex数值
        ui->detailsTable->insertRow(row);
        ui->process_Details->setText(QString("完成"));
    }
    else
        QMessageBox::warning(this, "提示", "当前记录为空，请先加载数据！");
}

void adminwin::on_delete_btn_clicked()
{
    // insert行和blank的插入数据
}
