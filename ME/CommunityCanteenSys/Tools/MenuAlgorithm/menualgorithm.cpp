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
