#ifndef ADMINWIN_H
#define ADMINWIN_H

#include <QWidget>

namespace Ui {
class adminwin;
}

class adminwin : public QWidget
{
    Q_OBJECT
    friend class controlwin;
public:
    explicit adminwin(QWidget *parent = nullptr);
    ~adminwin();

signals:
    void back();

private slots:
    void on_back_btn_clicked();

    void on_load_login_btn_clicked();

    void on_clear_btn_clicked();

    void on_save_all_btn_clicked();

private:
    void triggered();

private:
    Ui::adminwin *ui;
};

#endif // ADMINWIN_H
