#include "carouselchart.h"
#include "ui_carouselchart.h"

#include <QPropertyAnimation>
#include <QDebug>

static int Timer_time = 5000; // ms
static int Pic_Smooth_time = 1000; // ms

CarouselChart::CarouselChart(QVector<QString> addPic_path,QWidget *parent) :
    pics_path(addPic_path),
    QWidget(parent),
    timer(this->startTimer(Timer_time)),
    animation_group(new QParallelAnimationGroup(this)),
    animationIsRunning(false),
    cur_index(0),
    old_index(0)
{
    this->setGeometry(0,0,900,700);
    init_labels();
    init_btns();

    connect(leftBtn,&QPushButton::clicked,this,&CarouselChart::on_leftBtn_clicked);
    connect(rightBtn,&QPushButton::clicked,this,&CarouselChart::on_rightBtn_clicked);
    connect(animation_group,&QParallelAnimationGroup::stateChanged,this,&CarouselChart::on_animationState);
}

CarouselChart::~CarouselChart()
{

}

void CarouselChart::timerEvent(QTimerEvent *ev)
{   
    if(animationIsRunning)
        return;
    imageOrderMove(DIRECTION_RIGHT);
}

void CarouselChart::on_leftBtn_clicked()
{
    if(animationIsRunning)
        return;
    resetTimer();
    imageOrderMove(DIRECTION_LEFT);
}

void CarouselChart::on_rightBtn_clicked()
{
    if(animationIsRunning)
        return;
    resetTimer();
    imageOrderMove(DIRECTION_RIGHT);
}

void CarouselChart::on_animationState() // 动画组每次start的开始和结束都会发送信号，我让他调用这个函数
{
    // 【动画组第一次运行都是Running状态，只有clear后才回重新开始Running；如果不clear，则加载动画start后，每次都是Stop】
     QAbstractAnimation::State state = animation_group->state(); // 获取并行动画组当前的运行状态
//     qDebug() << state;
     if(state == QAbstractAnimation::Running)
     {
         animationIsRunning = true; // 根据动画组的Running Stop来夹住动画的During时间
     }
     else if(state == QAbstractAnimation::Stopped)
     {
        animation_group->clear(); // 清空动画组 重新开始 【会释放掉动画组中new出来的所有对象】
        labels[old_index]->hide(); // 在动画运行结束后，再将图片隐藏，防止图片叠加【必须依赖动画信号最后来隐藏之前的图片】
        animationIsRunning = false;
     }
}

void CarouselChart::paintEvent(QPaintEvent *event) // 重绘label【label不会随着widget大小变化一起绘制】
{
    labels[cur_index]->resize(this->size());

    leftBtn->move(0, this->size().height() / 2 - 40);
    rightBtn->move(this->size().width() - 80, this->size().height() / 2 - 40);

}

void CarouselChart::init_labels()
{
    for(int i = 0;i < pics_path.size();i++)
    {
        QLabel* label = new QLabel(this);
        label->setPixmap(QPixmap(pics_path[i])); // label添加图片
        label->setScaledContents(true); // 设置标签为可扩展内容，才能够设置标签的大小可变
        label->resize(this->size()); // 设置label的大小与widget一样
        if(i != cur_index) label->hide();

        labels << label;
    }
}

void CarouselChart::init_btns()
{ 
    QIcon leftIcon(":/image/leftArrow.png");
    leftBtn = new QPushButton(leftIcon, "", this);
    leftBtn->move(0, this->size().height() / 2 - 40);
    leftBtn->setMinimumSize(80,80);
    leftBtn->setStyleSheet(
                "QPushButton{background-color: rgb(178,180,164,40%);  border-radius: 40px;border: 1px;}"
                "QPushButton:hover{background-color: gray; border-radius: 40px;border: 1px;}"
                "QPushButton:pressed{background-color: rgb(255,255,255); border-radius: 40px;border: 1px;}"
                           );

    QIcon rightIcon(":/image/rightArrow.png");
    rightBtn = new QPushButton(rightIcon, "", this);
    rightBtn->move(this->size().width() - 80, this->size().height() / 2 - 40);
    rightBtn->setMinimumSize(80,80);
    rightBtn->setStyleSheet(
                "QPushButton{background-color: rgb(178,180,164,40%);  border-radius: 40px;border: 1px;}"
                "QPushButton:hover{background-color: gray; border-radius: 40px;border: 1px;}"
                "QPushButton:pressed{background-color: rgb(255,255,255); border-radius: 40px;border: 1px;}"
                            );
}

void CarouselChart::imageOrderMove(CarouselChart::DIRECTION direction)
{
    old_index = cur_index;

    int order = 0;
    if(direction == DIRECTION::DIRECTION_LEFT)
        order = -1;
    else if(direction == DIRECTION::DIRECTION_RIGHT)
        order = 1;
    cur_index = (cur_index + order + labels.size()) % labels.size();

    // 动画的效果有“pos” 、“opacity ”、“geometry”，“sacleFactor”，分别控制位置、透明度、形状，大小;
    QPropertyAnimation *animation_old = new QPropertyAnimation(labels[old_index], "geometry",this); // 给label添加动画【动画只是一个效果，附加在空间上】
    animation_old->setDuration(Pic_Smooth_time); // 动画的持续时间
    animation_old->setLoopCount(1);
    QPropertyAnimation *animation_new = new QPropertyAnimation(labels[cur_index], "geometry",this);
    animation_new->setDuration(Pic_Smooth_time);
    animation_new->setLoopCount(1);

    // 【点击左侧按钮，想看左侧的图片，图片动画应该是向右滑动】
    if(direction == DIRECTION::DIRECTION_LEFT)
    {
        // 设置动画的开始位置和结束位置
        // value:它是一个QVariant类型，QPoint对应pos，QRect对应geometry，单个数值对应opacity 或者sacleFactor
        animation_old->setStartValue(QRect(0,0,this->size().width(),this->size().height()));
        animation_old->setEndValue(QRect(this->size().width(),0,this->size().width(),this->size().height()));

        animation_new->setStartValue(QRect(-this->size().width(),0,this->size().width(),this->size().height()));
        animation_new->setEndValue(QRect(0,0,this->size().width(),this->size().height()));
    }
    else if(direction == DIRECTION::DIRECTION_RIGHT)
    {
        animation_old->setStartValue(QRect(0,0,this->size().width(),this->size().height()));
        animation_old->setEndValue(QRect(-this->size().width(),0,this->size().width(),this->size().height()));

        animation_new->setStartValue(QRect(this->size().width(),0,this->size().width(),this->size().height()));
        animation_new->setEndValue(QRect(0,0,this->size().width(),this->size().height()));
    }

    labels[cur_index]->show();

    // 将设置好的两个控件的动画加入并行动画组，让他们一起展示
    animation_group->addAnimation(animation_old);
    animation_group->addAnimation(animation_new);

    animation_group->setDirection(QAbstractAnimation::Forward);
    animation_group->start(); // 开始并行执行加载的动画
}

void CarouselChart::resetTimer()
{
    killTimer(timer); // 干掉之前的计时器
    timer = this->startTimer(5000); // 重新创建一个计时器，重新开始计时
}




























