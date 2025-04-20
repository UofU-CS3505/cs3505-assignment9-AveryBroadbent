#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "sudokubox.h"
#include "sudokumodel.h"

using std::vector;
#include <Box2D/Box2D.h>
#include <QLabel>

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
    b2World world;
    vector <b2Body*> correctBodies;
    vector <b2Body*> incorrectBodies;
    QTimer* correctTimer;
    QTimer* incorrectTimer;
    QLabel* firstLabel;
    float32 timeStep;
    int32 velocityIterations;
    int32 positionIterations;
    b2BodyDef bodyDef;
    const float scale = 30.0f;
    vector<SudokuBox*> correctCells;
    vector<SudokuBox*> incorrectCells;

public:
    MainWindow(SudokuModel* model, QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);
    // void mousePressEvent(QMouseEvent *event) override;

public slots:
    void updateSelected(SudokuBox* currentSelection);
    void cellsCorrect(vector <int> correctIndexes);
    void cellsIncorrect(vector <int> incorrectIndexes);
    void displayHint(int cellIndex, int answer);
    void displayStartingValues(std::map<int, int> startingValues);
    void rowFinished(int row);
    void colFinished(int col);
    void boxFinished(int boxRow, int boxCol);
    void updateCorrectPhysics();
    void updateIncorrectPhysics();

    void displayTextBox1();
    void displayTextBox2();
    void displayTextBox3();

signals:
    void updateCell(int index, int value);


};
#endif // MAINWINDOW_H
