#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Melon/ProgressionBuilder.h"

using namespace std;

RootWindow::RootWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::RootWindow)
{
    ui->setupUi(this);
    ui->uVariationNumber->setValue(1);
    ui->uScaleList->setCurrentRow(0);
    ui->uModeList->setCurrentRow(0);
    ui->uModeTypeList->setCurrentRow(0);
    ui->pushButton->setFocus();
    logger = MelonLogger::getInstance();
}

RootWindow::~RootWindow()
{
    delete ui;
}

void RootWindow::on_pushButton_clicked()
{
    // [ ] mixture modale
    // [ ] affichage des degreés relativement à Ionien/Aéolien (n'importe quel mode idéalement!)

    Note iNote = static_cast<Note>(ui->uScaleList->currentRow());
    Mode iMode = static_cast<Mode>(ui->uModeList->currentRow()+1);
    ModeType iModeType = static_cast<ModeType>(ui->uModeTypeList->currentRow()+1);
    int iVariation = ui->uVariationNumber->value();

    ProgressionBuilder progBuilder(iVariation, iNote, iMode, iModeType);

    Progression prog = progBuilder.generate();
    ui->oProgDisplay->append(QString::fromStdString(prog.toString()));
    ui->oProgDisplay->append(QString::fromStdString(prog.printChords()));

}

