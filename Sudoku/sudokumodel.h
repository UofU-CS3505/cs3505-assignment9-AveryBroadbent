/**
    A class that holds a backing vector of cell
    contents and the answer key. Used by
    sudokubox to determine if rows are
    finished. Can use wave propogation
    collapse to generate new puzzles

    Author: AMANDA STOFEY, ADRIANA BATRES,
        MASON AYERS, ALEXANDER GOFF, DREW BROADBENT
    Date: 4/22/2025
 */
#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H
#include <vector>
#include <QObject>
#include "tutorial.h"
using std::vector;

class SudokuModel: public QObject
{
    Q_OBJECT
private:
    vector<int> cellContents;
    vector<int> answerKey;

    /**
     * @brief currentTutorialLines
     */
    vector<QStringList> currentTutorialLines;

    size_t currentTutorialIndex;

    int currentTutorial = 0;

public:
    SudokuModel();
    ~SudokuModel();

    /**
     * Checks each value in each non-zero cell for matching values to the answer key.
     */
    void checkInputs();

    /**
     * Uploads a new answer key into the anserKey vector from a given filename
     * @param fileName - The file containing the answer key
     */
    void uploadKey(QString fileName);

    /**
     * Generates a new solved sudoku board answer key, randomly generated using wave propogation.
     */
    void genKey();

    /**
     * Helper method for genKey method. Used to repeatedly update
     * other values in the progogate stage of wave function
     * collapse.
     * @param sudoku
     * @param changedIndex
     * @param guessVal
     * @param backingSolvedIndex
     */
    void updateSudoku(std::vector<int>* sudoku, int changedIndex, int guessVal, bool* backingSolvedIndex);

    /**
     * Fills cellContents from the answerKey and removes all
     * but 32 to 28 randomly chosen, for a starting sudoku puzzle.
     */
    void genCellContents();

    /**
     * @brief newPuzzleSetup
     */
    void newPuzzleSetup();

    QJsonArray toJson() const;

    void fromJson(const QJsonArray& loadedFile);

    /**
     * @brief introduction tutorial
     */
    Tutorial *introduction;

    /**
     * @brief noteTaking
     */
    Tutorial *noteTaking;






signals:
    /**
     * Signals to the view which cell contents are correct.
     * @param correctIndexes
     */
    void correctAnswers(vector<int> correctIndexes);

    /**
     * Signals to the view which cell contents are incorrect.
     */
    void incorrectAnswers(vector<int> incorrectIndexes);

    /**
     * Signals to the view a selected hint and its value.
     * @param index - index of the hint's location.
     * @param showValue - value of the hint to show.
     */
    void showHint(int index, int showValue);

    /**
     * Signals to the view which starting values to display and their values
     * @param startingValues - map of (index, values) representing starting values for a sudoku puzzle
     */
    void showStartingValues(std::map<int, int> startingValues);

    /**
     * Signals to the view a correct row
     * @param rowNum - index of the correct row
     */
    void rowCorrect(int rowNum);

    /**
     * Signals to the view a correct column
     * @param colNum - index of the correct column
     */
    void colCorrect(int colNum);

    /**
     * Signals to the view a correct 3x3 box
     * @param boxRow - first row of the correct box
     * @param boxCol - first column of the correct box
     */
    void boxCorrect(int boxRow, int boxCol);

    /**
     * @brief hideNote used to hide the notetaking checkbox for certain tutorials
     */
    void hideNote();

    /**
     * @brief setHeader used to set the header to the tutorial name
     * @param tutorialName the header name
     */
    void setHeader(QString tutorialName);

    /**
     * @brief updateTutorialTextBox1 tutorialTextBox1 will contain the message
     * @param tutorialMessage the tutorial text being set in the QLabel
     */
    void updateTutorialTextBox1(QString tutorialMessage); //TODO might be easier to do just string?

    /**
     * @brief updateTutorialTextBox2 tutorialTextBox2 will contain the message
     * @param tutorialMessage the tutorial text being set in the QLabel
     */
    void updateTutorialTextBox2(QString tutorialMessage);

    /**
     * @brief updateTutorialTextBox3 tutorialTextBox3 will contain the message
     * @param tutorialMessage the tutorial text being set in the QLabel
     */
    void updateTutorialTextBox3(QString tutorialMessage);
    /**
     * @brief highlightCell informs the sudoku grid to highlight/enable a given cell
     * @param the cell being highlighted
     */
    void highlightCell(int cellIndex);

    /**
     * @brief enableCell
     * @param cellIndex
     */
    void enableCell(int cellIndex);

    /**
     * @brief awaitCell
     * @param cellIndex
     */
    void awaitCell(int cellIndex);

    /**
     * @brief endOfIntoTutorial
     */
    void endOfIntroTutorial();



public slots:
    /**
     * Slot to the model handling a change to an index in the cell contents.
     * @param index - index of the value to update.
     * @param value - value to update to.
     */
    void updateInput(int index, int value);

    /**
     * Retrieves a hint from a randomized index in the answer key.
     */
    void getHint();

    /**
     * @brief tutorialSetup - Sets up a template tutorial from a preset file location.
     */
    void tutorialSetup();

    /**
     * @brief introTutorial handles the logic when the intro tutorial has been selected in mainwindow
     */
    void introTutorial(int x);

    /**
     * @brief noteTutorial handles the logic when the note taking tutorial has been selected in mainwindow
     */
    void noteTutorial();

    /**
     * @brief decipherNextLine
     * @param words
     */
    void decipherNextLine(QStringList words);

    bool checkInput(int index);
};

#endif // SUDOKUMODEL_H
