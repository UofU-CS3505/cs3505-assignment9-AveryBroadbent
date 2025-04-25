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
    /**
     * Constructor for a sudokuBox object that represents one box in a sudoku grid
     * @param parent - The parent of SudokuBox is QWidget
     */
    explicit SudokuBox(QWidget *parent = nullptr);

    /**
     * This method activates when the user interacts with this object using the mouse
     * @param event - The type of mouse interaction
     */
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

    /**
     * Creates a QJsonArray out of this object.
     * @return A QJsonArray representing this object
     */
    QJsonArray toJson() const;

    /**
     * Translates a QJsonArray into this object
     * @param loadedFile - The information to be loaded into this object
     */
    void fromJson(const QJsonArray& loadedFile);

protected:
    /**
     * A paint event used to paint notes in the SudokuBox
     */
    void paintEvent(QPaintEvent* event) override;

signals:
    /**
     * Signals to the view which sudoku box has been selected by the mouse.
     * @param selectedBox - Pointer to the sudoku box ui element selected
     */
    void selected(SudokuBox* selectedBox);

};

#endif // SUDOKUBOX_H
