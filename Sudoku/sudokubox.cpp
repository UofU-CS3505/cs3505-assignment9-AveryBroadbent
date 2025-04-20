#include "sudokubox.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
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

void SudokuBox::setNote(int value) {
    int index = value-1;
    // Flip note spot
    notes[index] = !notes[index];

    update();
}

void SudokuBox::reset() {
    for (int i = 0; i < 9; i++) {
        notes[i] = false;
    }
    boxValue = 0;
    setText("");
    update();
}

void SudokuBox::mousePressEvent(QMouseEvent* event) {
    if (event->button()==Qt::LeftButton) {
        emit selected(this);
    }
}

void SudokuBox::paintEvent(QPaintEvent* event) {
    if (boxValue != 0) {
        // Draw text normally
        QLabel::paintEvent(event);
        return;
    }

    // Draw notes
    QPainter painter(this);

    // Set font of display grid
    QFont newFont(this->font()); // Create copy of font
    newFont.setPointSize(rect().height() * .2);
    painter.setFont(newFont);

    // Width/height of individual grids
    int h = rect().height()/3;
    int w = rect().width()/3;

    for (int i = 0; i < 9; i++) {
        // if no note on this index, skip
        if (!notes[i])
            continue;

        int row = (i) / 3;
        int col = (i) % 3;

        QRect textRect(col * w, row * h, w, h);
        painter.drawText(textRect, Qt::AlignCenter, QString::number(i+1));
    }

}
