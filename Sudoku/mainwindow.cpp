#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QRegularExpression>
MainWindow::MainWindow(SudokuModel* model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if (selectedCell == nullptr)
        return;

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
}

void MainWindow::updateSelected(SudokuBox* currentSelection) {
    selectedCell = currentSelection;
}

void MainWindow::cellCorrect(int index){
    cells.at(index)->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(105, 197, 95); border-color: rgb(0, 0, 0);");
    cells.at(index)->setDisabled(true);
}
void MainWindow::cellIncorrect(int index){
    cells.at(index)->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(197, 49, 49); border-color: rgb(0, 0, 0);");
}


