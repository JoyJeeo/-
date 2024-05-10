#ifndef BUYNUMBAR_H
#define BUYNUMBAR_H

#include <QWidget>

namespace Ui {
class BuyNumBar;
}

class BuyNumBar : public QWidget
{
    Q_OBJECT

public:
    explicit BuyNumBar(QWidget *parent = nullptr);
    ~BuyNumBar();

    int getBuyNum();

    void resetBuyNum();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_plus_ptn_clicked();

    void on_minus_ptn_clicked();

private:
    Ui::BuyNumBar *ui;

    int buynum = 1;
};

#endif // BUYNUMBAR_H
