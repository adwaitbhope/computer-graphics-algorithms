#include "hilbert.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hilbert w;
    w.show();

    return a.exec();
}
