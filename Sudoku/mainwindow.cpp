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
        qDebug() << sboxName;
        SudokuBox* thisBox = ui->sudokuGrid->findChild<SudokuBox *>(sboxName);
        //thisBox->updateText(5);

        connect(ui->sbox1,
                &SudokuBox::selected,
                this,
                &MainWindow::updateSelected);

        cells.push_back(thisBox);
    }

    for(SudokuBox* box : cells){
        connect(box,
                &SudokuBox::selected,
                this,
                &MainWindow::updateSelected);
    }


    qDebug() << cells.size();
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
        break;

    case Qt::Key_3:
        break;

    case Qt::Key_4:
        break;

    case Qt::Key_5:
        break;

    case Qt::Key_6:
        break;

    case Qt::Key_7:
        break;

    case Qt::Key_8:
        break;

    case Qt::Key_9:
        break;
    }

    qDebug() << "Finished switch";
}

void MainWindow::updateSelected(SudokuBox* currentSelection) {
    qDebug() << "I HEAR YOU";
    selectedCell = currentSelection;
}


