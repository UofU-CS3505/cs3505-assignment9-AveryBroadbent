#include "tutorial.h"

Tutorial::Tutorial(const QString &filename, QString tutorialName): file(filename), tutorialName(tutorialName)
{

}

vector<QStringList> Tutorial::getLines()
{
    QFile file(":/textFiles/puzzleFiles/TutorialStartingIndexes.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // error
        QMessageBox::information(nullptr, QString("Could not load key file"), file.errorString());
    }

    QTextStream in(&file);

    vector<QStringList> lines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList words = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        lines.push_back(words);
    }

    file.close();
    return lines;
}
