#include "menualgorithm.h"

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
