#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "sudokubox.h"
#include "sudokumodel.h"

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    SudokuBox* selectedCell = nullptr;
    vector<SudokuBox*> cells;

public:
    MainWindow(SudokuModel* model, QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);

public slots:
    void updateSelected(SudokuBox* currentSelection);
    void cellCorrect(int index);
    void cellIncorrect(int index);
    void displayHint(int cellIndex, int answer);
    void displayStartingValues(std::map<int, int> startingValues);
    void rowFinished(int row);

signals:
    void updateCell(int index, int value);




};
#endif // MAINWINDOW_H
