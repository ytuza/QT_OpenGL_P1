#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.paintGL();

    w.setTitle("OpenGL QT");
    w.resize(680,680);
    w.show();

    return a.exec();
}
