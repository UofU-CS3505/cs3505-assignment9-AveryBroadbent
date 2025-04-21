#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "sudokubox.h"
#include "sudokumodel.h"

using std::vector;
#include <Box2D/Box2D.h>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    SudokuBox* selectedCell = nullptr;
    vector<SudokuBox*> cells;
    b2World world;
    vector <b2Body*> correctBodies;
    vector <b2Body*> incorrectBodies;
    QTimer* correctTimer;
    QTimer* incorrectTimer;
    QLabel* firstLabel;
    float32 timeStep;
    int32 velocityIterations;
    int32 positionIterations;
    b2BodyDef bodyDef;
    const float scale = 30.0f;
    vector<SudokuBox*> correctCells;
    vector<SudokuBox*> incorrectCells;

public:
    MainWindow(SudokuModel* model, QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event);
    // void mousePressEvent(QMouseEvent *event) override;

public slots:
    /**
     * Slot that updates the view to properly display a newly selected sudokubox.
     * Additonally, clears the previously selected sudoku box.
     * @param currentSelection - The newly selected sudoku box
     */
    void updateSelected(SudokuBox* currentSelection);

    /**
     * Displays a list of sudokubox indexs as correct, animates them, and disables them.
     * @param correctIndexes - A vector of indexes representing the locations of the correct sudoku boxes.
     */
    void cellsCorrect(vector<int> correctIndexes);

    /**
     * Displays a list of sudokubox indexs as incorrect and animates them.
     * @param correctIndexes - A vector of indexes representing the locations of the incorrect sudoku boxes.
     */
    void cellsIncorrect(vector<int> incorrectIndexes);

    /**
     * Displays a sudokubox's answer, and disables it.
     * @param cellIndex - The index of the sudokubox to place the hint at.
     * @param answer - The correct value of the sudokubox.
     */
    void displayHint(int cellIndex, int answer);

    /**
     * Clears the current grid displays the starting values of a new sudoku puzzle
     * @param startingValues - A map of (index, value) that marks each starting value.
     */
    void displayStartingValues(std::map<int, int> startingValues);

    /**
     * Marks a row in the sudoku grid as completed.
     * @param row - index of the row to mark as complete.
     */
    void rowFinished(int row);

    /**
     * Marks a column in the sudoku grid as completed.
     * @param col - index of the column to mark as complete.
     */
    void colFinished(int col);

    /**
     * Marks a 3x3 section of the sudoku grid as completed.
     * @param boxRow - index of the box's first row
     * @param boxCol - index of the box's first column
     */
    void boxFinished(int boxRow, int boxCol);

    /**
     * Prepares the correct sudoku boxes for animation.
     */
    void updateCorrectPhysics();

    /**
     * Prepares the incorrect sudoku boxes for animation.
     */
    void updateIncorrectPhysics();

    void displayTextBox1();
    void displayTextBox2();
    void displayTextBox3();

    void startIntroduction();
    void toHomePage();

signals:
    /**
     * Signal to update the model to a changed value on a sudoku box.
     * @param index - the index of the entered value.
     * @param value - the value of the sudoku box.
     */
    void updateCell(int index, int value);


};
#endif // MAINWINDOW_H
