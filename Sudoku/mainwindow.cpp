#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QRegularExpression>
#include <QTimer>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileDialog>
#include <QVariant>
#include <algorithm>

MainWindow::MainWindow(SudokuModel* model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , world(b2Vec2(0.0f, -10.0f))
    , correctTimer(new QTimer(this))
    , incorrectTimer(new QTimer(this))
{
    ui->setupUi(this);
    m = model;

    awaitingInputs = list<SudokuBox*>();

    // starts stackedWidget at the home page
    ui->stackedWidget->setCurrentWidget(ui->HomePage);
    connect(ui->newGameButton, &QPushButton::clicked, this, &MainWindow::startGame);

    //
    connect(ui->IntroductionButton, &QPushButton::clicked, this, &MainWindow::startIntroduction);

    ui->textLabel1->hide();
    ui->textLabel2->hide();
    ui->textLabel3->hide();
    ui->OopsLabel->hide();
    ui->toNoteTakingButton->hide();
    ui->toHiddenSinglesButton->hide();
    ui->toHiddenPairsButton->hide();
    ui->toNakedPairsButton->hide();

    // ":/textFiles/puzzleFiles/SudokuTutorialScripts/SudokuIntroduction.txt"
    introduction = new Tutorial("Intro");
    noteTaking = new Tutorial("Note Taking");
    hiddenPairs = new Tutorial("Hidden Pairs");
    hiddenSingles = new Tutorial("Hideen Singles");
    nakedPairs = new Tutorial("Naked Pairs");


    // Setup for SudokuGame widget
    timeStep = 1.0f / 60.0f;
    velocityIterations = 6;
    positionIterations = 2;

    connect(correctTimer,
            &QTimer::timeout,
            this,
            &MainWindow::updateCorrectPhysics); // timer starts below and emits timeout? updatePhysics is signal

    connect(incorrectTimer,
            &QTimer::timeout,
            this,
            &MainWindow::updateIncorrectPhysics);

    // Set up references to sboxes
    for (int i = 1; i <= 81; i++) {
        QString sboxName = QString("sbox")+QString::number(i);
        SudokuBox* thisBox = ui->sudokuFrame->findChild<SudokuBox *>(sboxName);

        connect(thisBox,
                &SudokuBox::selected,
                this,
                &MainWindow::updateSelected);

        cells.push_back(thisBox);
    }

    connect(ui->homeButton,
            &QPushButton::clicked,
            this,
            &MainWindow::toHomePage);

    connect(ui->checkAnswerButton,
            &QPushButton::clicked,
            model,
            &SudokuModel::checkInputs);

    connect(ui->loadGameButton,
            &QPushButton::clicked,
            this,
            &MainWindow::pickLoadFile);

    connect(ui->saveGameButton,
            &QPushButton::clicked,
            this,
            &MainWindow::pickSaveFile);

    // Home button connections
    connect(ui->IntroductionButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startIntroduction);

    connect(ui->TutorialsButton,
            &QPushButton::clicked,
            this,
            &MainWindow::goToTutorialsPage);

    connect(this,
            &MainWindow::readLine,
            m,
            &SudokuModel::decipherNextLine);

    connect(this,
            &MainWindow::setupTutorial,
            m,
            &SudokuModel::tutorialGridSetup);

    connect(model,
            &SudokuModel::updateTutorialTextBox1,
            this,
            &MainWindow::displayTextBox1);

    connect(model,
            &SudokuModel::updateTutorialTextBox2,
            this,
            &MainWindow::displayTextBox2);

    connect(model,
            &SudokuModel::updateTutorialTextBox3,
            this,
            &MainWindow::displayTextBox3);

    connect(ui->NextButton,
            &QPushButton::clicked,
            this,
            &MainWindow::progressTutorial);

    // connect(ui->toNoteTakingButton,
    //         &QPushButton::clicked,
    //         model,
    //         &SudokuModel::tutorialSetup);

    connect(model,
            &SudokuModel::endOfIntroTutorial,
            this,
            &MainWindow::endOfTutorial);

    connect(model,
            &SudokuModel::highlightCell,
            this,
            &MainWindow::highlightBox);

    connect(model,
            &SudokuModel::enableCell,
            this,
            &MainWindow::enableBox);

    connect(model,
            &SudokuModel::awaitCell,
            this,
            &MainWindow::awaitInput);

    connect(this,
            &MainWindow::checkCell,
            model,
            &SudokuModel::checkInput);

    connect(ui->newGameButton,
            &QPushButton::clicked,
            model,
            &SudokuModel::newPuzzleSetup);

    connect(this,
            &MainWindow::updateCell,
            model,
            &SudokuModel::updateInput);

    connect(model,
            &SudokuModel::correctAnswers,
            this,
            &MainWindow::cellsCorrect);

    connect(model,
            &SudokuModel::incorrectAnswers,
            this,
            &MainWindow::cellsIncorrect);

    // Hints
    connect(ui->hintButton,
            &QPushButton::clicked,
            model,
            &SudokuModel::getHint);

    connect(model,
            &SudokuModel::showHint,
            this,
            &MainWindow::displayHint);

    // Start values
    connect(model,
            &SudokuModel::showStartingValues,
            this,
            &MainWindow::displayStartingValues);

    // Display
    connect(model,
            &SudokuModel::rowCorrect,
            this,
            &MainWindow::rowFinished);

    connect(model,
            &SudokuModel::colCorrect,
            this,
            &MainWindow::colFinished);

    connect(model,
            &SudokuModel::boxCorrect,
            this,
            &MainWindow::boxFinished);

    //TODO create startNoteTaking method to initiate note tutorial, similar to how intro is initiated
    connect(ui->toNoteTakingButton,
            &QPushButton::clicked,
            this, &MainWindow::startNoteTaking);

    connect(ui->toHiddenPairsButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startHiddenPairs);

    connect(ui->toHiddenSinglesButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startHiddenSingles);

    connect(ui->toNakedPairsButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startNakedPairs);


    //Tutorial Page connections
    connect(ui->homeButtonTutorial,
            &QPushButton::clicked,
            this,
            &MainWindow::toHomePage);

    connect(ui->tutorialIntroductionButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startIntroduction);

    connect(ui->tutorialNoteTakingButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startNoteTaking);

    connect(ui->tutorialHiddenSinglesButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startHiddenSingles);

    connect(ui->tutorialHiddenPairsButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startHiddenPairs);

    connect(ui->tutorialsNakedPairsButton,
            &QPushButton::clicked,
            this,
            &MainWindow::startNakedPairs);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete introduction;
    delete noteTaking;
    delete hiddenPairs;
    delete hiddenSingles;
    delete nakedPairs;
}

void MainWindow::disableAllBoxes(){
    for(int i = 0; i < (int)cells.size(); i++){
        cells.at(i) -> setDisabled(true);
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if (selectedCell == nullptr)
        return;

    //selectedCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
    QString indexString = (selectedCell->objectName()).remove(QRegularExpression("\\D"));
    int index = indexString.toInt()-1;

    int value = 0;
    switch(event->key()) {
    case Qt::Key_1:
        value = 1;
        break;

    case Qt::Key_2:
        value = 2;
        break;

    case Qt::Key_3:
        value = 3;
        break;

    case Qt::Key_4:
        value = 4;
        break;

    case Qt::Key_5:
        value = 5;
        break;

    case Qt::Key_6:
        value = 6;
        break;

    case Qt::Key_7:
        value = 7;
        break;

    case Qt::Key_8:
        value = 8;
        break;

    case Qt::Key_9:
        value = 9;
        break;
    }

    if (ui->noteCheck->isChecked()) {
        // Set box to 0
        selectedCell->updateText(0);
        emit updateCell(index, 0);
        // Add note
        selectedCell->setNote(value);
    }
    else {
        selectedCell->updateText(value);
        emit updateCell(index, value);
        // Handle awaiting inputs
        if (std::find(awaitingInputs.begin(), awaitingInputs.end(), selectedCell) != awaitingInputs.end()) {

            if (emit checkCell(index)) {
                // selected cell was awaited and is correct
                qDebug() << awaitingInputs.size();
                awaitingInputs.remove(selectedCell);
                ui->OopsLabel->hide();
                // selectedCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);"); // reset color
                // selectedCell->setDisabled(true);
                selectedCell = nullptr;

                m->checkInputs();

                // check if list is now empty
                if (awaitingInputs.empty()) {
                    ui->NextButton->show();
                    progressTutorial();
                }

                qDebug() << awaitingInputs.size();
            }
            else {
                //Oops! Wrong input!
                ui->OopsLabel->show();
            }
        }
    }
}

void MainWindow::updateSelected(SudokuBox* currentSelection) {
    if (selectedCell != nullptr && selectedCell->isEnabled())
        selectedCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);"); // White
    if(currentSelection != nullptr)
        currentSelection->setStyleSheet("background-color: rgb(165, 210, 242); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);"); // Blue
    selectedCell = currentSelection;
}

void MainWindow::cellsCorrect(vector<int> correctIndexes){
    correctBodies.clear();
    correctCells.clear();
    for(int correctIndex : correctIndexes){
        SudokuBox* correctCell = cells.at(correctIndex);
        if (!correctCell->isEnabled())
            continue;
        correctCells.push_back(correctCell);
        correctCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(105, 197, 95); border-color: rgb(0, 0, 0);");

        //animation stuff
        bodyDef.type = b2_kinematicBody;
        float pixelX = correctCell->x();
        float pixelY = correctCell->y();
        bodyDef.position.Set(pixelX/scale, pixelY/scale); // converts pixels to 'world' by dividing by 30
        b2Body* currentBody = world.CreateBody(&bodyDef);
        b2Vec2 originalPos = currentBody->GetPosition();
        ui->checkAnswerButton->setDisabled(true);
        currentBody->SetLinearVelocity(b2Vec2(0.0f, -10.0f));

        QTimer::singleShot(50, correctCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(0.0f, 10.0f));
        });

        QTimer::singleShot(100, correctCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
            currentBody->SetTransform(originalPos, 0.0f);
        });

        QTimer::singleShot(150, correctCell, [=]() {
            correctCell->setDisabled(true);
            selectedCell = nullptr;
            ui->checkAnswerButton->setDisabled(false);
            correctTimer->stop();
        });

        correctBodies.push_back(currentBody);
    }

    if(!correctTimer->isActive()){
        correctTimer->start(16);
    }
}
void MainWindow::cellsIncorrect(vector<int> incorrectIndexes){
    incorrectBodies.clear();
    incorrectCells.clear();
    for(int incorrectIndex : incorrectIndexes){
        SudokuBox* incorrectCell = cells.at(incorrectIndex);
        if (!incorrectCell->isEnabled())
            continue;
        incorrectCells.push_back(incorrectCell);
        incorrectCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(197, 49, 49); border-color: rgb(0, 0, 0);");

        //animation stuff
        bodyDef.type = b2_kinematicBody;
        float pixelX = incorrectCell->x();
        float pixelY = incorrectCell->y();
        bodyDef.position.Set(pixelX/scale, pixelY/scale); // converts pixels to 'world' by dividing by 30
        b2Body* currentBody = world.CreateBody(&bodyDef);
        b2Vec2 originalPos = currentBody->GetPosition();
        ui->checkAnswerButton->setDisabled(true);

        currentBody->SetLinearVelocity(b2Vec2(-20.0f, 0.0f));

        QTimer::singleShot(50, incorrectCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(40.0f, 0.0f));
        });

        QTimer::singleShot(100, incorrectCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(-20.0f, 0.0f));
        });

        QTimer::singleShot(150, incorrectCell, [=]() {
            currentBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
            currentBody->SetTransform(originalPos, 0.0f);
        });

        QTimer::singleShot(200, incorrectCell, [=]() {
            selectedCell = nullptr;
            ui->checkAnswerButton->setDisabled(false);
            incorrectTimer->stop();
        });

        incorrectBodies.push_back(currentBody);
    }

    if(!incorrectTimer->isActive()){
        incorrectTimer->start(16);
    }
}

void MainWindow::displayHint(int cellIndex, int answer) {
    SudokuBox* hintCell = cells.at(cellIndex);
    hintCell->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(240, 212, 2); border-color: rgb(0, 0, 0);");
    hintCell->updateText(answer);
    hintCell->setDisabled(true);

    if (selectedCell == hintCell)
        selectedCell = nullptr;
}

void MainWindow::displayStartingValues(std::map<int, int> startingValues){
    // Clear grid before showing start values
    for (int i = 0; i < 81; i++) {
        cells.at(i)->reset();
        cells.at(i)->setDisabled(false);
        cells.at(i)->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
    }

    // Fill out starting values
    for (const auto& pair : startingValues) {
        cells.at(pair.first)->updateText(pair.second);
        cells.at(pair.first)->setDisabled(true);
        cells.at(pair.first)->setStyleSheet("background-color: rgb(219, 219, 219); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
    }
}

void MainWindow::rowFinished(int row) {
    int startingIndex = row * 9;
    for(int i = startingIndex; i < startingIndex + 9; i++) {
        cells.at(i)->setStyleSheet("background-color: rgb(163, 222, 149); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
        if (selectedCell == cells.at(i))
            selectedCell = nullptr;
    }
}

void MainWindow::colFinished(int col) {
    for(int i = col; i <= (col + (9 * 8)); i += 9) {
        cells.at(i)->setStyleSheet("background-color: rgb(163, 222, 149); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
        if (selectedCell == cells.at(i))
            selectedCell = nullptr;
    }
}

void MainWindow::boxFinished(int boxRow, int boxCol){
    int rowStart = (boxCol * 3) + (boxRow * 27);
    int bottomRightCell = rowStart + 20;
    int currentIndex = rowStart;

    while(currentIndex <= bottomRightCell && currentIndex < 81) {
        for(; currentIndex < rowStart + 3; currentIndex ++){
            cells.at(currentIndex)->setStyleSheet("background-color: rgb(163, 222, 149); color: rgb(0, 0, 0); border-color: rgb(0, 0, 0);");
            if (selectedCell == cells.at(currentIndex))
                selectedCell = nullptr;
        }
        rowStart += 9;
        currentIndex = rowStart;
    }
}

void MainWindow::updateCorrectPhysics()
{
    // from lab:
        // Prepare for simulation. Typically we use a time step of 1/60 of a
        // second (60Hz) and 10 iterations. This provides a high quality simulation
        // in most game scenarios.

    world.Step(timeStep, velocityIterations, positionIterations);
    for(size_t i = 0; i < correctBodies.size(); i++) {
        b2Vec2 pos = correctBodies[i]->GetPosition();
        correctCells.at(i)->move(pos.x * scale, pos.y * scale);
    }
}

void MainWindow::updateIncorrectPhysics()
{
    // from lab:
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    world.Step(timeStep, velocityIterations, positionIterations);
    for(size_t i = 0; i < incorrectBodies.size(); i++) {
        b2Vec2 pos = incorrectBodies[i]->GetPosition();
        incorrectCells.at(i)->move(pos.x * scale, pos.y * scale);
    }
}

void MainWindow::pickLoadFile() {
    loadGame(QFileDialog::getOpenFileName(this, "Choose project to load", "", "Project files (*.sudoku)"));
}

void MainWindow::pickSaveFile() {
    saveGame(QFileDialog::getSaveFileName(this, "Choose Save Location", "", "Project files (*.sudoku)"));
}

void MainWindow::saveGame(const QString& filePath){
    QJsonObject toSave;
    QJsonArray mainWindowArray;
    QJsonArray modelArray;
    QJsonArray notesArray;

    updateSelected(nullptr);

    for(SudokuBox* box : cells){
        QJsonObject json;
        json["value"] = box->text();
        json["style"] = box->styleSheet();
        json["isEnabled"] = box->isEnabled();
        mainWindowArray.append(json);
        notesArray.append(box->toJson());
    }

    modelArray = m->toJson();


    toSave["View"] = mainWindowArray;
    toSave["Model"] = modelArray;
    toSave["Notes"] = notesArray;

    QJsonDocument doc(toSave);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open file.");
        return;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

/**
 * @brief Open's the file at the filepath, and then fills the cells
 * by converting the QJsonObject into the necessary datatype. When
 * failing to find a file, issues a qWarning and returns.
 *
 * @param filePath to read from
 */
void MainWindow::loadGame(const QString& filePath){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file to read.");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();

    int index = 0;
    QJsonArray notes = root["Notes"].toArray();
    for(const auto& val : root["View"].toArray()){
        QJsonObject obj = val.toObject();
        cells.at(index)->updateText(obj["value"].toString().toInt());
        cells.at(index)->setStyleSheet(obj["style"].toString());
        cells.at(index)->setDisabled(!(obj["isEnabled"].toBool()));
        cells.at(index)->fromJson(notes.at(index).toArray());
        index++;
    }

    m->fromJson(root["Model"].toArray());

    startGame();
}

void MainWindow::displayTextBox1(QString text)
{
    ui->textLabel1->show();
    ui->textLabel1->setText(text);
    counter++;
    ui->textLabel2->hide();
    ui->textLabel3->hide();
}

void MainWindow::displayTextBox2(QString text)
{
    ui->textLabel2->show();
    ui->textLabel2->setText(text);
    counter++;

    ui->textLabel1->hide();
    ui->textLabel3->hide();
}

void MainWindow::displayTextBox3(QString text)
{
    ui->textLabel3->show();
    ui->textLabel3->setText(text);
    counter++;

    ui->textLabel1->hide();
    ui->textLabel2->hide();
}

void MainWindow::goToTutorialsPage()
{
    ui->stackedWidget->setCurrentWidget(ui->TutorialsPage);
}

void MainWindow::startGame()
{
    // TODO: Clear grid since it doesn't do that after a tutorial
    clearLabels();

    qDebug() << "Calling Start Game";
    ui->stackedWidget->setCurrentWidget(ui->SudokuGame);
    ui->TitleLabel->setText("Sudoku");
    ui->checkAnswerButton->show();
    ui->hintButton->show();
    ui->hintButton->setEnabled(true);
    ui->saveGameButton->show();
    ui->noteCheck->show();
    ui->NextButton->hide();
    ui->toNoteTakingButton->hide();
    ui->toHiddenPairsButton->hide();
    ui->toHiddenSinglesButton->hide();
    ui->toNakedPairsButton->hide();

}

void MainWindow::startIntroduction()
{
    counter = 0;
    qDebug() << "Calling Introduction";
    emit setupTutorial(":/textFiles/puzzleFiles/TutorialPuzzle.txt", ":/textFiles/puzzleFiles/TutorialStartingIndexes.txt");
    qDebug() << "after emit";
    QString filename = ":/textFiles/puzzleFiles/SudokuTutorialScripts/SudokuIntroduction.txt";
    introduction->loadLines(filename);

    disableAllBoxes();
    ui->stackedWidget->setCurrentWidget(ui->SudokuGame);
    ui->TitleLabel->setText("Introduction");
    ui->TitleLabel->show();
    ui->hintButton->hide();
    ui->checkAnswerButton->hide();
    ui->saveGameButton->hide();
    ui->noteCheck->hide();
    ui->NextButton->show();
    ui->toNoteTakingButton->hide();
    ui->toHiddenPairsButton->hide();
    ui->toHiddenSinglesButton->hide();
    ui->toNakedPairsButton->hide();

    currentTutorial = introduction;
    progressTutorial();
}

void MainWindow::startNoteTaking()
{
    counter = 0;
    emit setupTutorial(":/textFiles/puzzleFiles/NotesPuzzle.txt", ":/textFiles/puzzleFiles/NotesStartingIndexes.txt");
    QString filename = ":/textFiles/puzzleFiles/SudokuTutorialScripts/SudokuNoteTaking.txt";
    noteTaking->loadLines(filename);

    disableAllBoxes();
    ui->stackedWidget->setCurrentWidget(ui->SudokuGame);
    ui->TitleLabel->setText("Note Taking");
    ui->TitleLabel->show();
    ui->hintButton->hide();
    ui->checkAnswerButton->hide();
    ui->saveGameButton->hide();
    ui->noteCheck->show();
    ui->toNoteTakingButton->hide();
    ui->NextButton->show();
    ui->toHiddenPairsButton->hide();
    ui->toHiddenSinglesButton->hide();
    ui->toNakedPairsButton->hide();

    currentTutorial = noteTaking;
    progressTutorial();
}

void MainWindow::startHiddenSingles()
{
    counter = 0;
    qDebug() << "Calling Hidden Singles";
    emit setupTutorial(":/textFiles/puzzleFiles/TutorialPuzzle.txt", ":/textFiles/puzzleFiles/TutorialStartingIndexes.txt");

    QString filename = ":/textFiles/puzzleFiles/SudokuTutorialScripts/SudokuHiddenSingles.txt";
    hiddenSingles->loadLines(filename);

    qDebug() << "after loading hidden singles file"; //This line is never reached, meaning the program crashes at loadlines call

    disableAllBoxes();
    ui->stackedWidget->setCurrentWidget(ui->SudokuGame);
    ui->TitleLabel->setText("Hidden Singles");
    ui->TitleLabel->show();
    ui->hintButton->hide();
    ui->checkAnswerButton->hide();
    ui->saveGameButton->hide();
    ui->noteCheck->hide();
    ui->NextButton->show();
    ui->toNoteTakingButton->show();
    ui->toHiddenPairsButton->hide();
    ui->toHiddenSinglesButton->hide();
    ui->toNakedPairsButton->hide();

    currentTutorial = hiddenSingles;
    progressTutorial();
}

void MainWindow::startHiddenPairs()
{
    counter = 0;
    emit setupTutorial(":/textFiles/puzzleFiles/NotesPuzzle.txt", ":/textFiles/puzzleFiles/NotesStartingIndexes.txt");
    QString filename = ":/textFiles/puzzleFiles/SudokuTutorialScripts/SudokuHiddenPairs.txt";
    hiddenPairs->loadLines(filename);

    disableAllBoxes();
    ui->stackedWidget->setCurrentWidget(ui->SudokuGame);
    ui->TitleLabel->setText("Hidden Pairs");
    ui->TitleLabel->show();
    ui->hintButton->hide();
    ui->checkAnswerButton->hide();
    ui->saveGameButton->hide();
    ui->noteCheck->show();
    ui->toNoteTakingButton->hide();
    ui->NextButton->show();
    ui->toHiddenPairsButton->hide();
    ui->toHiddenSinglesButton->hide();
    ui->toNakedPairsButton->hide();

    currentTutorial = hiddenPairs;
    progressTutorial();
}

void MainWindow::startNakedPairs()
{
    counter = 0;
    emit setupTutorial(":/textFiles/puzzleFiles/NotesPuzzle.txt", ":/textFiles/puzzleFiles/NotesStartingIndexes.txt");
    QString filename = ":/textFiles/puzzleFiles/SudokuTutorialScripts/SudokuNakedPairs.txt";
    nakedPairs->loadLines(filename);

    disableAllBoxes();
    ui->stackedWidget->setCurrentWidget(ui->SudokuGame);
    ui->TitleLabel->setText("Naked Pairs");
    ui->TitleLabel->show();
    ui->hintButton->show();
    ui->hintButton->setEnabled(false);
    ui->checkAnswerButton->hide();
    ui->saveGameButton->hide();
    ui->noteCheck->show();
    ui->toNoteTakingButton->hide();
    ui->NextButton->show();
    ui->toHiddenPairsButton->hide();
    ui->toHiddenSinglesButton->hide();
    ui->toNakedPairsButton->hide();


    currentTutorial = nakedPairs;
    progressTutorial();
}

void MainWindow::endOfTutorial()
{
    ui->NextButton->hide();
    if(currentTutorial==introduction)
        ui->toNoteTakingButton->show();
    else if (currentTutorial==noteTaking)
        ui->toHiddenSinglesButton->show();
    else if (currentTutorial==hiddenSingles)
        ui->toHiddenPairsButton->show();
    else if (currentTutorial==hiddenPairs)
        ui->toNakedPairsButton->show();
}

void MainWindow::progressTutorial() {
    if (currentTutorial->isAtEnd(counter))
        endOfTutorial();
    else
    {
        readLine(currentTutorial->getLine(counter));
        // ui->NextButton->show();
    }
}

void MainWindow::toHomePage()
{
    ui->stackedWidget->setCurrentWidget(ui->HomePage);
}

void MainWindow::highlightBox(int x)
{
    SudokuBox *selectedCell = cells.at(x);
    if (selectedCell != nullptr)
        selectedCell->setStyleSheet("background-color: rgb(100, 220, 100); border-width: 2px");
}
void MainWindow::awaitInput(int index) {
    awaitingInputs.push_back(cells.at(index));
    cells.at(index)->setStyleSheet("background-color: rgb(100, 220, 100); border-width: 2px");
    cells.at(index)->setDisabled(false);
    ui->NextButton->hide();
}

void MainWindow::enableBox (int index) {
    cells.at(index)->setDisabled(false);
}

void MainWindow::clearLabels() {
    ui->textLabel1->setText("");
    ui->textLabel2->setText("");
    ui->textLabel3->setText("");
}

