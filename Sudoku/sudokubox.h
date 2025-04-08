#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

#include <QWidget>
#include <QLabel>

class SudokuBox : public QLabel
{
    Q_OBJECT
private:
    int boxValue = 0;

    void updateText();

public:
    explicit SudokuBox(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent* event);

signals:


};

#endif // SUDOKUBOX_H
