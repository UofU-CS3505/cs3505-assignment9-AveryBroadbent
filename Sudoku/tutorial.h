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

private:

    vector<QStringList> lines;

public:

    /**
     * @brief Tutorial constructor
     * @param filename the textFile associated with a given tutorial
     * @param tutorialName the tutorial name that will be set as the header
     */
    Tutorial(QString tutorialName);

    /**
     * @brief tutorialName the tutorial name that will be set as the header
     */
    QString tutorialName;

    /**
     * @brief getNextLine calls the file reader to read the lines from a tutorial's text file
     * @return a vector of QStringLists- each QStringList is derived from a line from the text file
     */
    void loadLines(QString filename);

    /**
     * Gets the line at the given index in the list of Strings
     * @param line - The index of the line to return
     * @return the line at the given index
     */
    QStringList getLine(int line);

    /**
     * Checks if we're at the end of the list of lines
     * @param line - The index of the current line
     * @return true if we're at the end of lines, false if not
     */
    bool isAtEnd(int line);
};

#endif // TUTORIAL_H
