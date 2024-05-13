#ifndef DISHINFOBAR_H
#define DISHINFOBAR_H

#include <QWidget>
#include "Tools/DishShowBar/dishshowbar.h"

namespace Ui {
class DishInfoBar;
}

class DishInfoBar : public QWidget
{
    Q_OBJECT

public:
    explicit DishInfoBar(DishShowBar* t, QWidget *parent = nullptr);
    ~DishInfoBar();

signals:
    void addSuccess();
    void deleteSuccess(); // 1. dishInfo中对持久层和上层数据同时进行变换后；
                        // 2. 将变换对应结果传给上层再做进一步处理【链式传递】

private slots:
    void on_dishImagePathSelect_ptn_clicked();

    void on_commit_ptn_clicked();

    void on_cancel_ptn_clicked();

    void on_deleteDish_ptn_clicked();

private:
    Ui::DishInfoBar *ui;

    QString dishImagePath;
    QString dishName;
    QString dishMoney;
    QString dishNum;

    DishShowBar* selfDishShowBar;
};

#endif // DISHINFOBAR_H
