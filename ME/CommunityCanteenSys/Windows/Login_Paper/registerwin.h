#ifndef REGISTERWIN_H
#define REGISTERWIN_H

#include <QWidget>
#include "Tools/HoverableLabel/hoverablelabel.h"

namespace Ui {
class registerwin;
}

class registerwin : public QWidget
{
    Q_OBJECT

public:
    explicit registerwin(QWidget *parent = nullptr);
    ~registerwin();

signals:
    void register_complete();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_register_pbtn_clicked();

    void on_pushButton_clicked();
    void on_enter_watchEye();
    void on_leave_watchEye();

private:
    Ui::registerwin *ui;
    HoverableLabel *watchEye;
};

#endif // REGISTERWIN_H
