#include "Windows\Login_Paper\loginwin.h"

#include <QApplication>
#include <QDebug>

#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginwin w;
    w.show();

    return a.exec();
}

