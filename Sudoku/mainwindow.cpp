#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , world(b2Vec2(0.0f, -10.0f))
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    firstLabel = ui->firstLabel;

    connect(timer, &QTimer::timeout, this, &MainWindow::updatePhysics); // timer starts below and emits timeout? updatePhysics is signal
    timer->start(16);

    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    // from lab
    float pixelX = ui->firstLabel->x();
    float pixelY = ui->firstLabel->y();
    bodyDef.position.Set(pixelX / 30, pixelY / 30); // converts pixels to 'world' by dividing by 30
    body = world.CreateBody(&bodyDef);
    // from video but this doesnt work
    // bodyDef.position.set(box2d.coordPixelToWorld(x,y));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePhysics()
{
    // from lab:
        // Prepare for simulation. Typically we use a time step of 1/60 of a
        // second (60Hz) and 10 iterations. This provides a high quality simulation
        // in most game scenarios.
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world.Step(timeStep, velocityIterations, positionIterations);
    b2Vec2 position = body->GetPosition();
    ui->firstLabel->move(position.x * 30, position.y * 30); // converts 'world' to pixels by multiplying by 30
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{



    body->SetLinearVelocity(b2Vec2(5.0f, 0.0f));

    QTimer::singleShot(50, this, [=]() {
        body->SetLinearVelocity(b2Vec2(-5.0f, 0.0f));
    });

    QTimer::singleShot(100, this, [=]() {
        body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    });
}


