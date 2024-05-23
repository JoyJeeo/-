#ifndef HOVERABLELABEL_H
#define HOVERABLELABEL_H

#include <QLabel>

class HoverableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit HoverableLabel(QWidget *parent = nullptr);

signals:
    void mouseEntered();
    void mouseLeft();

protected:
    void enterEvent(QEvent *event) override
    {
        emit mouseEntered();
    }

    void leaveEvent(QEvent *event) override
    {
        emit mouseLeft();
    }
};

#endif // HOVERABLELABEL_H
