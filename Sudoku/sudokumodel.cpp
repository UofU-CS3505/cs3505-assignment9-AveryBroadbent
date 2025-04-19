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
    vector<int> correctBoxes;
    vector<int> incorrectBoxes;
    for(int i = 0; i < 81; i++) {
        if(cellContents.at(i) == 0)
            continue;
        else if(cellContents.at(i) == answerKey.at(i))
            correctBoxes.push_back(i);
        else
            incorrectBoxes.push_back(i);
    }

    emit correctAnswers(correctBoxes);
    emit incorrectAnswers(incorrectBoxes);



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

    //check if col is correct
    bool isColCorrect;
    for(int col = 0; col < 9; col++) {
        isColCorrect = true;
        for(int row = 0; row < 9; row++) {
            if(!(cellContents.at(row*9+col) == answerKey.at(row*9+col))) {
                isColCorrect = false;
                break;
            }
        }
        if(isColCorrect == true){
            emit colCorrect(col);
        }
    }


    bool isBoxCorrect;
    for(int boxRow = 0; boxRow <= 2; boxRow++){
        for(int boxCol = 0; boxCol <= 2; boxCol++){
            isBoxCorrect = true;

            //top left cell of box is (boxCol * 3) + (boxRow * 27), this is also the start of the first row of the box.
            //bottom right cell is top left + 20
            int rowStart = (boxCol * 3) + (boxRow * 27);
            int bottomRightCell = rowStart + 20;
            int currentIndex = rowStart;

            //check each cell within the current box
            while(currentIndex <= bottomRightCell && currentIndex < 81) {
                for(; currentIndex < rowStart + 3; currentIndex ++){
                    if(!(cellContents.at(currentIndex) == answerKey.at(currentIndex))) {
                        isBoxCorrect = false;
                        break;
                    }
                }
                if(isBoxCorrect == false) {
                    break;
                }
                rowStart += 9;
                currentIndex = rowStart;
            }
            //if entire box is correct, tell the view
            if(isBoxCorrect == true){
                emit boxCorrect(boxRow, boxCol);
            }
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

    if (emptyIndexes.empty())
        return;

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

//SUDOKU GENERATION STUFF
/**
 * Replaces the answerKey with a new solved sudoku
 * board randomly generated using wave propogation.
 */
void SudokuModel::genKey(){
    //Make a backing double array. The way
    //Wave propogate works is the following:
    //
    std::vector<int>* solvedSudoku = new std::vector<int>[81];
    srand(time(NULL));
    for(int i=0; i <81; i++){
        for(int num = 1; num < 10; num++)
            solvedSudoku[i].push_back(num);
    }
    bool backingSolvedIndex[81]{};
    for(int i=0; i <81; i++){
        backingSolvedIndex[i] = false;
    }
    bool notSolved = true;
    bool needReset = false;
    while(notSolved){
        int index = rand() % 81;
        int lowestEntropyIndex = index;
        int maxLoopVal = 81 + index;
        for(int i = index; i < maxLoopVal ;i++){
            int currentIndex = (index+i) % 81;
            if(solvedSudoku[currentIndex].size() < solvedSudoku[lowestEntropyIndex].size() && !backingSolvedIndex[currentIndex]){
                lowestEntropyIndex = currentIndex;
            }
        }
        int size = solvedSudoku[lowestEntropyIndex].size();
        int guessIndex = rand()%size;
        int guessVal = solvedSudoku[lowestEntropyIndex].at(guessIndex);
        solvedSudoku[lowestEntropyIndex].clear();
        solvedSudoku[lowestEntropyIndex].push_back(guessVal);
        backingSolvedIndex[lowestEntropyIndex] = true;
        updateSudoku(solvedSudoku, lowestEntropyIndex, guessVal, backingSolvedIndex);
        notSolved = false;
        for(int i = 0; i < 81; i++){
            if(solvedSudoku[i].size() != 1)
                notSolved = true;
            if(solvedSudoku[i].size() == 0){
                needReset = true;
            }
        }

        if(needReset){
            for(int i = 0; i < 81; i++){
                solvedSudoku[i].clear();
                for(int num = 1; num < 10; num++)
                    solvedSudoku[i].push_back(num);
            }
            for(int i=0; i <81; i++){
                backingSolvedIndex[i] = false;
            }
            notSolved = true;
            needReset = false;
        }
    }
    answerKey.clear();
    for(int i = 0; i < 81; i++){
        answerKey.push_back(solvedSudoku[i].at(0));
    }
    delete[] solvedSudoku;
}

/**
 * Helper method for genKey. Used to repeatedly update
 * other values in the progogate stage of wave function
 * collapse.
 */
void SudokuModel::updateSudoku(std::vector<int>* sudoku, int changedIndex, int guessVal, bool* backingSolvedIndex){
    int row = changedIndex / 9;
    int col = changedIndex % 9;
    int box = (row/3)*3 + col/3;
    for(int i = 0; i < 81; i ++){
        if(i != changedIndex && !backingSolvedIndex[i]){
            int currentRow = i / 9;
            int currentCol = i % 9;
            int currentBox = (currentRow/3)*3 + currentCol/3;
            if((currentRow == row) || (currentCol == col) || (currentBox == box)){
                sudoku[i].erase(std::remove(sudoku[i].begin(), sudoku[i].end(), guessVal), sudoku[i].end());
            }
        }
    }
}

/**
 * Fills cellContents with answerKey then removes all
 * but 32 to 28 randomly chosen values by setting to
 * 0.
 */
void SudokuModel::genCellContents(){
    cellContents = vector<int>(81, 0);
    for(int i = 0; i < 81; i++){
        cellContents.push_back(answerKey.at(i));
    }
    srand(time(NULL));
    int endFilledNum = 32 - (rand() % 5);
    int currFilledNum = 81;
    while(currFilledNum > endFilledNum){
        int toRemove = rand() % 81;
        while(cellContents.at(toRemove)!= 0){
            toRemove = rand() % 81;
        }
        cellContents.at(toRemove) = 0;
        currFilledNum--;
    }
}
