#include "dishshowmanager.h"

DishShowManager::DishShowManager()
{

}

DishShowManager::~DishShowManager()
{
    for(int i = 0;i < dishShowes.size();i++)
        DELETE(dishShowes[i]);
}

bool DishShowManager::addDish(DishShowBar *t)
{
    if(t == nullptr) return false;

    dishShowes.push_back(t);

    return true;
}

bool DishShowManager::deleteDish(QString dishName)
{
    for(int i = 0;i < dishShowes.size();i++)
    {
        if(*dishShowes[i]->getDishName() == dishName)
        {
            DELETE(dishShowes[i]);
            dishShowes.remove(i);
            return true;
        }
    }

    return false;
}

DishShowBar *DishShowManager::findDish(QString dishName)
{
    for(int i = 0;i < dishShowes.size();i++)
    {
        if(*dishShowes[i]->getDishName() == dishName)
        {
            return dishShowes[i];
        }
    }

    return nullptr;
}

int DishShowManager::sizeDish()
{
    return dishShowes.size();
}
