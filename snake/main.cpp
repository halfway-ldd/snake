#include "widget.h"
#include"menu.h"
#include <QApplication>
#include<QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    menu m;
    m.show();
    return a.exec();
}
