#include "tutorial.h"
#include <QDebug>


Tutorial::Tutorial(const QString &filename, QString tutorialName): file(filename), tutorialName(tutorialName)
{
}

void Tutorial::loadLines()
{
    QFile file(":/textFiles/puzzleFiles/SudokuTutorialScripts/SudokuIntroduction.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // error
        QMessageBox::information(nullptr, QString("Could not load key file"), file.errorString());
    }

    QTextStream in(&file);

    lines.clear();
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList words = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        lines.push_back(words);
    }

    file.close();
}

QStringList Tutorial::getLine(int line) {
    return lines.at(line);
}
