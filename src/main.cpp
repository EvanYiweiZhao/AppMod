#include <glew-1.11.0/include/GL/glew.h>
#include "mainWin.h"
#include <QtWidgets/QApplication>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    MainWin *window = new MainWin();

    return a.exec();
}