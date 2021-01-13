#include "pinger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pinger w;
    w.show();
    return a.exec();
}
