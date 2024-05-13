#ifndef BUYCARWIN_H
#define BUYCARWIN_H

#include <QWidget>

namespace Ui {
class buycarwin;
}

class buycarwin : public QWidget
{
    Q_OBJECT

public:
    explicit buycarwin(QWidget *parent = nullptr);
    ~buycarwin();

private:
    Ui::buycarwin *ui;
};

#endif // BUYCARWIN_H
