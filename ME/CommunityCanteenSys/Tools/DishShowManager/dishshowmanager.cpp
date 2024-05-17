#include "dishshowmanager.h"
#include "Tools/MenuAlgorithm/menualgorithm.h"
#include <QDebug>

DishShowManager::DishShowManager()
{

}

DishShowManager::~DishShowManager()
{
    for(int i = 0;i < dishShowes.size();i++)
    {
        if(dishShowes[i])
        {
            delete dishShowes[i];
            dishShowes[i] = nullptr;
        }
    }
}

bool DishShowManager::addDish(DishShowBar *t)
{
    if(t == nullptr) return false;

    t->hide();
    dishShowes.push_back(t);

    return true;
}

bool DishShowManager::deleteDish(QString dishName)
{
    for(int i = 0;i < dishShowes.size();i++)
    {
        if(MenuAlgorithm::KMPSearch(*dishShowes[i]->getDishName(), dishName) != -1)
        {
            if(dishShowes[i])
            {
                delete dishShowes[i];
                dishShowes[i] = nullptr;
            }
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
        if(MenuAlgorithm::KMPSearch(*dishShowes[i]->getDishName(), dishName) != -1)
        {
            return dishShowes[i];
        }
    }

    return nullptr;
}

DishShowBar *DishShowManager::operator[](int i)
{
    return dishShowes[i];
}

int DishShowManager::sizeDish()
{
    return dishShowes.size();
}
