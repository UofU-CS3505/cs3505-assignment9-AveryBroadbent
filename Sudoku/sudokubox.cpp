#include "sudokubox.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

SudokuBox::SudokuBox(QWidget *parent)
    : QLabel{parent}
{}

void SudokuBox::updateText(int boxVal)
{
    qDebug() <<"Attempting to update";
    boxValue = boxVal;
    if (boxVal == 0) {
        setText("");
    }
    else{
        setText(QString::number(boxValue));
    }
    qDebug() <<"Text Updated";
}

void SudokuBox::mousePressEvent(QMouseEvent* event) {
    if (event->button()==Qt::LeftButton) {
        qDebug() <<"Cell Selected";
        emit selected(this);
    }
}
