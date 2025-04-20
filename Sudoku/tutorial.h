/**
 * Tutorial class
 *
 * @author Mason Ayers
 * @version April 20, 2025
 */
#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QRegularExpression>

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

signals:




public slots:
    /**
     * @brief getNextLine calls the file reader to read the next line and handles commands at the beginning of the line.
     * This is called when the user clicks- could be changed to a timer based thing.
     */
    void getNextLine();

private:

    /**
     * @brief file tutorial's script file
     */
    QFile file;



};

#endif // TUTORIAL_H
