#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

#include <QWidget>
#include <QLabel>

class SudokuBox : public QLabel
{
    Q_OBJECT
private:
    int boxValue = 0;
    bool notes[9] = {};

public:
    explicit SudokuBox(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent* event)override;
    void updateText(int boxVal);
    void setNote(int value);
    void reset();

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:


signals:
    void selected(SudokuBox* selectedBox);

};

#endif // SUDOKUBOX_H
