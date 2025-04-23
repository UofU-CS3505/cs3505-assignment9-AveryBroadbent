/**
    Tutorial class that reads from a text
    file and produces a QStringList of
    lines for the mainwindow to display.

    Author: AMANDA STOFEY, ADRIANA BATRES,
        MASON AYERS, ALEXANDER GOFF, DREW BROADBENT
    Date: 4/22/2025
 */
#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QRegularExpression>
#include <vector>
using std::vector;

class Tutorial : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Tutorial constructor
     * @param filename the textFile associated with a given tutorial
     * @param tutorialName the tutorial name that will be set as the header
     */
    Tutorial(const QString &filename, QString tutorialName);

    /**
     * @brief tutorialName the tutorial name that will be set as the header
     */
    QString tutorialName;

    /**
     * @brief getNextLine calls the file reader to read the lines from a tutorial's text file
     * @return a vector of QStringLists- each QStringList is derived from a line from the text file
     */
    void loadLines();

    QStringList getLine(int line);

    bool isAtEnd(int line);

signals:




public slots:


private:

    /**
     * @brief file tutorial's script file
     */
    QFile file;

    vector<QStringList> lines;





};

#endif // TUTORIAL_H
