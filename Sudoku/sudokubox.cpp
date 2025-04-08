#include "sudokubox.h"
#include <QMouseEvent>
#include <QDebug>

SudokuBox::SudokuBox(QWidget *parent)
    : QLabel{parent}
{}

void SudokuBox::updateText()
{
    if (boxValue == 0)
        setText("");
    else
        setText(QString::number(boxValue));
}

void SudokuBox::mousePressEvent(QMouseEvent* event) {
    if (event->button()==Qt::LeftButton) {
        qDebug() << "left clicked";

        boxValue++;
        if (boxValue > 9)
            boxValue = 0;

        updateText();
    }
    else if (event->button()==Qt::RightButton) {
        qDebug() << "right clicked";

        boxValue--;
        if (boxValue < 0)
            boxValue = 9;
        updateText();
    }
    else if (event->button()==Qt::MiddleButton) {
        qDebug() << "middle clicked";

        boxValue = 0;
        updateText();
    }
}
