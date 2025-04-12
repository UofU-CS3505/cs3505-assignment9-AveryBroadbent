#include "sudokubox.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

SudokuBox::SudokuBox(QWidget *parent)
    : QLabel{parent}
{}

void SudokuBox::updateText(int boxVal)
{
    if (!this->isEnabled())
        return;

    boxValue = boxVal;
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
