#include "tutorial.h"

Tutorial::Tutorial(const QString &filename, QString tutorialName): file(filename), tutorialName(tutorialName)
{

}

void Tutorial::getNextLine()
{
    QFile file(":/textFiles/puzzleFiles/TutorialStartingIndexes.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // error
        QMessageBox::information(nullptr, QString("Could not load key file"), file.errorString());
    }

    QTextStream in(&file);

    QString text;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList words = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        for(int i = 0; i < 2; i++) //loop through the command prompts at the beginning of the line
        {
            if(words.at(0)!="[]")
            {
                //TODO emit signal to highlight given cell(s)
            }
            words.removeAt(i); //remove command prompt
        }

        if(words.at(0)=="[textbox1]")
        {
            //TODO add logic to connect the text textBox1
        }
        else if(words.at(0)=="[textbox2]")
        {
            //TODO add logic to connect the text textBox2
        }
        else
        {
            //TODO add logic to connect the text textBox3
        }
        words.removeAt(0); //remove command prompt

        for (const QString &word : words) {
            text += word + " ";
        }
    }

    file.close();//This will be moved elsewhere
}
