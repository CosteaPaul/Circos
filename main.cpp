#include <QtGui/QApplication>
#include "circosmain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CircosMain w;
    w.show();

    return a.exec();
}
