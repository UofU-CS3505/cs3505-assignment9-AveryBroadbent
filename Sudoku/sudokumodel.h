#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H
#include <vector>
#include <QObject>
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class SudokuModel: public QObject
{
    Q_OBJECT
private:
    vector<int> cellContents;
    vector<int> answerKey;

public:
    SudokuModel();
    void uploadNewPuzzle();
    void checkInputs();
    void uploadKey(QString fileName);
    void genKey();
    void updateSudoku(std::vector<int>* sudoku, int changedIndex, int guessVal, bool* backingSolvedIndex);
    void genCellContents();

signals:
    void correctAnswers(vector<int> correctIndexes);
    void incorrectAnswers(vector<int> incorrectIndexes);
    void showHint(int index, int showValue);
    void showStartingValues(std::map<int, int> startingValues);
    void rowCorrect(int rowNum);
    void colCorrect(int colNum);
    void boxCorrect(int boxRow, int boxCol);
public slots:
    void updateInput(int index, int value);
    void getHint();
    void tutorialSetup();

};

#endif // SUDOKUMODEL_H
