#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H
#include <vector>
#include <QObject>
#include <iostream>
#include <algorithm>
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

    int currentTutorialIndex;

public:
    SudokuModel();
    ~SudokuModel();
    void uploadNewPuzzle();
    void checkInputs();
    void uploadKey(QString fileName);
    void genKey();
    void updateSudoku(std::vector<int>* sudoku, int changedIndex, int guessVal, bool* backingSolvedIndex);
    void genCellContents();
    void newPuzzleSetup();

    /**
     * @brief introduction tutorial
     */
    Tutorial *introduction;

    /**
     * @brief noteTaking
     */
    Tutorial *noteTaking;

signals:
    void correctAnswers(vector<int> correctIndexes);
    void incorrectAnswers(vector<int> incorrectIndexes);
    void showHint(int index, int showValue);
    void showStartingValues(std::map<int, int> startingValues);
    void rowCorrect(int rowNum);
    void colCorrect(int colNum);
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
     * @brief endOfTutorial
     */
    void endOfTutorial();

public slots:
    void updateInput(int index, int value);
    void getHint();
    void tutorialSetup();

    /**
     * @brief introTutorial handles the logic when the intro tutorial has been selected in mainwindow
     */
    void introTutorial();

    /**
     * @brief noteTutorial handles the logic when the note taking tutorial has been selected in mainwindow
     */
    void noteTutorial();

    /**
     * @brief decipherNextLine
     * @param words
     */
    void decipherNextLine(QStringList words);
};

#endif // SUDOKUMODEL_H
