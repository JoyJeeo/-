#ifndef CAROUSELCHART_H
#define CAROUSELCHART_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QParallelAnimationGroup>

class CarouselChart : public QWidget
{
    Q_OBJECT

public:
    explicit CarouselChart(QVector<QString> addPic_path,QWidget *parent = nullptr);
    ~CarouselChart();

protected:
    void timerEvent(QTimerEvent* ev) override;

public slots:
    void on_leftBtn_clicked();
    void on_rightBtn_clicked();
    void on_animationState(); // 记录一个动画的During时间，bool判断

private:
    enum DIRECTION{DIRECTION_LEFT = 0, DIRECTION_RIGHT, DIRECTION_NONE}; // 轮播图的切图方向

    void paintEvent(QPaintEvent *event) override; // 加载窗体时会先调用绘制事件

    void init_labels(); // alt + enter生成实现函数
    void init_btns();

    void imageOrderMove(DIRECTION direction); // 图片轮播的方向函数
    void resetTimer(); // 重新设置计时器

private:
    QVector<QLabel*> labels;
    QVector<QString> pics_path;

    QPushButton* leftBtn;
    QPushButton* rightBtn;

    QParallelAnimationGroup *animation_group; // 并行动画组
    bool animationIsRunning;

    int cur_index;
    int old_index;

    int timer;

};

#endif // CAROUSELCHART_H
