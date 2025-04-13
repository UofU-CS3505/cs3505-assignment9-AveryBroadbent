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
    void uploadKey(QString fileName);
signals:
    void correctAnswer(int index);
    void incorrectAnswer(int index);
    void showHint(int index, int showValue);
public slots:
    void updateInput(int index, int value);
    void getHint();

};

#endif // SUDOKUMODEL_H
