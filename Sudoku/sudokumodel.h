#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H
#include <vector>
#include <QObject>
#include <iostream>
#include <vector>
#include <algorithm>
#include "tutorial.h"
using std::vector;

class SudokuModel: public QObject
{
    Q_OBJECT
private:
    vector<int> cellContents;
    vector<int> answerKey;

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

signals:
    void correctAnswers(vector<int> correctIndexes);
    void incorrectAnswers(vector<int> incorrectIndexes);
    void showHint(int index, int showValue);
    void showStartingValues(std::map<int, int> startingValues);
    void rowCorrect(int rowNum);
    void colCorrect(int colNum);
    void boxCorrect(int boxRow, int boxCol);

    /**
     * @brief hideNote used to hide the notetaking for certain tutorials
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
     * @brief updateTutorialTextBox2
     * @param tutorialMessage
     */
    void updateTutorialTextBox2(QString tutorialMessage);

    /**
     * @brief updateTutorialTextBox3
     * @param tutorialMessage
     */
    void updateTutorialTextBox3(QString tutorialMessage);

    /**
     * @brief highlightCell informs the sudoku grid to highlight a given cell
     * @param the cell being highlighted
     */
    void highlightCell(int cellIndex);

public slots:
    void updateInput(int index, int value);
    void getHint();
    void tutorialSetup();

};

#endif // SUDOKUMODEL_H
