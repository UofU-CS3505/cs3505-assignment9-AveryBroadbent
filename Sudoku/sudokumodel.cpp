#include "sudokumodel.h"
#include <QDebug>

SudokuModel::SudokuModel() {
    vector<int> cellContents(81, 0);
    qDebug() << cellContents.size();
    vector<int> answerKey(81, 5);
}

void SudokuModel::uploadNewPuzzle() {

}

void SudokuModel::uploadAnswerKey() {

}

void SudokuModel::updateInput(int index, int value) {
    cellContents.at(index) = value;
    qDebug() << "Hello";
}

void SudokuModel::checkInputs(){
    for(int i = 1; i <= 81; i++) {
        if(cellContents.at(i) == 0)
            continue;
        else if(cellContents.at(i) == answerKey.at(i))
            emit correctAnswer(i);
        else
            emit incorrectAnswer(i);
    }
}
