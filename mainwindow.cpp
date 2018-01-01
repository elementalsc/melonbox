#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Melon/ProgressionBuilder.h"

using namespace std;

RootWindow::RootWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::RootWindow)
{
    ui->setupUi(this);
    ui->uVariationNumber->setValue(1);
    ui->uScaleList->setItemSelected(0,true);
    ui->uModeList->setItemSelected(0,true);
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
    // [ ] affichage des noms des accords

    Note iNote = static_cast<Note>(ui->uScaleList->currentRow());
    Mode iMode = static_cast<Mode>(ui->uModeList->currentRow()+1) ;
    int iVariation = ui->uVariationNumber->value();

    ProgressionBuilder progBuilder(iVariation, iNote, iMode);

    Progression prog = progBuilder.generate();
    ui->oProgDisplay->append(QString::fromStdString(prog.toString()));
    ui->oProgDisplay->append(QString::fromStdString(prog.printChords()));

}

