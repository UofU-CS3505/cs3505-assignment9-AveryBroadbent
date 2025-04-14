#include "sudokumodel.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

SudokuModel::SudokuModel() {
    cellContents = vector<int>(81, 0);
    answerKey = vector<int>(81, 5);


}

void SudokuModel::tutorialSetup() {
    uploadKey(":/textFiles/puzzleFiles/TutorialPuzzle.txt");
    vector<int> startingIndexes;
    std::map<int, int> startingValues;

    QFile file(":/textFiles/puzzleFiles/TutorialStartingIndexes.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // error
        QMessageBox::information(nullptr, QString("Could not load key file"), file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()){
        QString index = in.readLine();
        startingIndexes.push_back(index.toInt());
    }

    for(int index : startingIndexes){
        startingValues[index] = answerKey.at(index);
        cellContents.at(index) = answerKey.at(index);
    }

    file.close();
    emit showStartingValues(startingValues);
}

void SudokuModel::uploadNewPuzzle() {

}

void SudokuModel::updateInput(int index, int value) {
    cellContents.at(index) = value;
}

void SudokuModel::checkInputs(){
    //Add a check to see if entire row/box/column is correct and if so, emit correctRow, correctColumn, correctBox that
    //pulses the row/box/column green
    for(int i = 0; i < 81; i++) {
        if(cellContents.at(i) == 0)
            continue;
        else if(cellContents.at(i) == answerKey.at(i))
            emit correctAnswer(i);
        else
            emit incorrectAnswer(i);
    }



    //check if row is correct
    bool isRowCorrect;
    for(int row = 0; row < 9; row++) {
        isRowCorrect = true;
        for(int col = 0; col < 9; col++) {
            //box number = i * 9 + j
            if(!(cellContents.at(row*9+col) == answerKey.at(row*9+col))) {
                isRowCorrect = false;
                break;
            }
        }
        if(isRowCorrect == true){
            emit rowCorrect(row);
        }
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

void SudokuModel::uploadKey(QString fileName) {
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // error
            QMessageBox::information(nullptr, QString("Could not load key file"), file.errorString());
        }

        QTextStream in(&file);
        QString key = in.readAll();
        file.close();

        qDebug() << key.length();

        answerKey.clear();
        for (int i = 0; i < key.length(); i++) {
            int value = key.at(i).digitValue();
            answerKey.push_back(value);
        }
        qDebug() << answerKey.size();
        // TODO: populate cell contents and send starting values to grid
    }
}
