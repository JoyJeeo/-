#ifndef DISHSHOWMANAGER_H
#define DISHSHOWMANAGER_H

#include <QVector>
#include "Tools/DishShowBar/dishshowbar.h"

#define DELETE(ptr) if(ptr != nullptr) delete ptr

class DishShowManager
{
public:
    DishShowManager();
    ~DishShowManager();

    // 增
    bool addDish(DishShowBar* t);
    // 删
    bool deleteDish(QString dishName);
    // 查
    DishShowBar* findDish(QString dishName);

    DishShowBar* operator[](int i);

    // 容器大小
    int sizeDish();

private:
    QVector<DishShowBar*> dishShowes;
};

#endif // DISHSHOWMANAGER_H
