#ifndef PAYPALBAR_H
#define PAYPALBAR_H

#include <QWidget>

namespace Ui {
class PayPalBar;
}

class PayPalBar : public QWidget
{
    Q_OBJECT

public:
    enum{
        OK = 0,
        NO
    };
    explicit PayPalBar(QWidget *parent,QString title,QString text);
    ~PayPalBar();

signals:
    void back(int ret);

private slots:
    void on_ok_ptn_clicked();

    void on_no_ptn_clicked();

private:
    Ui::PayPalBar *ui;
    QString paypalPath = "D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/PayPal/Paying.jpg";
};

#endif // PAYPALBAR_H
