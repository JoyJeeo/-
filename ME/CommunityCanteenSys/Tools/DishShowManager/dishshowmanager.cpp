#include "dishshowmanager.h"
#include "Tools/MenuAlgorithm/menualgorithm.h"

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
