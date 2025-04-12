#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SudokuModel m;
    MainWindow w(&m);
    w.show();
    return a.exec();
}
