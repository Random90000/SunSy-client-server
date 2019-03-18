#include "sunsystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SunSystem sun_system;
    sun_system.show();
    return a.exec();
}
