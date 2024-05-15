#include "menualgorithm.h"
#include <QBitmap>
#include <QPainter>

int MenuAlgorithm::KMPSearch(QString s, QString cmp)
{
    QVector<int> kmp = get_kmp(cmp);

    assert(kmp.size() > 0);

    for(int i = 0,j = 0;i < s.size();)
    {
        while(j != -1 && s[i] != cmp[j]) j = kmp[j];

        if(j == cmp.size() - 1)
        {
            return (i - cmp.size() + 1);
        }
        i++,j++;
    }

    return -1;
}

int MenuAlgorithm::GetQStringByFirstNum(QString str)
{
    // 要求字符串长度小与50
    if(str.size() > 50) return -1;

    bool numIndex[51] = {false}; // 最后一个一定为false 作为结束标志

    for(int i = 0;i < str.size();i++)
    {
        if(str[i] >= '0' && str[i] <= '9') numIndex[i] = true;
    }

    QString num = "";
    for(int i = 0;i < 51;i++)
    {
        if(numIndex[i]) num += str[i];
        if(!numIndex[i] && num.size() != 0) break;
    }

    return num.size() != 0 ? num.toInt() : -1;
}

QString MenuAlgorithm::replaceQStringByFirstNum(QString str, int newNum)
{
    // 要求字符串长度小与50
    if(str.size() > 50) return QString();

    bool numIndex[51] = {false}; // 最后一个一定为false 作为结束标志

    for(int i = 0;i < str.size();i++)
    {
        if(str[i] >= '0' && str[i] <= '9') numIndex[i] = true;
    }

    int pre = -1, post = -1;
    for(int i = 0;i < 50;i++)
    {
        if(!numIndex[i] && numIndex[i + 1]) pre = i + 1;
        if(numIndex[i] && !numIndex[i + 1]) post = i;

        if(pre != -1 && post != -1) break;
    }

    QString pre_str = str.mid(0, pre);
    QString post_str = str.mid(post + 1);

    return pre_str + QString::number(newNum) + post_str;
}

QPixmap MenuAlgorithm::PixmapToRound(const QPixmap &srcPixmap, const int &radius, const int &width, const int &height)
{
    // 目标图片尺寸
       QSize desSize(width, height);

       // 新建一个目标大小的画布Qpixmap
       QPixmap desPixMap(desSize);
       // 填充透明色作为背景
       desPixMap.fill(Qt::transparent);

       //以QPixmap 为绘画背景进行画笔绘制
       QPainter painter(&desPixMap);
       painter.setRenderHints(QPainter::Antialiasing); //抗锯齿
       painter.setRenderHints(QPainter::SmoothPixmapTransform); //平滑像素图变换

       QPainterPath path;//绘制路径
       //绘制圆角矩形，其中最后两个参数值的范围为（0-99），就是圆角的px值
       path.addRoundedRect(0, 0, desSize.width(), desSize.height(), radius, radius);

       // 将绘制的圆角矩形路径中内容进行裁剪
       painter.setClipPath(path);

       //将图片绘制到desPixmap中，IgnoreAspectRatio忽视图片比例
       painter.drawPixmap(0, 0, desSize.width(), desSize.height(), srcPixmap.scaled(desSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

       painter.setClipping(false); // 关闭裁剪

       return desPixMap;
}

//QPixmap MenuAlgorithm::PixmapToRound(QPixmap &src, int radius)
//{
//    if (src.isNull()) {
//        return QPixmap();
//    }

//    QSize size(2 * radius, 2 * radius);
//    QBitmap mask(size);
//    QPainter painter(&mask);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setRenderHint(QPainter::SmoothPixmapTransform);
//    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
//    painter.setBrush(QColor(0, 0, 0));
//    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);

//    QPixmap image = src.scaled(size);
//    image.setMask(mask);
//    return image;
//}

QVector<int> MenuAlgorithm::get_kmp(QString cmp)
{
    if(cmp.size() <= 0) return QVector<int>();

    QVector<int> kmp(cmp.size(),0);
    kmp[0] = -1;
    int j = -1,i = 0;
    while(i < cmp.size() - 1)
    {
        if(j == -1 || cmp[j] == cmp[i]) kmp[++i] = ++j;
        else j = kmp[j];
    }

    return kmp;
}

MenuAlgorithm::MenuAlgorithm()
{

}
