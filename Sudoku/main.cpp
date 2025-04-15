#include "mainwindow.h"

#include <QApplication>
#include <Box2D/Box2D.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SudokuModel m;
    MainWindow w(&m);
    // Define the gravity vector.
    b2Vec2 gravity(0.0f, -10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    b2World world(gravity);

    MainWindow w;
    w.show();
    return a.exec();
}
