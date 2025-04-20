#ifndef SUDOKUBOX_H
#define SUDOKUBOX_H

#include <QWidget>
#include <QLabel>

class SudokuBox : public QLabel
{
    Q_OBJECT
private:
    /**
     * Represents the current value in the sudoku box
     */
    int boxValue = 0;
    /**
     * Represents selected notes
     */
    bool notes[9] = {};

public:
    explicit SudokuBox(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent* event)override;

    /**
     * Sets the text number value of the box. Setting to 0 will show an empty box.
     * @param boxVal
     */
    void updateText(int boxVal);

    /**
     * Toggles a note on/off for a value.
     */
    void setNote(int value);

    /**
     * Clear's the box's display information, setting its value to 0 and removing all notes.
     */
    void reset();

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:


signals:
    void selected(SudokuBox* selectedBox);

};

#endif // SUDOKUBOX_H
