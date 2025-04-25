/**
    This program is an application that provides
    tutorials for sudoku solving techniques and
    then allows the user to practice what they've
    learned on procedurally generated puzzles with
    the ability to take notes and ask for hints.

    Author: AMANDA STOFEY, ADRIANA BATRES,
        MASON AYERS, ALEXANDER GOFF, DREW BROADBENT
    Date: 4/22/2025
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <list>
#include "sudokubox.h"
#include "sudokumodel.h"

using std::vector;
using std::list;
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
    SudokuModel* m;
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
    int counter = 0;

    list<SudokuBox*> awaitingInputs;

    /**
     * The introductory tutorial to explain the basics of sudoku
     */
    Tutorial *introduction;

    /**
     * The tutorial on how to take notes in the sudoku application
     */
    Tutorial *noteTaking;

    /**
     * The tutorial for the hidden Singles technique
     */
    Tutorial *hiddenSingles;

    /**
     * The tutorial for the hidden pairs technique
     */
    Tutorial *hiddenPairs;

    /**
     * The tutorial for the naked pairs technique
     */
    Tutorial *nakedPairs;

    /**
     * The current tutorial being displayed
     */
    Tutorial* currentTutorial;

    /**
     * A method to clear all the tutorial labels.
     */
    void clearLabels();

public:
    /**
     * Constructor for the MainWindow object
     * @param model - Our Sudoku Model that contains all the information for sudoku puzzles
     * @param parent - The Parent of MainWindow is QWidget
     */
    MainWindow(SudokuModel* model, QWidget *parent = nullptr);

    /**
     * Destructor for MainWindow
     */
    ~MainWindow();

    /**
     * @brief Handles all key presses to take in numbers for
     * the sudiku box
     *
     * @param event is number entered
     */
    void keyPressEvent(QKeyEvent* event);

    /**
     * @brief disable all boxes in sudoku box
     */
    void disableAllBoxes();

    /**
     * @brief Called by pickSaveFile(). Creates a QJsonArray and
     * appapends a QJSON Object of each box in SudokuBox containing
     * its text, stylesheet, and isEnabled. It then opens and writes
     * this json to the given filepath. Failure issues a qWarning and
     * returns.
     * @param filePath to save on
     */
    void saveGame(const QString& filePath);

    /**
     * @brief Open's the file at the filepath, and then fills the cells
     * SudokuBox by converting the QJsonObject into the necessary
     * datatype. When failing to find a file, issues a qWarning and
     * returns.
     *
     * @param filePath to read from
     */
    void loadGame(const QString& filePath);

public slots:
    /**
     * Slot that updates the view to properly display a newly selected sudokubox.
     * Additonally, clears the previously selected sudoku box.
     * @param currentSelection - The newly selected sudoku box
     */
    void updateSelected(SudokuBox* currentSelection);

    /**
     * Enables the box to be edited at the selected index
     * @param index - the index of the box to be enabled
     */
    void enableBox (int index);

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

    /**
     * Allows you to pick a file to load.
     */
    void pickLoadFile();


    /**
     * Allows you to save a file and give it a name
     */
    void pickSaveFile();

    /**
     * Displays text in the text Box at the top of the tutorial text box list
     * @param text - the text to be displayed
     */
    void displayTextBox1(QString text);

    /**
     * Displays text in the text Box in the middle of the tutorial text box list
     * @param text - the text to be displayed
     */
    void displayTextBox2(QString text);

    /**
     * Displays text in the text Box at the bottom of the tutorial text box list
     * @param text - the text to be displayed
     */
    void displayTextBox3(QString text);

    /**
     * hightlights the box at the selected index within the grid
     * @param index - the index of the box to be highlighted
     */
    void highlightBox(int index);

    /**
     * Adds the box at the selected index to the vector of items awaiting inputs
     * @param index - the index of the box awaiting an input
     */
    void awaitInput(int index);

    /**
     * Changes the view to the tutorials page
     */
    void goToTutorialsPage();

    /**
     * starts the game with a random sudoku puzzle
     */
    void startGame();

    /**
     * starts the introductory tutorial
     */
    void startIntroduction();

    /**
     * Starts the tutorial for note taking
     */
    void startNoteTaking();

    /**
     * Starts the tutorial for Hidden Singles
     */
    void startHiddenSingles();

    /**
     * Starts the tutorial for Hidden Pairs
     */
    void startHiddenPairs();

    /**
     * Starts the tutorial for Naked Pairs
     */
    void startNakedPairs();

    /**
     * Moves onto the next tutorial if one is available
     */
    void endOfTutorial();

    /**
     * Progresses the current tutorial to the next part. If the tutorial is at the end, calls endOfTutorial
     */
    void progressTutorial();

    /**
     * Sets the UI back to the homepage
     */
    void toHomePage();


signals:
    /**
     * Signal to update the model to a changed value on a sudoku box.
     * @param index - the index of the entered value.
     * @param value - the value of the sudoku box.
     */
    void updateCell(int index, int value);

    /**
     * Checks with the model to see if the box at the current index has the correct input
     * @param index - the index of the box to be checked
     * @return true if the box contains the correct value, false if not.
     */
    bool checkCell(int index);

    /**
     * Gets the next line for the tutorial to be displayed
     * @param words - The list of words to be displayed in the tutorial.
     */
    void readLine(QStringList words);

    /**
     * Sets up the tutorial sudoku puzzle by getting the answer key and the starting values from the given text files.
     * @param keyFile - The file that contains the answer key
     * @param startFile - The file that contains the starting values
     */
    void setupTutorial(QString keyFile, QString startFile);

};
#endif // MAINWINDOW_H
