#include "sudokubox.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

SudokuBox::SudokuBox(QWidget *parent)
    : QLabel{parent}
{}

void SudokuBox::updateText(int boxVal)
{
    boxValue = boxVal;
    qDebug() << "Settting value";
    if (boxVal == 0) {
        setText("");
    }
    else{

        setText(QString::number(boxValue));
    }

}

void SudokuBox::mousePressEvent(QMouseEvent* event) {
    if (event->button()==Qt::LeftButton) {
        emit selected(this);
    }
}
