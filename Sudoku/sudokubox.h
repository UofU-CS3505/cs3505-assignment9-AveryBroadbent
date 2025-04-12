#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

#include <QWidget>
#include <QLabel>

class SudokuBox : public QLabel
{
    Q_OBJECT
private:
    int boxValue = 0;

public:
    explicit SudokuBox(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent* event)override;
    void updateText(int boxVal);
public slots:


signals:
    void selected(SudokuBox* selectedBox);

};

#endif // SUDOKUBOX_H
