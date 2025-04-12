#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H
#include <vector>
#include <QObject>

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
    void uploadAnswerKey();
    void checkInputs();
signals:
    void correctAnswer(int index);
    void incorrectAnswer(int index);
public slots:
    void updateInput(int index, int value);

};

#endif // SUDOKUMODEL_H
