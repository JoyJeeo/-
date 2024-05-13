#ifndef DISHTURNPAGEBAR_H
#define DISHTURNPAGEBAR_H

#include <QWidget>
#include <QVector>
#include <Tools/DishShowManager/dishshowmanager.h>
#include <QScrollArea>
#include <QScrollBar>

namespace Ui {
class DishTurnPageBar;
}

class DishTurnPageBar : public QWidget
{
    Q_OBJECT

public:
    explicit DishTurnPageBar(QString *controlwin_username, QScrollArea* scrollArea, QWidget *parent = nullptr);
    ~DishTurnPageBar();

    // 增
    bool addDish(DishShowBar* t);
    // 删
    bool deleteDish(QString dishName);
    // 查
    DishShowBar* findDish(QString dishName);

    // 容器大小
    int sizeDish();

    void dishInitfromDB();

    void dishShow();


private slots:
    void on_curIndex_lineEdit_textEdited(const QString &arg1);

    void on_left_ptn_clicked();

    void on_right_ptn_clicked();

    void on_pageIndex_lineEdit_textChanged(const QString &arg1);

    void slot_addDishShowBarSuccess(DishShowBar* self);
    void slot_deleteDishShowBarSuccess(DishShowBar* self);

private:
    Ui::DishTurnPageBar *ui;

    QString *controlwin_username;

    QScrollArea* scrollArea;
    QWidget* scrollAreaContents;

    int curIndex = 0;
    const int x = 10, y = 230;
    const int pageShowNum = 6;
    DishShowManager dishManager;

};

#endif // DISHTURNPAGEBAR_H
