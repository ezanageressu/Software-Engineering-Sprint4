#include "produce_pencil.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    produce_pencil pencil;
    pencil.show();

    return a.exec();
}
