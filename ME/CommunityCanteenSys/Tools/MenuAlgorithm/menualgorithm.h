#ifndef MENUALGORITHM_H
#define MENUALGORITHM_H

#include <QString>
#include <QVector>

class MenuAlgorithm
{
public:
    // KMP线性时间复杂度O(m+n)的快速模糊匹配方法
    static int KMPSearch(QString s,QString cmp);

private:
    MenuAlgorithm();

    static QVector<int> get_kmp(QString cmp);

};

#endif // MENUALGORITHM_H
