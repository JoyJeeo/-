#ifndef CAROUSELCHARTBAR_H
#define CAROUSELCHARTBAR_H

#include <QLabel>

class CarouselChartBar : public QLabel
{
    Q_OBJECT
public:
    explicit CarouselChartBar(QString annoImagePath,
                              QString annoIndex,
                              QWidget *parent = nullptr);
    ~CarouselChartBar();

signals:
    void selectStart();
    void selectEnd();

private:
    void mousePressEvent(QMouseEvent *ev) override;


private:
    QString annoImagePath;
    QString annoIndex;

};

#endif // CAROUSELCHARTBAR_H
