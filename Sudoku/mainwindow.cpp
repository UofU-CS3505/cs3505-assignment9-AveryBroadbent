#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if (selectedCell == nullptr)
        return;

    qDebug() << "Key pressed";
    switch(event->key()) {
    case Qt::Key_1:
        selectedCell->updateText(1);
        break;

    case Qt::Key_2:
        selectedCell->updateText(2);
        break;

    case Qt::Key_3:
        selectedCell->updateText(3);
        break;

    case Qt::Key_4:
        selectedCell->updateText(4);
        break;

    case Qt::Key_5:
        selectedCell->updateText(5);
        break;

    case Qt::Key_6:
        selectedCell->updateText(6);
        break;

    case Qt::Key_7:
        selectedCell->updateText(7);
        break;

    case Qt::Key_8:
        selectedCell->updateText(8);
        break;

    case Qt::Key_9:
        selectedCell->updateText(9);
        break;
    }

    qDebug() << "Finished switch";
}

void MainWindow::updateSelected(SudokuBox* currentSelection) {
    qDebug() << "I HEAR YOU";
    selectedCell = currentSelection;
}


