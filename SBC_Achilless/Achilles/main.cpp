#include <QCoreApplication>
#include "gamepad.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Gamepad gp;

    return a.exec();
}
