#ifndef DISHTURNPAGEBAR_H
#define DISHTURNPAGEBAR_H

#include <QWidget>
#include <QVector>

namespace Ui {
class DishTurnPageBar;
}

class DishTurnPageBar : public QWidget
{
    Q_OBJECT

public:
    explicit DishTurnPageBar(QWidget *parent);
    ~DishTurnPageBar();

private slots:
    void on_curIndex_lineEdit_textEdited(const QString &arg1);

    void on_left_ptn_clicked();

    void on_right_ptn_clicked();

private:
    Ui::DishTurnPageBar *ui;

    QWidget *parent;

    int curIndex = 1;
    const int pageShowNum = 6;

};

#endif // DISHTURNPAGEBAR_H
