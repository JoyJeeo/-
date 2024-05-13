#ifndef ODERDETAILBAR_H
#define ODERDETAILBAR_H

#include <QWidget>

namespace Ui {
class OderDetailBar;
}

class OderDetailBar : public QWidget
{
    Q_OBJECT

public:
    explicit OderDetailBar(QString controlwin_username, QString takeOrderTime, QWidget *parent = nullptr);
    ~OderDetailBar();

    QString getTakeOrderTime();

signals:
    void deleteOrder(OderDetailBar* );

private slots:
    void on_delete_ptn_clicked();

    void on_detail_ptn_clicked();

private:
    Ui::OderDetailBar *ui;

    QString controlwin_username;
    QString takeOrderTime;

};

#endif // ODERDETAILBAR_H
