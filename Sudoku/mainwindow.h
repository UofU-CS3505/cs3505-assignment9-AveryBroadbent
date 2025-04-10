#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "sudokubox.h"

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);
public slots:
    void updateSelected(SudokuBox* currentSelection);
private:
    Ui::MainWindow *ui;
    SudokuBox* selectedCell = nullptr;
    vector<SudokuBox*> cells;

signals:


};
#endif // MAINWINDOW_H
