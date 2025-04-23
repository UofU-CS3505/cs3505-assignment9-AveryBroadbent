/**
    This Class is used to represent the
    currently displayed boxes in the qt
    window. It's connected to the users clicks
    and inputs in the qt boxes. It can set
    notes, and save and read from json.

    Author: AMANDA STOFEY, ADRIANA BATRES,
        MASON AYERS, ALEXANDER GOFF, DREW BROADBENT
    Date: 4/22/2025
 */
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

    QJsonArray toJson() const;

    void fromJson(const QJsonArray& loadedFile);

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:


signals:
    /**
     * Signals to the view which sudoku box has been selected by the mouse.
     * @param selectedBox - Pointer to the sudoku box ui element selected
     */
    void selected(SudokuBox* selectedBox);

};

#endif // SUDOKUBOX_H
