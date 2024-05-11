#ifndef USERICONLABEL_H
#define USERICONLABEL_H

#include <QLabel>

class UserIconLabel : public QLabel
{
    Q_OBJECT
public:
    explicit UserIconLabel(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *ev) override;

signals:
    void back(QString userIconPath);

};

#endif // USERICONLABEL_H
