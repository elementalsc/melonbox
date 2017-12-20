#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Melon/ProgressionBuilder.h"

using namespace std;

RootWindow::RootWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::RootWindow)
{
    ui->setupUi(this);
    ui->variationNumber->setValue(1);
    logger = MelonLogger::getInstance();
}

RootWindow::~RootWindow()
{
    delete ui;
}

void RootWindow::on_pushButton_clicked()
{
    // [ ] affichage des degreés relativement à Ionien/Aéolien (n'importe quel mode idéalement!)
    // [ ] affichage des noms des accords
    // [ ] faire un tableau donnant l'historique de la création de la progression
    // [/] faire un logger qui est un singleton

    ProgressionBuilder progBuilder;
    ui->oProgDisplay->append(QString::fromStdString(progBuilder.generate().toString()));

}

