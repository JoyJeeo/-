#ifndef REGISTERWIN_H
#define REGISTERWIN_H

#include <QWidget>

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

private:
    Ui::registerwin *ui;
};

#endif // REGISTERWIN_H
