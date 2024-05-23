#include "Windows\Login_Paper\loginwin.h"
#include "Tools/MenuAlgorithm/menualgorithm.h"

#include <QApplication>
#include <QDebug>

#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginwin w;
    w.show();

//    QWidget *w = new QWidget;
//    w->setGeometry(0,0,600,700);
//    QPixmap pixmap("D:/MyDesktop/Graduation/ME/CommunityCanteenSys/Image/Background_PICS/chart.png");//设定图片
//    pixmap = MenuAlgorithm::PixmapToRound(pixmap,0,w->width(),w->height());
//    QPalette palette;//创建一个调色板对象
//    palette.setBrush(w->backgroundRole(),QBrush(pixmap));//用调色板的画笔把映射到pixmap上的图片画到            frame.backgroundRole()这个背景上
//    w->setPalette(palette);//设置窗口调色板为palette，窗口和画笔相关联
//    w->show();

    return a.exec();
}

