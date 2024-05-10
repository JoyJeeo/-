#include "Windows\Login_Paper\loginwin.h"
#include "Tools/DishShowBar/dishshowbar.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginwin w;
    w.show();
    return a.exec();
}
