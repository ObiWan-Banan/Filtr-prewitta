#include "JAproj.h"
#include"bitmap.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JAproj w;
    w.show();
    return a.exec();
}
