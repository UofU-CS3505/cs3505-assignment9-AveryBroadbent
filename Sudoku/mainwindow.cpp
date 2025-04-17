#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QRegularExpression>
#include <QTimer>


MainWindow::MainWindow(SudokuModel* model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , world(b2Vec2(0.0f, -10.0f))
    , timer(new QTimer(this))
{
    ui->setupUi(this);
    //firstLabel = ui->firstLabel;

    //is this supposed to be a single shot? This would updatePhysics every 16ms. is this what we want?
    connect(timer, &QTimer::timeout, this, &MainWindow::updatePhysics); // timer starts below and emits timeout? updatePhysics is signal
    // timer->start(16);
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    // from lab
    /*
    float pixelX = ui->firstLabel->x();
    float pixelY = ui->firstLabel->y();
    bodyDef.position.Set(pixelX / 30, pixelY / 30); // converts pixels to 'world' by dividing by 30
    body = world.CreateBody(&bodyDef);
    */
    // from video but this doesnt work
    // bodyDef.position.set(box2d.coordPixelToWorld(x,y));



    // Set up references to sboxes
    for (int i = 1; i <= 81; i++) {
        QString sboxName = QString("sbox")+QString::number(i);
        SudokuBox* thisBox = ui->sudokuFrame->findChild<SudokuBox *>(sboxName);

        connect(thisBox,
                &SudokuBox::selected,
                this,
                &MainWindow::updateSelected);

        cells.push_back(thisBox);
    }
    connect(ui->checkAnswerButton,
            &QPushButton::clicked,
            model,
            &SudokuModel::checkInputs);

    //might want to change which button is mapped to tutorial setup
    connect(ui->startTutorialButton,
            &QPushButton::clicked,
            model,
            &SudokuModel::tutorialSetup);

    connect(this,
            &MainWindow::updateCell,
            model,
            &SudokuModel::updateInput);

    connect(model,
            &SudokuModel::correctAnswer,
            this,
            &MainWindow::cellCorrect);

    connect(model,
            &SudokuModel::incorrectAnswer,
            this,
            &MainWindow::cellIncorrect);

    // Hints
    connect(ui->hintButton,
            &QPushButton::clicked,
            model,
            &SudokuModel::getHint);

    connect(model,
            &SudokuModel::showHint,
            this,
            &MainWindow::displayHint);

    // Start values
    connect(model,
            &SudokuModel::showStartingValues,
            this,
            &MainWindow::displayStartingValues);

    // Display
    connect(model,
            &SudokuModel::rowCorrect,
            this,
            &MainWindow::rowFinished);

    connect(model,
            &SudokuModel::colCorrect,
            this,
            &MainWindow::colFinished);

    connect(model,
            &SudokuModel::boxCorrect,
            this,
            &MainWindow::boxFinished);


    qDebug() << "finished constructor";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if (selectedCell == nullptr)
        return;

    selectedCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
    QString indexString = (selectedCell->objectName()).remove(QRegularExpression("\\D"));
    int index = indexString.toInt()-1;

    switch(event->key()) {
    case Qt::Key_1:
        selectedCell->updateText(1);
        emit updateCell(index, 1);
        break;

    case Qt::Key_2:
        selectedCell->updateText(2);
        emit updateCell(index, 2);
        break;

    case Qt::Key_3:
        selectedCell->updateText(3);
        emit updateCell(index, 3);
        break;

    case Qt::Key_4:
        selectedCell->updateText(4);
        emit updateCell(index, 4);
        break;

    case Qt::Key_5:
        selectedCell->updateText(5);
        emit updateCell(index, 5);
        break;

    case Qt::Key_6:
        selectedCell->updateText(6);
        emit updateCell(index, 6);
        break;

    case Qt::Key_7:
        selectedCell->updateText(7);
        emit updateCell(index, 7);
        break;

    case Qt::Key_8:
        selectedCell->updateText(8);
        emit updateCell(index, 8);
        break;

    case Qt::Key_9:
        selectedCell->updateText(9);
        emit updateCell(index, 9);
        break;
    }

    // Remove selected cell
    // NOTE: I added this since setting the color back to white made it look like it unselected after entering a number
    // I actually like that as a design choice so I'm adding it. If we don't like it, we can just remove this.
    selectedCell = nullptr;
}

void MainWindow::updateSelected(SudokuBox* currentSelection) {
    qDebug() << "Updating selected Color";
    if (selectedCell != nullptr && selectedCell->isEnabled())
        selectedCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);"); // White
    currentSelection->setStyleSheet("background-color: rgb(165, 210, 242); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);"); // Blue
    selectedCell = currentSelection;
}

void MainWindow::cellCorrect(int index){
    SudokuBox* correctCell = cells.at(index);

    if (!correctCell->isEnabled())
        return;

    if (selectedCell == correctCell)
        selectedCell = nullptr;

    correctCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(105, 197, 95); border-color: rgb(0, 0, 0);");
    correctCell->setDisabled(true);
}
void MainWindow::cellIncorrect(int index){
    cells.at(index)->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(197, 49, 49); border-color: rgb(0, 0, 0);");
    if (cells.at(index) == selectedCell)
        selectedCell = nullptr;
}

void MainWindow::displayHint(int cellIndex, int answer) {
    SudokuBox* hintCell = cells.at(cellIndex);
    hintCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(240, 212, 2); border-color: rgb(0, 0, 0);");
    hintCell->updateText(answer);
    hintCell->setDisabled(true);
    qDebug() << "hint Displayed at box:" << cellIndex + 1;

    if (selectedCell == hintCell)
        selectedCell = nullptr;
}

void MainWindow::displayStartingValues(std::map<int, int> startingValues){
    for (const auto& pair : startingValues) {
        cells.at(pair.first)->updateText(pair.second);
        cells.at(pair.first)->setDisabled(true);
        cells.at(pair.first)->setStyleSheet("background-color: rgb(219, 219, 219); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
    }
}

void MainWindow::rowFinished(int row) {
    int startingIndex = row * 9;
    for(int i = startingIndex; i < startingIndex + 9; i++) {
        cells.at(i)->setStyleSheet("background-color: rgb(163, 222, 149); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
        if (selectedCell == cells.at(i))
            selectedCell = nullptr;
    }
}

void MainWindow::colFinished(int col) {
    for(int i = col; i <= (col + (9 * 8)); i += 9) {
        cells.at(i)->setStyleSheet("background-color: rgb(163, 222, 149); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
        if (selectedCell == cells.at(i))
            selectedCell = nullptr;
    }
}

void MainWindow::boxFinished(int boxRow, int boxCol){
    int rowStart = (boxCol * 3) + (boxRow * 27);
    int bottomRightCell = rowStart + 20;
    int currentIndex = rowStart;

    while(currentIndex <= bottomRightCell && currentIndex < 81) {
        for(; currentIndex < rowStart + 3; currentIndex ++){
            cells.at(currentIndex)->setStyleSheet("background-color: rgb(163, 222, 149); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
            if (selectedCell == cells.at(currentIndex))
                selectedCell = nullptr;
        }
        rowStart += 9;
        currentIndex = rowStart;
    }
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
    //ui->firstLabel->move(position.x * 30, position.y * 30); // converts 'world' to pixels by multiplying by 30
}

// void MainWindow::mousePressEvent(QMouseEvent *event)
// {
//     body->SetLinearVelocity(b2Vec2(5.0f, 0.0f));

//     QTimer::singleShot(50, this, [=]() {
//         body->SetLinearVelocity(b2Vec2(-5.0f, 0.0f));
//     });

//     QTimer::singleShot(100, this, [=]() {
//         body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
//     });
// }


