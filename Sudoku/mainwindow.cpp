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

    timeStep = 1.0f / 60.0f;
    velocityIterations = 6;
    positionIterations = 2;

    connect(timer,
            &QTimer::timeout,
            this,
            &MainWindow::updatePhysics); // timer starts below and emits timeout? updatePhysics is signal

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
            &SudokuModel::correctAnswers,
            this,
            &MainWindow::cellsCorrect);

    connect(model,
            &SudokuModel::incorrectAnswers,
            this,
            &MainWindow::cellsIncorrect);

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

    //selectedCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
    QString indexString = (selectedCell->objectName()).remove(QRegularExpression("\\D"));
    int index = indexString.toInt()-1;

    int value = 0;
    switch(event->key()) {
    case Qt::Key_1:
        value = 1;
        break;

    case Qt::Key_2:
        value = 2;
        break;

    case Qt::Key_3:
        value = 3;
        break;

    case Qt::Key_4:
        value = 4;
        break;

    case Qt::Key_5:
        value = 5;
        break;

    case Qt::Key_6:
        value = 6;
        break;

    case Qt::Key_7:
        value = 7;
        break;

    case Qt::Key_8:
        value = 8;
        break;

    case Qt::Key_9:
        value = 9;
        break;
    }

    if (ui->noteCheck->isChecked()) {
        // Set box to 0
        selectedCell->updateText(0);
        emit updateCell(index, 0);
        // Add note
        selectedCell->setNote(value);
    }
    else {
        selectedCell->updateText(value);
        emit updateCell(index, value);
    }
}

void MainWindow::updateSelected(SudokuBox* currentSelection) {
    qDebug() << "Updating selected Color";
    if (selectedCell != nullptr && selectedCell->isEnabled())
        selectedCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);"); // White
    currentSelection->setStyleSheet("background-color: rgb(165, 210, 242); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);"); // Blue
    selectedCell = currentSelection;
}

void MainWindow::cellsCorrect(vector<int> correctIndexes){
    correctBodies.clear();
    correctCells.clear();
    for(int correctIndex : correctIndexes){
        SudokuBox* correctCell = cells.at(correctIndex);
        if (!correctCell->isEnabled())
            continue;
        correctCells.push_back(correctCell);
        correctCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(105, 197, 95); border-color: rgb(0, 0, 0);");

        //animation stuff
        bodyDef.type = b2_kinematicBody;
        float pixelX = correctCell->x();
        float pixelY = correctCell->y();
        bodyDef.position.Set(pixelX/scale, pixelY/scale); // converts pixels to 'world' by dividing by 30
        b2Body* currentBody = world.CreateBody(&bodyDef);

        currentBody->SetLinearVelocity(b2Vec2(0.0f, -10.0f));

        QTimer::singleShot(50, correctCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(0.0f, 10.0f));
        });

        QTimer::singleShot(100, correctCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        });

        QTimer::singleShot(150, correctCell, [=]() {
            timer->stop();
            correctCell->setDisabled(true);
            selectedCell = nullptr;
        });

        correctBodies.push_back(currentBody);
    }

    if(!timer->isActive()){
        timer->start(16);
    }
}
void MainWindow::cellsIncorrect(vector<int> incorrectIndexes){
    incorrectBodies.clear();
    incorrectCells.clear();
    for(int incorrectIndex : incorrectIndexes){
        SudokuBox* incorrectCell = cells.at(incorrectIndex);
        if (!incorrectCell->isEnabled())
            continue;
        incorrectCells.push_back(incorrectCell);
        incorrectCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(197, 49, 49); border-color: rgb(0, 0, 0);");

        //animation stuff
        bodyDef.type = b2_kinematicBody;
        float pixelX = incorrectCell->x();
        float pixelY = incorrectCell->y();
        bodyDef.position.Set(pixelX/scale, pixelY/scale); // converts pixels to 'world' by dividing by 30
        b2Body* currentBody = world.CreateBody(&bodyDef);

        QTimer::singleShot(0, incorrectCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(-20.0f, 0.0f));
        });

        QTimer::singleShot(50, incorrectCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(40.0f, 0.0f));
        });

        QTimer::singleShot(100, incorrectCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(-20.0f, 0.0f));
        });

        QTimer::singleShot(150, incorrectCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
        });

        QTimer::singleShot(200, incorrectCell, [=]() {
            timer->stop();
            selectedCell = nullptr;
        });

        incorrectBodies.push_back(currentBody);
    }

    if(!timer->isActive()){
        timer->start(16);
    }
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

    world.Step(timeStep, velocityIterations, positionIterations);
    for(size_t i = 0; i < correctBodies.size(); i++) {
        b2Vec2 pos = correctBodies[i]->GetPosition();
        correctCells.at(i)->move(pos.x * scale, pos.y * scale);
    }

    for(size_t i = 0; i < incorrectBodies.size(); i++) {
        b2Vec2 pos = incorrectBodies[i]->GetPosition();
        incorrectCells.at(i)->move(pos.x * scale, pos.y * scale);
    }
}


