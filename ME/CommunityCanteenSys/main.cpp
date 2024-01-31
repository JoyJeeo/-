#include "controlwin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controlwin w;
    w.show();
    return a.exec();
}
