#include "sudokumodel.h"
#include <QDebug>

SudokuModel::SudokuModel() {
    cellContents = vector<int>(81, 0);
    answerKey = vector<int>(81, 5);
}

void SudokuModel::uploadNewPuzzle() {

}

void SudokuModel::uploadAnswerKey() {

}

void SudokuModel::updateInput(int index, int value) {
    cellContents.at(index) = value;
}

void SudokuModel::checkInputs(){
    for(int i = 0; i < 81; i++) {
        if(cellContents.at(i) == 0)
            continue;
        else if(cellContents.at(i) == answerKey.at(i))
            emit correctAnswer(i);
        else
            emit incorrectAnswer(i);
    }
}

void SudokuModel::getHint() {
    // Create vector for empty values
    vector<int> emptyIndexes;
    for (int i = 0; i < 81; i++) {
        if (cellContents.at(i) == 0) {
            emptyIndexes.push_back(i);
        }
    }

    int chosenHint = emptyIndexes.at(std::rand() % emptyIndexes.size());
    cellContents.at(chosenHint) = answerKey.at(chosenHint);
    emit showHint(chosenHint, answerKey.at(chosenHint));

}
